#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
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
    void on_zAxisRadioButton_toggled(bool checked);
    void on_yAxisRadioButton_toggled(bool checked);
    void on_xAxisRadioButton_toggled(bool checked);
    void on_scaleModeRadioButton_clicked(bool checked);
    void on_rotateModeRadioButton_toggled(bool checked);
    void on_translateModeRadioButton_toggled(bool checked);
    void on_resetViewButton_clicked();
};

#endif // MAINWINDOW_H
