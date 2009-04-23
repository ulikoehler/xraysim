#ifndef XRAYGLWIDGET_H
#define XRAYGLWIDGET_H

#include <QGLWidget>

enum TransformationMode
{
    MODE_TRANSLATE,
    MODE_ROTATE,
    MODE_SCALE
};

class XRayGLWidget : public QGLWidget
{
    Q_OBJECT

 public:
     XRayGLWidget(QWidget *parent = 0);
     ~XRayGLWidget();

     QSize minimumSizeHint() const;
     QSize sizeHint() const;

     /**
      * Resets the modelview matrix and the transformation variables and updates the view
      */
     void resetView();

     /**
      * Sets a new transformation mode
      */
     void setTransformationMode(TransformationMode mode);

 public slots:
     void setXRotation(int angle);
     void setYRotation(int angle);
     void setZRotation(int angle);

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
    //Transformation variables
    TransformationMode transformationMode = MODE_ROTATE;
    float xRot, yRot, zRot;
    float xMov, yMov, zMov;
    float xScale, yScale, zScale;
    QPoint lastPos;
};

#endif // XRAYGLWIDGET_H
