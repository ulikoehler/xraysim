#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    glWidget = new XRayGLWidget(ui->groupBox);
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(glWidget);
    hbox->addStretch(1);
    ui->groupBox->setLayout(hbox);
}

MainWindow::~MainWindow()
{
    delete ui;
}
