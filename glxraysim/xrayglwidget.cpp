#include "xrayglwidget.h"

XRayGLWidget::XRayGLWidget() : QGLWidget(parent)
{
        object = 0;
        xRot = 0;
        yRot = 0;
        zRot = 0;

}
    GLWidget::~GLWidget()
    {
        makeCurrent();
        glDeleteLists(object, 1);
    }



    void GLWidget::initializeGL()
    {
        qglClearColor(trolltechPurple.dark());
        object = makeObject();
        glShadeModel(GL_FLAT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        
    }

    void GLWidget::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslated(0.0, 0.0, -10.0);
        glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
        glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
        glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
        glCallList(object);
    }
