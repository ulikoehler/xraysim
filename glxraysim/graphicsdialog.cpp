#include "graphicsdialog.h"
#include "ui_graphicsdialog.h"

graphicsdialog::graphicsdialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::graphicsdialog)
{
    m_ui->setupUi(this);
}

graphicsdialog::~graphicsdialog()
{
    delete m_ui;
}

 void graphicsdialog::setImage(QImage& image)
 {
    m_ui->graphicsView->setBackgroundBrush(image);
    m_ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
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
