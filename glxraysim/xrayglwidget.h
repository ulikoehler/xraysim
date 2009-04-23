#ifndef XRAYGLWIDGET_H
#define XRAYGLWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>

class XRayGlWidget : public QGLWidget
{
    public:
        XRayGlWidget();

    signals:
        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    protected:
        void initializeGL();
        void paintGL();
        void resizeGL(int width, int height);
        void mousePressEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);

    private:
        GLuint makeObject();
        void quad(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2,
                  GLdouble x3, GLdouble y3, GLdouble x4, GLdouble y4);
        void extrude(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
        void normalizeAngle(int *angle);

        GLuint object;
        int xRot;
        int yRot;
        int zRot;
        QPoint lastPos;
        QColor trolltechGreen;
        QColor trolltechPurple;

};

#endif // XRAYGLWIDGET_H
