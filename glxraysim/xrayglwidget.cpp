#include <QtGui>
#include <QtOpenGL>
#include <cstdlib>

#include <tr1/random>

using namespace std;

#include "xrayglwidget.h"

//Fwd declarations
inline void drawCube(const float color);

XRayGLWidget::XRayGLWidget(QWidget *parent) : QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    xMov = 0;
    yMov = 0;
    zMov = 0;

    scale = 1;
}

XRayGLWidget::~XRayGLWidget()
{
    makeCurrent();
}

void XRayGLWidget::resetView()
{
    xRot = 0;
    yRot = 0;
    zRot = 0;
    updateGL();
}

void XRayGLWidget::setTransformationMode(TransformationMode mode)
{
    this->transformationMode = mode;
}

void XRayGLWidget::setTransformationAxis(TransformationAxis axis)
{
    this->transformationAxis = axis;
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

void XRayGLWidget::setScale(int scalePercent)
{
    this->scale = scalePercent / 100.0;
    updateGL();
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

    if(transformationMode == MODE_ROTATE)
    {
        switch(transformationAxis)
        {
            case X_AXIS: {setXRotation(xRot + 4 * dx);break;}
            case Y_AXIS: {setYRotation(yRot + 4 * dy);break;}
            case Z_AXIS: {setZRotation(zRot + 4 * dy);break;}
        }
    }
    else if(transformationMode == MODE_TRANSLATE)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            xMov += 0.01 * dx;
            yMov += 0.01 * dy;
        }
        else if (event->buttons() & Qt::RightButton)
        {
            zMov += 0.01 * dy;
        }
        updateGL();
    }
    lastPos = event->pos();
}



/////////////////
//Painting code//
/////////////////

void XRayGLWidget::initializeGL()
{
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    const GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    const GLfloat lightSpecular[] = { 1, 1, 1, 1 };
    const GLfloat lightPosition[] = { 0,0,1,0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);
}

void XRayGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Apply the transformation parameters
    glScalef(scale, scale, scale);
    glTranslatef(xMov, yMov, zMov);
    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);
    //Draw the cubes
    drawCube(0.5);
}


inline void drawCube(const float color)
{
    glBegin(GL_TRIANGLE_STRIP);
        //Set the material
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS , 1);
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

    glBegin(GL_TRIANGLE_STRIP);
    //Draw the top
        glVertex3s(0,1,1);
        glVertex3s(0,1,0);
        glVertex3s(1,1,1);
        glVertex3s(1,1,0);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
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
    gluPerspective(60, height/width, 5, 100.0);
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
