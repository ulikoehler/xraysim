#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    //Create a new GL widget and put it into the graphics box
    glWidget = new XRayGLWidget(ui->groupBox);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(glWidget);
    hbox->addStretch(1);
    ui->groupBox->setLayout(hbox);
    //Connect the GL widget signals
    connect(ui->xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    connect(glWidget, SIGNAL(xRotationChanged(int)), ui->xSlider, SLOT(setValue(int)));
    connect(ui->ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    connect(glWidget, SIGNAL(yRotationChanged(int)), ui->ySlider, SLOT(setValue(int)));
    connect(ui->zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
    connect(glWidget, SIGNAL(zRotationChanged(int)), ui->zSlider, SLOT(setValue(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
