#include <QtGui>
#include <QtOpenGL>
#include <cstdlib>

#include "xrayglwidget.h"

//Fwd declarations
inline void drawCube(const float color);

XRayGLWidget::XRayGLWidget(QWidget *parent) : QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

XRayGLWidget::~XRayGLWidget()
{
    makeCurrent();
}

void XRayGLWidget::resetView()
{
    xRot = 0;
    yRot = 0;
}

/////////////////
//Rotation code//
/////////////////

inline int normalizeAngle(int angle)
{
    int ret = angle % 360;
    if(ret < 0) {ret *= (-1);}
    return ret;
}
void XRayGLWidget::setXRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != xRot)
    {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void XRayGLWidget::setYRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != yRot)
    {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void XRayGLWidget::setZRotation(int angle)
{
    normalizeAngle(angle);
    if (angle != zRot)
    {
        zRot = angle;
        emit zRotationChanged(angle);
        updateGL();
    }
}


////////////////////
//Mouse event code//
////////////////////

void XRayGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}


void XRayGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}



/////////////////
//Painting code//
/////////////////

void XRayGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    const GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    const GLfloat lightSpecular[] = { 1, 1, 1, 1 };
    const GLfloat lightPosition[] = { 0,0,1,0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void XRayGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Add the lights
    //glTranslated(-1.0, -1.0, -5.0);
    glScaled(0.5,0.5,0.5);
    glRotatef(45.0, 0.0, 1.0, 1.0);
    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);
    //Draw the cubes
    drawCube(0.8);
}


inline
void drawCube(const float color)
{
    glBegin(GL_QUAD_STRIP);
        //Set the material
        glMaterialf(GL_FRONT_AND_BACK,GL_SPECULAR, 0.8);
        //Draw the side 'walls'
        glColor4f(color, color, color, color);
        //Front side
        glVertex3s(0,1,0);
        glVertex3s(0,0,0);
        glVertex3s(1,1,0);
        glVertex3s(1,0,0);
        //Right side
        glVertex3s(1,1,1);
        glVertex3s(1,0,1);
        //Back side
        glVertex3s(0,1,1);
        glVertex3s(0,0,1);
        //Left side
        glVertex3s(0,1,0);
        glVertex3s(0,0,0);
    glEnd();
    //Draw the top and the bottom
    glBegin(GL_QUADS);
        //Draw the top
        glVertex3s(0,1,1);
        glVertex3s(0,1,0);
        glVertex3s(1,1,1);
        glVertex3s(1,1,0);
        //Draw the bottom
        glVertex3s(1,0,0);
        glVertex3s(1,0,1);
        glVertex3s(0,0,0);
        glVertex3s(0,0,1);
    glEnd();
}

void XRayGLWidget::resizeGL(int width, int height)
{
        int side = qMin(width, height);
        glViewport((width - side) / 2, (height - side) / 2, side, side);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glOrtho(-10, +10, +10, -10, 0.1, 25.0);
        glMatrixMode(GL_MODELVIEW);

}

QSize XRayGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize XRayGLWidget::sizeHint() const
{
    return QSize(400, 400);
}
