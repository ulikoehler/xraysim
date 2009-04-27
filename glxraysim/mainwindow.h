#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QFileDialog>
#include "xrayglwidget.h"

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
    XRayGLWidget *glWidget;

private slots:
    void on_selectInputFilesButton_clicked();
    void on_textureBlendModeRadioButton_toggled(bool checked);
    void on_pixelCubesModeRadioButton_toggled(bool checked);
    void on_scaleSlider_valueChanged(int value);
    void on_rotateModeRadioButton_toggled(bool checked);
    void on_translateModeRadioButton_toggled(bool checked);
    void on_resetViewButton_clicked();

private:
    QFileDialog *inputFileDialog;
};

#endif // MAINWINDOW_H
