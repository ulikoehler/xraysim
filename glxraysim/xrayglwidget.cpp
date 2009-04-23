#include "xrayglwidget.h"

XRayGLWidget::XRayGLWidget(QWidget *parent) : QGLWidget(parent)
{
        xRot = 0;
        yRot = 0;
        zRot = 0;

}


void XRayGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void drawCube(const float color)
{
      glBegin(GL_TRIANGLE_STRIP);
      //Draw the side 'walls'
        glColor4f(color, color, color, color);
        //Front side
        glVertex3f(0.0,1.0,0.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(1.0,1.0,0.0);
        glVertex3f(1.0,0.0,0.0);
        //Right side
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,0.0,1.0);
        //Back side
        glVertex3f(0.0,1.0,1.0);
        glVertex3f(0.0,0.0,1.0);
        //Left side
        glVertex3f(0.0,1.0,0.0);
        glVertex3f(0.0,0.0,0.0);
      glEnd();
}

void XRayGLWidget::resizeGL(int width, int height)
{

}

QSize XRayGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize XRayGLWidget::sizeHint() const
{
    return QSize(400, 400);
}


void XRayGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glTranslated(1.0, 1.0, 5.0);
    glRotatef(45.0, 0.0, 1.0, 1.0);
    glScalef(0.3,0.3,0.3);
    drawCube(0.8);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
}
