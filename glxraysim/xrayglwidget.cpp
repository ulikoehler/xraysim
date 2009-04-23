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

    /*glTranslated(0.0, 0.0, -10.0);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);*/
}
