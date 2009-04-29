#ifndef GLDIALOG_H
#define GLDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QMenu>
#include <QFileDialog>
#include <QPointer>
#include <QShortcut>
#include "xrayglwidget.h"

namespace Ui
{
    class gldialog;
}

class gldialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(gldialog)
public:
    explicit gldialog(QWidget *parent = 0);
    virtual ~gldialog();

    void setGLWidget(XRayGLWidget* widget);

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent* event);

private:
    Ui::gldialog *m_ui;
    XRayGLWidget* glWidget;

protected slots:
    void onFrameBufferSaveShortcutActivated();
};

#endif // GLDIALOG_H
