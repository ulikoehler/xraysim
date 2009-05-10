#include "configurematerialdialog.h"
#include "ui_configurematerialdialog.h"

ConfigureMaterialDialog::ConfigureMaterialDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ConfigureMaterialDialog)
{
    m_ui->setupUi(this);
}

ConfigureMaterialDialog::~ConfigureMaterialDialog()
{
    delete m_ui;
}

void ConfigureMaterialDialog::changeEvent(QEvent *e)
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
