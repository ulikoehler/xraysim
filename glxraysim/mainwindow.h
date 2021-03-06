#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QSharedPointer>
#include "xrayglwidget.h"
#include "gldialog.h"
#include "configurelightdialog.h"
#include "graphicsdialog.h"
#include "alphatestdialog.h"
#include "configurematerialdialog.h"
#include "togglefeaturesdialog.h"

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

protected:
     void closeEvent(QCloseEvent* event);

private slots:
    void on_setAlphaExponentAction_triggered();
    void on_surfaceRadioButton_toggled(bool checked);
    void on_toggleFeaturesAction_triggered();
    void on_actionMaterial_properties_triggered();
    void on_textureBlendModeRadioButton_toggled(bool checked);
    void on_pixelCubesModeRadioButton_toggled(bool checked);
    void on_rotateModeRadioButton_toggled(bool checked);
    void on_translateModeRadioButton_toggled(bool checked);
    void on_alphaTestAction_triggered();
    void on_lightPropertiesAction_triggered();
    void on_simpleSumUpAction_triggered();
    void on_exitAction_triggered();
    void on_pixelCubeScaleSpinner_valueChanged(int );
    void on_imageDistanceComboBox_valueChanged(double );
    void on_selectInputFilesButton_clicked();
    void on_scaleSlider_valueChanged(int value);
    void on_resetViewButton_clicked();

private:
    Ui::MainWindowClass *ui;
    //Dialogs
    QPointer<gldialog> glDialog;
    QPointer<XRayGLWidget> glWidget;
    QPointer<ConfigureLightDialog> lightDialog;
    QPointer<ConfigureMaterialDialog> materialDialog;
    QPointer<ToggleFeaturesDialog> toggleFeaturesDialog;
    QPointer<AlphaTestDialog> alphaTestDialog;

    QPointer<QInputDialog> alphaExponentInputDialog;
    QPointer<QInputDialog> alphaFactorInputDialog;
    QPointer<QFileDialog> inputFileDialog;

    QStringList inputFileNameList;
};

#endif // MAINWINDOW_H
