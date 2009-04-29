#include "gldialog.h"
#include "ui_gldialog.h"

gldialog::gldialog(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::gldialog)
{
    m_ui->setupUi(this);
    QPointer<QShortcut> saveFramebufferShortcut(new QShortcut(QKeySequence("Ctrl+S"), this));
    connect(saveFramebufferShortcut, SIGNAL(activated()), this, SLOT(onFrameBufferSaveShortcutActivated()));
}

gldialog::~gldialog()
{
    delete m_ui;
}

void gldialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void gldialog::setGLWidget(XRayGLWidget* widget)
{
    glWidget = widget;
    layout()->addWidget(widget);
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

void gldialog::onFrameBufferSaveShortcutActivated()
{
    QPointer<QFileDialog> fileDialog(new QFileDialog(this, "Save image to"));
    fileDialog->setAcceptMode(QFileDialog::AcceptSave);
    if(fileDialog->exec() == QDialog::Accepted)
    {
        glWidget->grabFrameBuffer(true).save(fileDialog->selectedFiles()[0]);
    }

}
