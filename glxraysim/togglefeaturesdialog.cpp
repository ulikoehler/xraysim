#include "togglefeaturesdialog.h"
#include "ui_togglefeaturesdialog.h"

ToggleFeaturesDialog::ToggleFeaturesDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ToggleFeaturesDialog)
{
    m_ui->setupUi(this);
}

ToggleFeaturesDialog::~ToggleFeaturesDialog()
{
    delete m_ui;
}

void ToggleFeaturesDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void ToggleFeaturesDialog::on_depthTestCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_DEPTH_TEST, checked);
}

void ToggleFeaturesDialog::on_lightingCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_LIGHTING, checked);
}

void ToggleFeaturesDialog::on_colorMaterialCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_COLOR_MATERIAL, checked);
}

void ToggleFeaturesDialog::on_blendingCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_BLEND, checked);
}

void ToggleFeaturesDialog::on_texture2dCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_TEXTURE_2D, checked);
}

void ToggleFeaturesDialog::on_alphaTestCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_ALPHA_TEST, checked);
}

void ToggleFeaturesDialog::on_autoNormalCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_AUTO_NORMAL, checked);
}

void ToggleFeaturesDialog::on_cullFaceCheckBox_toggled(bool checked)
{
    emit featureToggled(GL_CULL_FACE, checked);
}
