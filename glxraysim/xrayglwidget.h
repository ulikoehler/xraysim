#ifndef XRAYGLWIDGET_H
#define XRAYGLWIDGET_H

#include <QtOpenGL>
#include <QGLWidget>

class XRayGLWidget : public QGLWidget
{
public:
    XRayGLWidget(QWidget *parent);

//signals:
//    void xRotationChanged(int angle);
//    void yRotationChanged(int angle);
//    void zRotationChanged(int angle);

QSize minimumSizeHint() const;
QSize sizeHint() const;


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);


private:

    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;

};

#endif // XRAYGLWIDGET_H
