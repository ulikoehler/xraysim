#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass), glDialog(new gldialog)
{
    ui->setupUi(this);
    //Initialize the member dialogs
    inputFileDialog = new QFileDialog(this, "Select input files");
    inputFileDialog->setFileMode(QFileDialog::ExistingFiles); //Allow multiple file selection

    /**
     * Initialize the GL widget
     */
    glWidget = new XRayGLWidget(glDialog);
    glWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    glDialog->setGLWidget(glWidget);
    glDialog->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    int ret = QMessageBox::question(this, tr("Quit GLXRaySim?"),
                                   tr("Do you really want to quit GLXRaySim?"),
                                   QMessageBox::Yes | QMessageBox::No);
    if(ret == QMessageBox::Yes)
    {
        QApplication::quit();
    }
    else {event->ignore();}
}

void MainWindow::on_resetViewButton_clicked()
{
    glWidget->resetView();
}
///////////////////////
//Transformation mode//
///////////////////////

void MainWindow::on_translateModeRadioButton_toggled(bool checked)
{
    if(checked) {glWidget->setTransformationMode(MODE_TRANSLATE);}
}

void MainWindow::on_rotateModeRadioButton_toggled(bool checked)
{
    if(checked) {glWidget->setTransformationMode(MODE_ROTATE);}
}

///////////////////////
//Transformation axis//
///////////////////////

void MainWindow::on_scaleSlider_valueChanged(int value)
{
    glWidget->setScale(value);
}

void MainWindow::on_pixelCubesModeRadioButton_toggled(bool checked)
{
    if(checked)
    {
        glWidget->setSimulationMode(SIM_MODE_PIXEL_CUBES); //Set the simulation mode
        glWidget->setPixelCubeScale(1.0/(ui->pixelCubeScaleSpinner->value())); //Update the pixel cube scale
    }
}

void MainWindow::on_textureBlendModeRadioButton_toggled(bool checked)
{
    if(checked)
    {
        glWidget->setSimulationMode(SIM_MODE_TEXTURE_BLEND); //Set the simulation mode
        glWidget->setPixelCubeScale(1); //The pixel cube scale is multiplied with other variables when transforming, so set it to 1
    }
}

void MainWindow::on_selectInputFilesButton_clicked()
{
    inputFileDialog->exec();
    inputFileNameList = inputFileDialog->selectedFiles();
    glWidget->setInputFileList(inputFileNameList);
}

void MainWindow::on_imageDistanceComboBox_valueChanged(double value)
{
    glWidget->setImageDistance(value);
    glWidget->updateGL();
}

void MainWindow::on_pixelCubeScaleSpinner_valueChanged(int value)
{
    glWidget->setPixelCubeScale(1.0/value);
}

void MainWindow::on_exitAction_triggered()
{
    QApplication::quit();
}

void MainWindow::on_simpleSumUpAction_triggered()
{
    //Declare an array of QImage pointers
    int inputLen = inputFileNameList.size();
    QImage** images = new QImage*[inputLen];

    int height = -1; //-1 indicates that the first image has not been read yet
    int width = -1; //-1 indicates that the first image has not been read yet
    for(int i = 0; i < inputLen; i++)
    {
        images[i] = new QImage(inputFileNameList[i]);
        //Set the height and width if this is the first image
        if(width == -1) {width = images[i]->width();}
        if(height == -1) {height = images[i]->height();}

        /**
         * Check if the height and width of this image
         * is equal to the first images
         * (Overall effect: Check if all images have equal geometry)
         */
        if((images[i]->width() != width) || (images[i]->height() != height))
        {
            QMessageBox::critical(this, tr("Image size error"),
                                   tr("The selected images don't have a common width and height!"));
            return;
        }
    }

    //Arrays and pixel coordinates start from 0
    width -= 1;
    height -= 1;

    //Initialize an array to hold the sum values
    uint* matrix = new uint[width * height];
    //Set all values in the matrix to 0
    for(int i = 0; i < (width * height); i++)
    {
        matrix[i] = 0;
    }

    for(int i = 0; i < inputLen; i++)
    {
        for(int h = 0; h < height;h++)
        {
            for(int w = 0; w < width; w++)
            {
                //Add the pixel's gray value to the appropriate matrix value
                matrix[h * width + w] = matrix[h * width + w] + qAlpha(images[i]->pixel(w, h));
            }
        }
    }
    //for(int i = 0; i<(width*height);i++)
    //{printf("%i ",matrix[i]);}


    //Set the pixels of the result images to the values (relative to the maximum)
    QImage resultImage(QImage(width, height, QImage::Format_ARGB32));
    for(int h = 0; h < height;h++)
        {
            for(int w = 0; w < width; w++)
            {
                //TODO Check if ceil is appropriate here
                int val = matrix[h * width + w] / (float)inputLen;
                cout << val << " ";
                resultImage.setPixel(w, h, qRgba(val, val, val, 255-val));
            }
        }

    GraphicsDialog* graphicsDialog = new GraphicsDialog(this);
    graphicsDialog->setImage(resultImage);
    graphicsDialog->show();

    //Delete the images and the ptr array
    for(int i = 0; i < inputFileNameList.length(); i++)
    {
        delete images[i];
    }
    delete images;
}
