#ifndef XRAYGLWIDGET_H
#define XRAYGLWIDGET_H


#define GL_GLEXT_PROTOTYPES

#include <tr1/memory>
#include <QGLWidget>
#include <QtGui>
#include "configurelightdialog.h"
#include "graphicsdialog.h"
#include "sobel.h"


//DEBUG
#include <cstdio>
using namespace std;
using namespace std::tr1;

/**
 * Enums
 */

enum SimulationMode
{
    SIM_MODE_TEXTURE_BLEND,
    SIM_MODE_PIXEL_CUBES,
    SIM_MODE_3D_SURFACE
};

enum TransformationMode
{
    MODE_TRANSLATE,
    MODE_ROTATE
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

     void setTransformationMode(TransformationMode mode);
     void setSimulationMode(SimulationMode mode);

     void setScale(int scalePercent);
     void setPixelCubeScale(float pixelCubeScale);

     void setInputFileList(QStringList newList);

     void setImageDistance(float distance);

 public slots:
     void setXRotation(int angle);
     void setYRotation(int angle);
     void setZRotation(int angle);

    /**
     * Light configuration slots
     */
    void ambientIntensityChanged(vec4f values);
    //Light 1
    void light1Toggled(bool enabled);
    void light1PositionChanged(vec4f values);
    void light1DirectionChanged(vec4f values);
    void light1AmbientChanged(vec4f values);
    void light1DiffuseChanged(vec4f values);
    void light1SpecularChanged(vec4f values);
    void light1AttenuationChanged(vec4f values);
    void light1ExponentChanged(float value);

    /**
     * Material configuration slots
     */
    void materialAmbientChanged(vec4f values);
    void materialDiffuseChanged(vec4f values);
    void materialSpecularChanged(vec4f values);
    void materialEmissionChanged(vec4f values);
    void materialShininessChanged(int value);

    /**
     * Other slots
     */
    //Connected to the alpha test dialog
    void alphaFuncChanged(uint mode, double value);
    void useAlphaChannelChanged(bool enabled);
    void toggleAlpha(bool enable);

    //Connected to the feature toggling dialog
    void featureToggled(uint feature, bool enabled);


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
    TransformationMode transformationMode;
    SimulationMode simulationMode;
    bool useAlphaChannel;
    bool alphaEnabled;
    double testRefVal; //Reference value for alpha and emulated-alpha test
    float xRot, yRot, zRot;
    float xMov, yMov, zMov;
    float scale; //Changed by the slider
    float pixelCubeScale; //Changed by the spinner
    float imageDistance; //z distance from one image to another
    QPoint lastPos;

    bool textureChanged; //True if the textures are to be updated; the have to be updated at the first call
    bool redrawPixelCubes; //Makes the display list to be re-initialized

    //Input properties
    QStringList inputFileList;

    //Private functions
    void renderTextureBlending();
    void render3dSurface();
    void renderPixelCubes();

    /**
     * OpenGL variables
     */
    //Display list IDs
    GLuint drawCubeListID;
    GLuint drawTexturedPlaneListID;

    GLuint drawPixelCubesListID; //Changed dynamically
    GLuint pixelCubesVBOID; //Vertex buffer object identifier for pixel cube mode

    GLuint *textures; //Array holding the texture IDs
    int texturesLength; //Length of textures array

    QImage **imageTextures; //Same as textures but used in pixel cube mode (QImage* is the type here -> dbl ptr)
    int imageTexturesLength; //Length of imageTextures
};

#endif // XRAYGLWIDGET_H
