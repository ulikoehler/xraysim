#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    //Create a new GL widget and put it into the graphics box
    glWidget = new XRayGLWidget(ui->groupBox);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(glWidget, 0);
    ui->groupBox->setLayout(hbox);
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

void MainWindow::on_scaleModeRadioButton_clicked(bool checked)
{
    if(checked) {glWidget->setTransformationMode(MODE_SCALE);}
}

///////////////////////
//Transformation axis//
///////////////////////

void MainWindow::on_xAxisRadioButton_toggled(bool checked)
{

    if(checked) {glWidget->setTransformationAxis(X_AXIS);}
}

void MainWindow::on_yAxisRadioButton_toggled(bool checked)
{

    if(checked) {glWidget->setTransformationAxis(Y_AXIS);}
}

void MainWindow::on_zAxisRadioButton_toggled(bool checked)
{

    if(checked) {glWidget->setTransformationAxis(Z_AXIS);}
}
