#include "graphicsdialog.h"
#include "ui_graphicsdialog.h"

#include <iostream>
using namespace std;

GraphicsDialog::GraphicsDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::GraphicsDialog)
{
    m_ui->setupUi(this);
    m_ui->imageLabel->setBackgroundRole(QPalette::AlternateBase);
    m_ui->imageLabel->update();
}

GraphicsDialog::~GraphicsDialog()
{
    delete m_ui;
}

 void GraphicsDialog::setImage(QImage& image)
 {
    m_ui->imageLabel->setPixmap(QPixmap::fromImage(image));
 }

void GraphicsDialog::changeEvent(QEvent *e)
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
