#include "configurelightdialog.h"
#include "ui_configurelightdialog.h"

ConfigureLightDialog::ConfigureLightDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ConfigureLightDialog)
{
    m_ui->setupUi(this);
}

ConfigureLightDialog::~ConfigureLightDialog()
{
    delete m_ui;
}

void ConfigureLightDialog::changeEvent(QEvent *e)
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

void ConfigureLightDialog::on_light1Cutoff180CheckBox_toggled(bool checked)
{
    //Disable the cutoff spin box if the 180 degrees button is selected; else enable it
    if(checked)
    {
        m_ui->light1CutoffSpinBox->setEnabled(false);
    }
    else
    {
        m_ui->light1CutoffSpinBox->setEnabled(true);
    }

}
