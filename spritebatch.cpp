#include "spritebatch.h"
#include <QGLFunctions>
#include "jatlas.h"
#include <settings.h>

SpriteBatch::SpriteBatch(JGraphics *parent, QOpenGLContext *context) :
    m_parent(parent),
    m_context(context),
    current(-1),
    cur(0)
{
    index = new unsigned int[SIZE*6];
    uv = new vec2[SIZE*4];
    pos = new vec3[SIZE*4];
    col = new col4[SIZE*4];
    vert_b.create();
    col_b.create();
    uv_b.create();
    ind_b.create();
    vao.create();

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_COLOR_ATTRIBUTE 2

    texture_program = new QOpenGLShaderProgram();
    loadShader("data/shaders/simple.vert", "data/shaders/simple.frag", texture_program);

    bind(texture_program);
    texture_program->setUniformValue("colorTexture", 0);

    color_program = new QOpenGLShaderProgram();
    loadShader("data/shaders/color.vert", "data/shaders/color.frag", color_program);

    font_program = new QOpenGLShaderProgram();
    loadShader("data/shaders/font.vert", "data/shaders/font.frag", font_program);

    bind(font_program);
    texture_program->setUniformValue("colorTexture", 0);

    initFreeType();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SpriteBatch::initFreeType()
{
    FT_Library ft;
    if(FT_Init_FreeType(&ft))
    {
        qDebug() << "could not init free type library.";
        return;
    }
    else
        qDebug() << "FT init OK";
    QString fontPath = QApplication::applicationDirPath() + "/data/fonts/Inconsolata.otf";
    if(FT_New_Face(ft, fontPath.toLatin1().data(), 0, &m_ftFace))
    {
        qDebug() << "Could not open font" << fontPath;
        return;
    }
    else
        qDebug() << "FT face OK";

    FT_Set_Pixel_Sizes(m_ftFace, 0, 48);
}

vec2 SpriteBatch::renderText(const char *text, float x, float y, float sx, float sy, vec4 col_)
{
    float x_start = x;
    float y_start = y;
    float x_max = 0;
    const char *p;
    FT_GlyphSlot ftGlyph = m_ftFace->glyph;

    GLuint ftTex;
    Texture tex;
    glGenTextures(1, &ftTex);
    glBindTexture(GL_TEXTURE_2D, ftTex);

    for(p = text; *p; p++)
    {
        if(*p == '\n')
        {
            y+=20;
            x=x_start;
            continue;
        }
        if(FT_Load_Char(m_ftFace, *p, FT_LOAD_RENDER))
        {
            qDebug() << "Could not load character" << *p;
            continue;
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, ftGlyph->bitmap.width,
                     ftGlyph->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE,
                     ftGlyph->bitmap.buffer);

        float w = ftGlyph->bitmap.width * sx;
        float h = ftGlyph->bitmap.rows * sy;
        float x2 = x + ftGlyph->bitmap_left * sx;
        float y2 = y + 20 - ftGlyph->bitmap_top * sy;

        GLfloat box[4][4] =
        {
            {x2,     -y2    , 0, 0},
            {x2 + w, -y2    , 1, 0},
            {x2,     -y2 - h, 0, 1},
            {x2 + w, -y2 - h, 1, 1},
        };

        tex.textureId = ftTex;
        drawQuadText(vec2(x2, y2), vec2(w, h), tex, col_);
        render();

        x += (ftGlyph->advance.x >> 6) * sx;
        y += (ftGlyph->advance.y >> 6) * sy;
        x_max = max(x, x_max);
    }
    return vec2(x_max - x_start, y - y_start);
}

vec2 SpriteBatch::drawText(const QString &text, vec2 pos, vec2 size, vec4 col_)
{
    renderText(text.toLatin1().data(), pos.x() + 1, pos.y(), size.x(), size.y(), col_);
}

SpriteBatch::~SpriteBatch()
{
    delete[] index;
    delete[] uv;
    delete[] pos;
    delete[] col;

    vert_b.destroy();
    col_b.destroy();
    uv_b.destroy();
    ind_b.destroy();
    vao.destroy();

    delete texture_program;
    delete color_program;
    delete font_program;
}

void SpriteBatch::bind(QOpenGLShaderProgram *prog)
{
    current_program = prog;
    prog->bind();
    prog->setUniformValue("MVP", uni);
}

void SpriteBatch::drawQuadAtlas(vec2 loc, vec2 size, QString num, vec4 col_)
{
    auto inst = JAtlas::instance();
    if(current_program != texture_program)
    {
        render();
        bind(texture_program);
    }    if(inst->tex->textureId != current)
    {
        render();
        current = inst->tex->textureId;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, current);
    }

    if(cur >= SIZE - 1)
        render();

    auto f = inst->sources.find(num);
    if(f == inst->sources.end())
        return;

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = col_;
    col[cur*4 + 1] = col_;
    col[cur*4 + 2] = col_;
    col[cur*4 + 3] = col_;

    vec2 source = inst->sources[num];

    uv[cur*4]      = source;
    uv[cur*4 + 1]  = source + vec2(inst->sSize.x(), 0);
    uv[cur*4 + 2]  = source + inst->sSize;
    uv[cur*4 + 3]  = source + vec2(0, inst->sSize.y());

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::drawQuadText(vec2 loc, vec2 size, const Texture &tex, vec4 col_)
{
    if(current_program != font_program)
    {
        render();
        bind(font_program);
    }
    if(tex.textureId != current)
    {
        render();
        current = tex.textureId;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, current);
    }

    if(cur >= SIZE - 1)
        render();

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = col_;
    col[cur*4 + 1] = col_;
    col[cur*4 + 2] = col_;
    col[cur*4 + 3] = col_;

    uv[cur*4]      =vec2(0,0);
    uv[cur*4 + 1]  =vec2(1,0);
    uv[cur*4 + 2]  =vec2(1,1);
    uv[cur*4 + 3]  =vec2(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::drawQuad(vec2 loc, vec2 size, const Texture &tex, vec4 col_)
{
    if(current_program != texture_program)
    {
        render();
        bind(texture_program);
    }
    if(tex.textureId != current)
    {
        render();
        current = tex.textureId;
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, current);
    }
    if(cur >= SIZE - 1)
        render();

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = col_;
    col[cur*4 + 1] = col_;
    col[cur*4 + 2] = col_;
    col[cur*4 + 3] = col_;

    uv[cur*4]      =vec2(0,0);
    uv[cur*4 + 1]  =vec2(1,0);
    uv[cur*4 + 2]  =vec2(1,1);
    uv[cur*4 + 3]  =vec2(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::drawRect(vec2 loc, vec2 size, col4 _col)
{
    if(cur >= SIZE - 1)
        render();
    if(current_program != color_program)
    {
        render();
        bind(color_program);
    }

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = _col;
    col[cur*4 + 1] = _col;
    col[cur*4 + 2] = _col;
    col[cur*4 + 3] = _col;

    uv[cur*4]      = vec2(0,0);
    uv[cur*4 + 1]  = vec2(1,0);
    uv[cur*4 + 2]  = vec2(1,1);
    uv[cur*4 + 3]  = vec2(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::drawRect(vec2 loc, vec2 size, col4 left, col4 right)
{
    if(cur >= SIZE - 1)
        render();
    if(current_program != color_program)
    {
        render();
        bind(color_program);
    }

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = left;
    col[cur*4 + 1] = left;
    col[cur*4 + 2] = right;
    col[cur*4 + 3] = right;

    uv[cur*4]      = vec2(0,0);
    uv[cur*4 + 1]  = vec2(1,0);
    uv[cur*4 + 2]  = vec2(1,1);
    uv[cur*4 + 3]  = vec2(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::drawLine(vec2 start, vec2 end, float width, col4 color)
{
    if(cur >= SIZE - 1)
        render();
    if(current_program != color_program)
    {
        render();
        bind(color_program);
    }

    vec2 s = start;
    vec2 e = end;


    pos[cur*4]     = vec3(s.x(), s.y(), 0);
    pos[cur*4 + 1] = vec3(s.x() + width, s.y(), 0);
    pos[cur*4 + 2] = vec3(e.x() + width, e.y() + 1, 0);
    pos[cur*4 + 3] = vec3(e.x(), e.y(), 0);

    col[cur*4]     = color;
    col[cur*4 + 1] = color;
    col[cur*4 + 2] = color;
    col[cur*4 + 3] = color;

    uv[cur*4]      = vec2(0,0);
    uv[cur*4 + 1]  = vec2(1,0);
    uv[cur*4 + 2]  = vec2(1,1);
    uv[cur*4 + 3]  = vec2(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::render()
{
    if(cur == 0)
        return;
    glEnable(GL_BLEND);
    bind(current_program);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, vert_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*cur*4, &pos[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_VERTEX_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, col_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*cur*4, &uv[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), 0);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, uv_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(col4)*cur*4, &col[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_COLOR_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, sizeof(col4), 0);

    m_parent->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_b.bufferId());
    m_parent->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*cur*6, &index[0], GL_STREAM_DRAW);

    m_parent->glDrawElements(GL_TRIANGLES, cur*6, GL_UNSIGNED_INT, NULL);

    cur = 0;
    }

void SpriteBatch::setUniform(QMatrix4x4 mat)
{
    uni = mat;
}

void SpriteBatch::setScissor(vec2 loc, vec2 size)
{
    render();
    m_parent->glEnable(GL_SCISSOR_TEST);
    m_parent->glScissor(loc.x(), Settings::instance()->resolution.y() - (loc.y() + size.y()), size.x(), size.y());
}

void SpriteBatch::resetScissor()
{
    render();
    m_parent->glDisable(GL_SCISSOR_TEST);
}
