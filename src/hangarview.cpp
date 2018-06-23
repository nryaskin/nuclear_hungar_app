#include "hangarview.h"
#include <QOpenGLShaderProgram>
#include <QString>
#include <QDebug>
#include "vertex.h"
#include <math.h>
#include <QtWidgets>
#include "camera.h"

//FLOOR sizes in mm
#define FLOOR_LENGTH 36000.0f
#define FLOOR_WIDTH  12000.0f
#define FLOOR_HEIGHT 250.0f

//CUBEsizes in mm
#define CUBE_LENGTH 1650.0f
#define CUBE_WIDTH  1650.0f
#define CUBE_HEIGHT 1375.0f


// Front CUBE Verticies
#define VERTEX_FTR Vertex( QVector3D( CUBE_LENGTH/2,  CUBE_HEIGHT/2,  CUBE_WIDTH/2),\
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define VERTEX_FTL Vertex( QVector3D( -CUBE_LENGTH/2,  CUBE_HEIGHT/2,  CUBE_WIDTH/2),\
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define VERTEX_FBL Vertex( QVector3D( -CUBE_LENGTH/2, -CUBE_HEIGHT/2,  CUBE_WIDTH/2),\
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define VERTEX_FBR Vertex( QVector3D( CUBE_LENGTH/2, -CUBE_HEIGHT/2,  CUBE_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back CUBE Verticies
#define VERTEX_BTR Vertex( QVector3D( CUBE_LENGTH/2,  CUBE_HEIGHT/2, -CUBE_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define VERTEX_BTL Vertex( QVector3D(-CUBE_LENGTH/2,  CUBE_HEIGHT/2, -CUBE_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_BBL Vertex( QVector3D(-CUBE_LENGTH/2, -CUBE_HEIGHT/2, -CUBE_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 1.0f ) )
#define VERTEX_BBR Vertex( QVector3D( CUBE_LENGTH/2, -CUBE_HEIGHT/2, -CUBE_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 0.0f ) )


// Front Floor Verticies
#define F_VERTEX_FTR Vertex( QVector3D( FLOOR_LENGTH/2,  FLOOR_HEIGHT/2,  FLOOR_WIDTH/2),\
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define F_VERTEX_FTL Vertex( QVector3D( -FLOOR_LENGTH/2,  FLOOR_HEIGHT/2,  FLOOR_WIDTH/2),\
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define F_VERTEX_FBL Vertex( QVector3D( -FLOOR_LENGTH/2, -FLOOR_HEIGHT/2,  FLOOR_WIDTH/2),\
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define F_VERTEX_FBR Vertex( QVector3D( FLOOR_LENGTH/2, -FLOOR_HEIGHT/2,  FLOOR_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 0.0f ) )

// Back Floor Verticies
#define F_VERTEX_BTR Vertex( QVector3D( FLOOR_LENGTH/2,  FLOOR_HEIGHT/2, -FLOOR_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 0.0f ) )
#define F_VERTEX_BTL Vertex( QVector3D(-FLOOR_LENGTH/2,  FLOOR_HEIGHT/2, -FLOOR_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 1.0f ) )
#define F_VERTEX_BBL Vertex( QVector3D(-FLOOR_LENGTH/2, -FLOOR_HEIGHT/2, -FLOOR_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 1.0f ) )
#define F_VERTEX_BBR Vertex( QVector3D( FLOOR_LENGTH/2, -FLOOR_HEIGHT/2, -FLOOR_WIDTH/2), \
                             QVector3D( 0.0f, 0.0f, 0.0f ) )

static const Vertex sg_floor_vertexes[] = {
    // Face 1 (Front)
      F_VERTEX_FTR, F_VERTEX_FTL, F_VERTEX_FBL,
      F_VERTEX_FBL, F_VERTEX_FBR, F_VERTEX_FTR,
    // Face 2 (Back)
      F_VERTEX_BBR, F_VERTEX_BTL, F_VERTEX_BTR,
      F_VERTEX_BTL, F_VERTEX_BBR, F_VERTEX_BBL,
    // Face 3 (Top)
      F_VERTEX_FTR, F_VERTEX_BTR, F_VERTEX_BTL,
      F_VERTEX_BTL, F_VERTEX_FTL, F_VERTEX_FTR,
    // Face 4 (Bottom)
      F_VERTEX_FBR, F_VERTEX_FBL, F_VERTEX_BBL,
      F_VERTEX_BBL, F_VERTEX_BBR, F_VERTEX_FBR,
    // Face 5 (Left)
      F_VERTEX_FBL, F_VERTEX_FTL, F_VERTEX_BTL,
      F_VERTEX_FBL, F_VERTEX_BTL, F_VERTEX_BBL,
    // Face 6 (Right)
      F_VERTEX_FTR, F_VERTEX_FBR, F_VERTEX_BBR,
      F_VERTEX_BBR, F_VERTEX_BTR, F_VERTEX_FTR
};

// Create a colored cube
static const Vertex sg_cube_vertexes[] = {
  // Face 1 (Front)
    VERTEX_FTR, VERTEX_FTL, VERTEX_FBL,
    VERTEX_FBL, VERTEX_FBR, VERTEX_FTR,
  // Face 2 (Back)
    VERTEX_BBR, VERTEX_BTL, VERTEX_BTR,
    VERTEX_BTL, VERTEX_BBR, VERTEX_BBL,
  // Face 3 (Top)
    VERTEX_FTR, VERTEX_BTR, VERTEX_BTL,
    VERTEX_BTL, VERTEX_FTL, VERTEX_FTR,
  // Face 4 (Bottom)
    VERTEX_FBR, VERTEX_FBL, VERTEX_BBL,
    VERTEX_BBL, VERTEX_BBR, VERTEX_FBR,
  // Face 5 (Left)
    VERTEX_FBL, VERTEX_FTL, VERTEX_BTL,
    VERTEX_FBL, VERTEX_BTL, VERTEX_BBL,
  // Face 6 (Right)
    VERTEX_FTR, VERTEX_FBR, VERTEX_BBR,
    VERTEX_BBR, VERTEX_BTR, VERTEX_FTR
};

#undef VERTEX_BBR
#undef VERTEX_BBL
#undef VERTEX_BTL
#undef VERTEX_BTR

#undef VERTEX_FBR
#undef VERTEX_FBL
#undef VERTEX_FTL
#undef VERTEX_FTR

#undef F_VERTEX_FTR
#undef F_VERTEX_FTL
#undef F_VERTEX_FBL
#undef F_VERTEX_FBR

#undef F_VERTEX_BTR
#undef F_VERTEX_BTL
#undef F_VERTEX_BBL
#undef F_VERTEX_BBR





HangarView::HangarView()
{
    setFocusPolicy(Qt::StrongFocus);
    m_transformation.translate(0.0f, 0.0f, -12000.0f/2);
    QVector3D CameraPos(1.0f, 1.0f, -12000.0f);
    QVector3D CameraTarget(0.45f, 0.0f, 1.0f);
    QVector3D CameraUp(0.0f, 1.0f, 0.0f);
    Camera cam(18000, 16000);
    m_transformation.setCamera(cam);
    //m_transformation.scale(0.5f);
}

void HangarView::addContainerClicked()
{
     QMessageBox msgBox;
     msgBox.setWindowTitle("MessageBox Title");
     msgBox.setText("You Clicked "+ ((QPushButton*)sender())->text());
     msgBox.exec();

     i++;
     j++;
}
//User enteractions event handlers
void HangarView::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    m_transformation.camera().onMouseMove(mouseEvent->x(), mouseEvent->y());
}

void HangarView::keyPressEvent(QKeyEvent *k)
{
     m_transformation.camera().onKeyboard(k->key());
}

void HangarView::mousePressEvent(QMouseEvent *mouseEvent){
    m_transformation.camera().mousePos().setX(mouseEvent->x());
    m_transformation.camera().mousePos().setY(mouseEvent->y());
}

HangarView::~HangarView()
{
    makeCurrent();
    tearDown();
}

void HangarView::setGWorld()
{
    int gWorldLocation = m_program->uniformLocation("gWorld");
    static float Scale = 0.0f;
    Scale = 1.5707f;
    m_transformation.setRotation(-4.0f * Scale, QVector3D(sinf(Scale) * 90.0f, 0.0f, 0.0f));
    m_transformation.setPerspectiveProj(45.0f, this->width(), this->height(), 0.0f, 100000.0f);
    m_program->setUniformValue(gWorldLocation, m_transformation.toMatrix());
}

void HangarView::renderSceneCB()
{
    m_transformation.camera().onRender();
    makeCurrent();
    m_program->bind();
    {
         setGWorld();
    }
    m_program->release();
}

void HangarView::initializeGL()
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(renderSceneCB()));
    connect(this, SIGNAL(frameSwapped()), this, SLOT(update()));
    initializeOpenGLFunctions();
    // Set global information
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
    {
        // Create Shader (Do not release until VAO is created)

        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/simple.vert");
        m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simple.frag");
        m_program->link();
        m_program->bind();

        //setting world global matrix
        setGWorld();

        // Create Buffer (Do not release until VAO is created)
        m_vertex.create();
        m_vertex.bind();
        m_vertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
        m_vertex.allocate(sg_floor_vertexes, sizeof(sg_floor_vertexes));
        // Create Vertex Array Object
        m_object.create();
        m_object.bind();
        m_program->enableAttributeArray(0);
        m_program->enableAttributeArray(1);
        m_program->setAttributeBuffer(0, GL_FLOAT, Vertex::positionOffset(), Vertex::PositionTupleSize, Vertex::stride());
        m_program->setAttributeBuffer(1, GL_FLOAT, Vertex::colorOffset(), Vertex::ColorTupleSize, Vertex::stride());

        // Release (unbind) all
        m_object.release();
        m_vertex.release();
        m_program->release();
    }
    timer->start(1);
}

void HangarView::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_program->bind();
    {
        m_object.bind();
        glDrawArrays(GL_TRIANGLES, 0, sizeof(sg_floor_vertexes) / sizeof(sg_floor_vertexes[0]));
        m_object.release();
    }
    m_program->release();
}

void HangarView::resizeGl(int width, int height)
{
    m_transformation.camera().setWindowHeight(height);
    m_transformation.camera().setWindowWidth(width);
    m_transformation.setPerspectiveProj(45.0f, width, height, 0.0f, 10.0f);
}

void HangarView::tearDown()
{
    m_object.destroy();
    m_vertex.destroy();
    delete m_program;
}
