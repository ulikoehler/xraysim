#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    //Create a new GL widget and put it into the graphics box
    glWidget = new XRayGLWidget(ui->graphicsGroupBox);
    glWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(glWidget, 0);
    ui->graphicsGroupBox->setLayout(hbox);
    //Set the default mode
    glWidget->setTransformationMode(MODE_ROTATE);

   //connect(ui->scaleDial,
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
    glWidget->setSimulationMode(SIM_MODE_PIXEL_CUBES);
}

void MainWindow::on_textureBlendModeRadioButton_toggled(bool checked)
{
    glWidget->setSimulationMode(SIM_MODE_TEXTURE_BLEND);
}
