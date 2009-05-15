#include "newmatrixdialog.h"
#include "ui_newmatrixdialog.h"

NewMatrixDialog::NewMatrixDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::NewMatrixDialog)
{
    m_ui->setupUi(this);
}

NewMatrixDialog::~NewMatrixDialog()
{
    delete m_ui;
}

void NewMatrixDialog::changeEvent(QEvent *e)
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

void NewMatrixDialog::on_buttonBox_accepted()
{

}

void NewMatrixDialog::on_buttonBox_rejected()
{

}
