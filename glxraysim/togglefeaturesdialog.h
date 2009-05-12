#ifndef TOGGLEFEATURESDIALOG_H
#define TOGGLEFEATURESDIALOG_H

#include <QtGui/QDialog>
#include <QtOpenGL>

namespace Ui {
    class ToggleFeaturesDialog;
}

class ToggleFeaturesDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ToggleFeaturesDialog)
public:
    explicit ToggleFeaturesDialog(QWidget *parent = 0);
    virtual ~ToggleFeaturesDialog();

signals:
    void featureToggled(uint feature, bool enabled);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ToggleFeaturesDialog *m_ui;

private slots:
    void on_cullFaceCheckBox_toggled(bool checked);
    void on_autoNormalCheckBox_toggled(bool checked);
    void on_alphaTestCheckBox_toggled(bool checked);
    void on_texture2dCheckBox_toggled(bool checked);
    void on_blendingCheckBox_toggled(bool checked);
    void on_colorMaterialCheckBox_toggled(bool checked);
    void on_lightingCheckBox_toggled(bool checked);
    void on_depthTestCheckBox_toggled(bool checked);
};

#endif // TOGGLEFEATURESDIALOG_H
