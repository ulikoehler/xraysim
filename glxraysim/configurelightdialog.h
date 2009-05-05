/**
 * OpenGL developer remark:
 * LIGHT_0 is referenced as light1 in this file
 * That way the user doesn't need to be familiar with the OpenGL syntax
 *
 * Slots are referred as ...ValueChanged(...); signals as ...Changed(...)
 * Slot parameters are ignored usuallyd
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
    ConfigureLightDialog* thisRef;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ConfigureLightDialog *m_ui;

signals:
    void ambientIntensityChanged(vec4d values);
    //Light 1
    void light1Toggled(bool enabled);
    void light1PositionChanged(vec3f values);
    void light1DirectionChanged(vec3f values);
    void light1AmbientChanged(vec4f values);
    void light1DiffuseChanged(vec4f values);
    void light1SpecularChanged(vec4f values);
    void light1AttenuationChanged(vec4f values);
    void light1ExponentChanged(float value);

public slots:
    void ambientIntensityValuesChanged(double value);
    //Light 1
    void light1ToggledChanged(bool enabled);
    void light1PositionValuesChanged(double);
    void light1DirectionValuesChanged(double);
    void light1AmbientValuesChanged(double);
    void light1DiffuseValuesChanged(double);
    void light1SpecularValuesChanged(double);
    void light1ExponentValueChanged(double value);


private slots:
    void on_light1Cutoff180CheckBox_toggled(bool checked);
};

#endif // CONFIGURELIGHTDIALOG_H
