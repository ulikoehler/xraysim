#include "fftvisualizerwindow.h"
#include "ui_fftvisualizerwindow.h"

FFTVisualizerWindow::FFTVisualizerWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::FFTVisualizerWindow)
{
    ui->setupUi(this);
}

FFTVisualizerWindow::~FFTVisualizerWindow()
{
    delete ui;
}

void FFTVisualizerWindow::setImage(QSharedPointer<QImage> img)
{
    image = img;
    ui->imageLabel->setPixmap(QPixmap::fromImage(*img.data()));
    repaint();
}

void FFTVisualizerWindow::on_selectInputFilesButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open image"), ".", 0);
    setImage(QSharedPointer<QImage>(new QImage(filename)));
}


void FFTVisualizerWindow::on_goButton_clicked()
{
    if(ui->directionForwardRadioButton->isChecked())
    {setImage(FFTTransformer::transformOne(image, FFTTransformer::FORWARD));}
    else
    {

    setImage(FFTTransformer::transformOne(image, FFTTransformer::INVERSE));
    }
}
