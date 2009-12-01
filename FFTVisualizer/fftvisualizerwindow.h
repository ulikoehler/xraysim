#ifndef FFTVISUALIZERWINDOW_H
#define FFTVISUALIZERWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QFileDialog>
#include <QtGui/QImage>
#include <QtCore>

#include "ffttransformer.h"

namespace Ui
{
    class FFTVisualizerWindow;
}

class FFTVisualizerWindow : public QMainWindow
{
    Q_OBJECT

public:
    FFTVisualizerWindow(QWidget *parent = 0);
    ~FFTVisualizerWindow();

private:
    Ui::FFTVisualizerWindow *ui;
    QSharedPointer<QImage> image;

private slots:
    void on_goButton_clicked();
    void on_selectInputFilesButton_clicked();
    void setImage(QSharedPointer<QImage> image);
};

#endif // FFTVISUALIZERWINDOW_H
