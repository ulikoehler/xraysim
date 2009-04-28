#include "gldialog.h"
#include "ui_gldialog.h"

gldialog::gldialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::gldialog)
{
    m_ui->setupUi(this);
}

gldialog::~gldialog()
{
    delete m_ui;
}

void gldialog::changeEvent(QEvent *e)
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

void gldialog::closeEvent(QCloseEvent* event)
{
    int ret = QMessageBox::question(this, tr("Quit GLXRaySim?"),
                                   tr("Do you really want to quit GLXRaySim?"),
                                   QMessageBox::No | QMessageBox::Yes);
    if(ret == QMessageBox::Yes)
    {
        QApplication::quit();
    }
    else {event->ignore();}
}
