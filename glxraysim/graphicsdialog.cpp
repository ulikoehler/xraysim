#include "graphicsdialog.h"
#include "ui_graphicsdialog.h"

#include <iostream>
using namespace std;

graphicsdialog::graphicsdialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::graphicsdialog)
{
    m_ui->setupUi(this);
    m_ui->imageLabel->setBackgroundRole(QPalette::AlternateBase);
}

graphicsdialog::~graphicsdialog()
{
    delete m_ui;
}

 void graphicsdialog::setImage(QImage& image)
 {
    m_ui->imageLabel->setPixmap(QPixmap::fromImage(image));
 }

void graphicsdialog::changeEvent(QEvent *e)
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
