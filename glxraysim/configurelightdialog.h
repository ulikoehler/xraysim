/**
 * OpenGL developer remark:
 * LIGHT_0 is referenced as light1 in this file
 * That way the user doesn't need to be familiar with the OpenGL syntax
 */
#ifndef CONFIGURELIGHTDIALOG_H
#define CONFIGURELIGHTDIALOG_H

#include <QtGui/QDialog>

#include <tr1/array>
using namespace std::tr1;

typedef array<float, 3> vec3f;
typedef array<double, 3> vec3d;
typedef array<float, 4> vec4f;
typedef array<double, 4> vec4d;

namespace Ui {
    class ConfigureLightDialog;
}

class ConfigureLightDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ConfigureLightDialog)
public:
    explicit ConfigureLightDialog(QWidget *parent = 0);
    virtual ~ConfigureLightDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ConfigureLightDialog *m_ui;

signals:
    void ambientIntensityChanged(vec4d values);


private slots:
    void on_light1Cutoff180CheckBox_toggled(bool checked);
    void ambientIntensityValuesChanged(double value);
};

#endif // CONFIGURELIGHTDIALOG_H
