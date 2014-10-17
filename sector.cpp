#include "sector.h"

#define XY(x,y)(x*RY + y)
#define BACK QVector3D(0, 0, -1)
#define DOWN QVector3D(0, -1, 0)
#define FORWARD QVector3D(0, 0, 1)
#define LEFT QVector3D(-1, 0, 0)
#define ONE QVector3D(1, 1, 1)
#define RIGHT QVector3D(1, 0, 0)
#define UP QVector3D(0, 1, 0)
#define ZERO QVector3D(0, 0, 0)

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

void AddBlockGeom(int i, int j)
{

}

void Sector::Rebuild(GLWidget *parent)
{
    auto comp_off = offset*QVector3D(RX, 0, RY);
    for(int i =0;i<RX;i++)
        for(int j=0;j<RY;j++)
        {
            auto block_data = m_blocks[XY(i,j)].data();
            auto m_source = JAtlas::instance()->sources[block_data->texture()];

            int last = geom.size();

            geom.push_back(Vertex(comp_off + QVector3D(i, 0, j), UP, QVector2D()));
            geom.push_back(Vertex(comp_off + QVector3D(i + 1, 0, j), UP, QVector2D()));
            geom.push_back(Vertex(comp_off + QVector3D(i, 0, j + 1), UP, QVector2D()));
            geom.push_back(Vertex(comp_off + QVector3D(i + 1, 0, j + 1), UP, QVector2D()));

            indeces.push_back(last);
            indeces.push_back(last + 1);
            indeces.push_back(last + 2);
            indeces.push_back(last + 1);
            indeces.push_back(last + 3);
            indeces.push_back(last + 2);
        }

    m_vao = new QOpenGLVertexArrayObject( this );
    m_vao->create();
    m_vao->bind();

    parent->program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    parent->program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    parent->program->setAttributeArray(PROGRAM_VERTEX_ATTRIBUTE, GL_FLOAT, geom.constData(), 3, sizeof(Vertex));
    parent->program->setAttributeBuffer(PROGRAM_TEXCOORD_ATTRIBUTE, GL_FLOAT, sizeof(QVector3D), 2, sizeof(Vertex));
}

Sector::Sector() :
    m_vao(nullptr)
{
    m_blocks = new Block[RXYZ];
}

Sector::~Sector()
{
    delete[] m_blocks;
    m_blocks = nullptr;
    if(m_vao)
    {
        delete m_vao;
        m_vao = nullptr;
    }
}

void Sector::render(GLWidget *parent)
{
    QMatrix4x4 m;
    m.ortho(-0.5f, +0.5f, +0.5f, -0.5f, 4.0f, 15.0f);
    m.translate(0.0f, 0.0f, -10.0f);

    parent->program->setUniformValue("matrix", m);

    glDrawElements(GL_TRIANGLE_FAN, geom.size(), GL_UNSIGNED_INT, indeces.constData());
}

void Sector::setBlock(int x, int y, const QString &id)
{
    auto temp = BlockDataBase::getBlockData(id);
    m_blocks[XY(x,y)].data(temp);
}

void Sector::setBlock(int x, int y, const Block &block)
{

}

const Block *Sector::getBlock(int x, int y) const
{
    return &m_blocks[XY(x,y)];
}
