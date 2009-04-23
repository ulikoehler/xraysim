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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resetViewButton_clicked()
{
    glWidget->resetView();
}

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
