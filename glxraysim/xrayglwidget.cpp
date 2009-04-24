#include <QtGui>
#include <QtOpenGL>
#include <cstdlib>

#include <tr1/random>

//Macros
#define drawCube(color) glColor4f(color, color, color, color);glCallList(drawCubeListID);

using namespace std;
using namespace std::tr1;

#include "xrayglwidget.h"

XRayGLWidget::XRayGLWidget(QWidget *parent) : QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

    xMov = 0;
    yMov = 0;
    zMov = 0;

    baseScale = 0.01;
    scale = baseScale;
}

XRayGLWidget::~XRayGLWidget()
{
    makeCurrent();
    //Delete the display lists
    glDeleteLists(drawCubeListID, 1);
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

void XRayGLWidget::setScale(int scalePercentValue)
{
    scalePercent = scalePercentValue;
    this->scale = (scalePercent / 100.0) * baseScale;
    updateGL();
}

void XRayGLWidget::setBaseScale(double baseScaleValue)
{
    baseScale = baseScaleValue;
    this->scale = (scalePercent / 100.0) * baseScale;
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
    }
    else if(transformationMode == MODE_TRANSLATE)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            xMov += (0.01/scale) * dx;
            yMov -= (0.01/scale) * dy;
        }
        else if (event->buttons() & Qt::RightButton)
        {
            zMov -= (0.01/scale) * dy;
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
    //Set the background color
    qglClearColor(Qt::black);

    //Enable the required featuresg
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    const GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    const GLfloat lightSpecular[] = { 1, 1, 1, 1 };
    const GLfloat lightPosition[] = { 0,0,-10,1};
    const GLfloat lightDirection[] = {0,0,1};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 90);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE);

    /**
     * Initialize the display lists
     */
    //Initialize the cube generation list
    drawCubeListID = glGenLists(1);

    glNewList(drawCubeListID, GL_COMPILE);
        glBegin(GL_TRIANGLE_STRIP);
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
            glVertex3s(0,0,0);
            glVertex3s(0,0,1);
            glVertex3s(1,0,0);
            glVertex3s(1,0,1);
        glEnd();
    glEndList();

}

void XRayGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Add the light
    glTranslatef(0,0,-10);
    glMateriali(GL_FRONT_AND_BACK, GL_EMISSION, 1);
    drawCube(0);
    glMaterialf(GL_FRONT_AND_BACK, GL_EMISSION, 0);
    glLoadIdentity();
    //Set some material parameters (for the meshes, not for the light emitter
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS , 1);
    //Apply the transformation parameters
    glScalef(scale, scale, scale);
    glTranslatef(xMov, yMov, zMov);
    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);
    //Draw the cubes
    mt19937 rng(time(0));
    for(int i = 0; i < 100; i++) //x loop
    {
        glPushMatrix();
            for(int j = 0; j < 100; j++)//y lopp
            {
                drawCube((rng() % 9) * 0.1);
                glTranslatef(0,1,0);
            }
        glPopMatrix();
        glTranslatef(1,0,0);
    }
    drawCube(0.4);
    glTranslatef(0,1,0.1);
    drawCube(0.8);
    //glTranslatef(1.0
}

void XRayGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glTranslatef(0,0,5);
    gluPerspective(90, height/width, 0.1, 100.0);
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
