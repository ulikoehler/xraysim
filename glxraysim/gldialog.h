#ifndef GLDIALOG_H
#define GLDIALOG_H

#include <QtGui/QDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QCloseEvent>

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

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent* event);

private:
    Ui::gldialog *m_ui;
};

#endif // GLDIALOG_H
