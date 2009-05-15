#include "xrayglwidget.h"

//Global variables
const GLfloat null4f[] = {0,0,0,0};

//Macros
#define drawCube(color) glColor4f(color, color, color, color);glCallList(drawCubeListID)
#define drawCubeRaw() glCallList(drawCubeListID);


XRayGLWidget::XRayGLWidget(QWidget *parent) : QGLWidget(parent)
{
    //Initialize member variables
    xRot = 0;
    yRot = 0;
    zRot = 0;

    xMov = 0;
    yMov = 0;
    zMov = 0;

    scale = 1;
    pixelCubeScale = 1;

    transformationMode = MODE_ROTATE;
    simulationMode = SIM_MODE_TEXTURE_BLEND;
    useAlphaChannel = true;
    alphaEnabled = true;
    testRefVal = 0.0;

    textureChanged = true;
    redrawPixelCubes = true;

    texturesLength = 0;
    textures = 0;

    imageDistance = 10;

    imageTextures = 0;
    imageTexturesLength = 0;

    drawCubeListID = 0;
    drawTexturedPlaneListID = 0;
    drawPixelCubesListID = 0;
    pixelCubesVBOID = 0;
}

XRayGLWidget::~XRayGLWidget()
{
    makeCurrent();
    //Delete the display lists
    glDeleteLists(drawCubeListID, 2); //Alaos covers the textured plane drawing list

    //Delete the old pixel cube drawing list wif there is one
    if(drawPixelCubesListID > 0)
    {
        glDeleteLists(drawPixelCubesListID, 1);
    }

    //Delete the textures saved in the VRAM
    if(textures != 0)
    {
        for(int i = 0; i < texturesLength; i++)
        {
            deleteTexture(textures[i]);
        }
        //Delete the textures array
        delete textures;
    }
    //Do the same with the QImage textures
    if(imageTextures != 0)
    {
        for(int i = 0; i < imageTexturesLength; i++)
        {
            delete imageTextures[i];
        }
        //Delete the old textures array
        delete imageTextures;
    }
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
    updateGL();
}

void XRayGLWidget::setSimulationMode(SimulationMode mode)
{
    this->simulationMode = mode;
    //Enforce texture reload
    textureChanged = true;
    //Update the graphics
    updateGL();
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


void XRayGLWidget::setPixelCubeScale(float pixelCubeScale)
{
    this->pixelCubeScale = pixelCubeScale;
    redrawPixelCubes = true; //Force full redraw
}

void XRayGLWidget::setInputFileList(QStringList newList)
{
    inputFileList = newList;
    textureChanged = true;
}

void XRayGLWidget::setImageDistance(float distance)
{
    imageDistance = distance;
    redrawPixelCubes = true; //Force full redraw
}

///////////
//Signals//
///////////

void XRayGLWidget::ambientIntensityChanged(vec4f values)
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, values.data());
}

void XRayGLWidget::light1Toggled(bool enabled)
{
    if(enabled)
    {
        glEnable(GL_LIGHT0);
    }
    else
    {
       glDisable(GL_LIGHT0);
    }
}
void XRayGLWidget::light1PositionChanged(vec4f values)
{
    glLightfv(GL_LIGHT0, GL_POSITION, values.data());
    updateGL();
}
void XRayGLWidget::light1DirectionChanged(vec4f values)
{
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, values.data());
    updateGL();
}
void XRayGLWidget::light1AmbientChanged(vec4f values)
{
    glLightfv(GL_LIGHT0, GL_AMBIENT, values.data());
    updateGL();
}
void XRayGLWidget::light1DiffuseChanged(vec4f values)
{
    glLightfv(GL_LIGHT0, GL_DIFFUSE, values.data());
    updateGL();
}
void XRayGLWidget::light1SpecularChanged(vec4f values)
{
    glLightfv(GL_LIGHT0, GL_SPECULAR, values.data());
    updateGL();
}
void XRayGLWidget::light1AttenuationChanged(vec4f )//values)
{
    //TODO implement here and in the light config dialog
    updateGL();
}
void XRayGLWidget::light1ExponentChanged(float value)
{
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, value);
    updateGL();
}

void XRayGLWidget::alphaFuncChanged(uint mode, double value)
{
    glAlphaFunc(mode, value);
    testRefVal = value;
    updateGL();
}

//Material slots
void XRayGLWidget::materialAmbientChanged(vec4f values)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, values.data());
    redrawPixelCubes = true; //Force full redraw
    updateGL();
}
void XRayGLWidget::materialDiffuseChanged(vec4f values)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, values.data());
    redrawPixelCubes = true; //Force full redraw
    updateGL();
}
void XRayGLWidget::materialSpecularChanged(vec4f values)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, values.data());
    redrawPixelCubes = true; //Force full redraw
    updateGL();
}
void XRayGLWidget::materialEmissionChanged(vec4f values)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, values.data());
    redrawPixelCubes = true; //Force full redraw
    updateGL();
}
void XRayGLWidget::materialShininessChanged(int value)
{
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, value);
    redrawPixelCubes = true; //Force full redraw
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
    //Note: As the scaling matrix is applied BEFORE the rotation and translation,
    //  we don't have to involve the scale factors in the calculation
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();
    
    if(transformationMode == MODE_ROTATE)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            setXRotation(xRot + 4 * dy);
            setYRotation(yRot + 4 * dx);
        }
        else if (event->buttons() & Qt::RightButton)
        {
            setXRotation(xRot + 4 * dx);
            setZRotation(zRot + 4 * dy);
        }
    }
    else if(transformationMode == MODE_TRANSLATE)
    {
        if (event->buttons() & Qt::LeftButton)
        {
            xMov += 0.01/pixelCubeScale * dx;
            yMov -= 0.01/pixelCubeScale * dy;
        }
        else if (event->buttons() & Qt::RightButton)
        {
            zMov -= (0.01/pixelCubeScale) * dy;
        }
        updateGL();
    }
    lastPos = event->pos();
}

void XRayGLWidget::useAlphaChannelChanged(bool enabled)
{
    useAlphaChannel = enabled;
    textureChanged = true;
    redrawPixelCubes = true; //Force full redraw
    updateGL();
}

void XRayGLWidget::toggleAlpha(bool enable)
{
    alphaEnabled = enable;
    redrawPixelCubes = true; //Force full redraw
    updateGL();
}

void XRayGLWidget::featureToggled(uint feature, bool enabled)
{
    if(enabled)
    {
        glEnable(feature);
    }
    else
    {
        glDisable(feature);
    }    
    redrawPixelCubes = true; //Force full redraw
    updateGL();
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
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    glAlphaFunc ( GL_GREATER, 0.0);
    //glAlphaFunc(GL_ALWAYS, 1);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Set texture parameters
    const GLfloat texBorderColor[] = { 1, 1, 1, 0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, texBorderColor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);

    //Set material

    //Set ambient  to null (because the light source already emits ambient light)

    //const GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    const GLfloat global_ambient[] = {0,0,0,0};
    //const GLfloat global_ambient[] = {1,1,1,1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);


    //Set some material parameters (for the meshes, not for the light emitter
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS , 0);
    glMaterialf(GL_FRONT_AND_BACK, GL_SPECULAR, 0);
    glMaterialf(GL_FRONT_AND_BACK, GL_DIFFUSE, 0);
    glMaterialf(GL_FRONT_AND_BACK, GL_AMBIENT, 1);

    const GLfloat lightSpecular[] = {0,0,0,0};
    const GLfloat lightPosition[] = { 0,-30,0,0};
    const GLfloat lightDirection[] = {0,1,0};
    const GLfloat lightAmbient[] = {1,1,1,0};
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDirection);
    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, 90);

    /**
     * Initialize the display lists
     */
    //Initialize the cube generation list
    //(We initialize 2 at a time because the plain drawing list is the next)
    drawCubeListID = glGenLists(2);
    /*
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
            //Top
            glVertex3s(0,1,1);
            glVertex3s(0,1,0);
            glVertex3s(1,1,1);
            glVertex3s(1,1,0);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            //Bottom
            glVertex3s(0,0,0);
            glVertex3s(0,0,1);
            glVertex3s(1,0,0);
            glVertex3s(1,0,1);
        glEnd();
    glEndList();*/

    //Initialize the textured plane drawing list
    drawTexturedPlaneListID = drawCubeListID + 1;

    glNewList(drawTexturedPlaneListID,GL_COMPILE);
        glBegin(GL_TRIANGLE_STRIP);
                 glTexCoord2f(0,1); glVertex2f(-1,1); //lo
                 glTexCoord2f(0,0); glVertex2f(-1,-1); //lu
                 glTexCoord2f(1,1); glVertex2f(1,1);  //ru
                 glTexCoord2f(1,0); glVertex2f(1,-1); //ro
        glEnd();
    glEndList();
}


void XRayGLWidget::renderTextureBlending()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Apply the transformation parameters
    glScalef(scale, scale, scale);
    glTranslatef(xMov, yMov, zMov);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    //Set the color
    glColor3f(1,1,1);

    /**
     * If the texture file names have changed, update the textures
     * This is an extra loop to avoid time-consuming branching inside the GL-drawing loop
     */
    if(textureChanged)
    {
        if(textures != 0)
        {
            //We don't need the old textures any more so delete it
            for(int i = 0; i < texturesLength; i++)
            {
                deleteTexture(textures[i]);
            }
            //Delete the old textures array
            delete textures;
            //Initialize a new texture array;
            texturesLength = inputFileList.size();
        }

        textures = new GLuint[inputFileList.size()];

        for(int i = 0; i < inputFileList.size(); i++)
        {
            textures[i] = bindTexture(QPixmap(inputFileList[i]), GL_TEXTURE_2D);
        }
        //The texture doesn't have to be changed next time
        textureChanged = false;
    }

    for(int i = 0; i < texturesLength; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glCallList(drawTexturedPlaneListID);
        //Move along the z axis to draw the next textured plane later on
        glTranslatef(0,0,-imageDistance);
    }
}

void XRayGLWidget::render3dSurface()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Apply the transformation parameters
    glScalef(scale, scale, scale);
    glTranslatef(xMov, yMov, zMov);
    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    //Set the color
    glColor3f(1,1,1);

    if(inputFileList.length() == 0) {return;}

    QPointer<GraphicsDialog> graphicsDialog = new GraphicsDialog(this);

    shared_ptr<QImage> image(new QImage(inputFileList[0]));
    int h = image->height() / 2; //Integer division
    //Iterate the pixels at height startHeight
    //and calculate the sobel matrix for the surrounding values

    shared_ptr<QImage> sobelImage(new QImage(image->width(), image->height(), QImage::Format_RGB32));
    //std::list<struct Point> vertices;
    //Sobel sob(image);
    std::list<QPoint> vertices;
    const int rvalue = 10;

    //Search for edges from the left
    for(int y = 0; y < image->height(); y++)
    {
        for(int x = 1; x < image->width() - 1;x++)
        {
            if(qGray(image->pixel(x,y)) > rvalue)
            {
                vertices.push_back(QPoint(x,y));
                break;
            }
        }
    }
    //Search for edges from the right
    for(int y = image->height() - 1; y > 0; y--)
    {
        for(int x = image->width() - 1; x > 0;x--)
        {
            if(qGray(image->pixel(x,y)) > rvalue)
            {
                vertices.push_back(QPoint(x,y));

                break;
            }
        }
    }

    //bool found
    /*for(int x = image->width() - 1; x > 0;x--)
    {
        for(int y = image->height() - 1; y > 0; y--)
        {
            if(qGray(image->pixel(x,y)) > rvalue)
            {
                vertices.push_back(QPoint(x,y));
                break;
            }
        }
    }*/

    //Draw
    //glBegin(GL_QUADS);
    //glVertex2f(-0.5,0.5);
    //glVertex2f(-0.5,-0.5);
    //glVertex2f(0.5,0.5);
    //glVertex2f(0.5,-0.5);
    //glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(1,1,1);
    glLineWidth(5);
    glTranslatef(0,0,-25);
    list<QPoint>::iterator it;
    for( it=vertices.begin() ; it != vertices.end(); it++ )
    {
        //printf("%i %i \n", it->x(), it->y());
        //sobelImage->setPixel(it->x(), it->y(), 0xffffff);
        glVertex3f(it->x()/255, it->y()/255,0);
    }
    glEnd();

    //graphicsDialog->setImage(sobelImage);
    //graphicsDialog->show();
}

void XRayGLWidget::renderPixelCubes()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //Apply the transformation parameters
    glScalef(scale, scale, scale);
    glScalef(pixelCubeScale, pixelCubeScale, pixelCubeScale);
    glTranslatef(xMov, yMov, zMov);
    glRotated(xRot, 1.0, 0.0, 0.0);
    glRotated(yRot, 0.0, 1.0, 0.0);
    glRotated(zRot, 0.0, 0.0, 1.0);

    if(textureChanged)
    {
        //Delete the old textures if there are some loaded
        if(imageTextures != 0)
        {
            for(int i = 0; i < texturesLength; i++)
            {
                delete imageTextures[i];
            }
            //Delete the old textures array
            delete imageTextures;
            //Initialize a new texture array;
        }

        imageTextures = new QImage*[inputFileList.size()];
        imageTexturesLength = inputFileList.size();

        for(int i = 0; i < inputFileList.size(); i++)
        {
            if(useAlphaChannel)
            {
                imageTextures[i] = new QImage(QImage(inputFileList[i]).alphaChannel());
            }
            else
            {
                imageTextures[i] = new QImage(inputFileList[i]);
            }
        }
        //The texture doesn't have to be changed next time
        textureChanged = false;


    }

    //If the texture or another property has changed, the if statement is true and the model is redrawn
    if(textureChanged || redrawPixelCubes)
    {

        //Delete the old display list if there is one
        if(drawPixelCubesListID > 0)
        {
            glDeleteLists(drawPixelCubesListID, 1);
        }

        //Initialize the list
        drawPixelCubesListID = glGenLists(1);
        //Draw the cubes (to the list

        //uint bufferID;

        glNewList(drawPixelCubesListID, GL_COMPILE);
        //Test cube
        glCallList(drawCubeListID);
        ///////////////////////////////////////////

                glPointSize(1.0);
                glScalef(1,1,imageDistance);
                for(int i = 0; i < imageTexturesLength; i++)
                {
                    QImage* image = imageTextures[i];
                    glPushMatrix();
                    //Draw the rows
                    for(int y = 0; y < image->height(); y++)
                    {
                        //Extend the cubes to have a depth of imageDistance
                        glPushMatrix();
                        for(int x = 0; x < image->width(); x++)
                        {
                            float color = qGray(image->pixel(x,y)) / 255.0; //This may also be the alpha value
                            if(alphaEnabled)
                            {
                                if(color > testRefVal)
                                {
                                    glColor4f(color, color, color, color);
                                    glBegin(GL_POINTS);
                                    glVertex3s(0,0,0);
                                    glEnd();
                                }
                            }
                            else
                            {
                                if(color > testRefVal)
                                {
                                    glColor3f(color, color, color);
                                    glCallList(drawCubeListID);
                                }
                            }
                            glTranslatef(1,0,0);
                        }
                        glPopMatrix();
                        glTranslatef(0,1,0);
                    }
                    glPopMatrix();
                    glTranslatef(0,0,-1);
                }
        ///////////////////////////////////////////
        glEndList();
    }

    //Call the display list (renders the pixel cubes)
    glCallList(drawPixelCubesListID);


}

void XRayGLWidget::paintGL()
{
    switch(simulationMode)
    {
        case SIM_MODE_TEXTURE_BLEND: renderTextureBlending();break;
        case SIM_MODE_3D_SURFACE: render3dSurface();break;
        case SIM_MODE_PIXEL_CUBES: renderPixelCubes();break;
    }
}

void XRayGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, height/width, 0, 1500.0);
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

