#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    glWidget = new XRayGLWidget(ui->graphicsGroupBox);
    glWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //glDialog->//addWidget(glWidget,0);
    //glDialog
    glDialog->layout()->addWidget(glWidget);
    glDialog->show();
    //Set the default mode
    glWidget->setTransformationMode(MODE_ROTATE);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    if(checked) {glWidget->setSimulationMode(SIM_MODE_PIXEL_CUBES);}
}

void MainWindow::on_textureBlendModeRadioButton_toggled(bool checked)
{
    if(checked) {glWidget->setSimulationMode(SIM_MODE_TEXTURE_BLEND);}
}

void MainWindow::on_selectInputFilesButton_clicked()
{
    inputFileDialog->exec();
    glWidget->setInputFileList(inputFileDialog->selectedFiles());
}

void MainWindow::on_imageDistanceComboBox_valueChanged(double value)
{
    glWidget->setImageDistance(value);
    glWidget->updateGL();
}
