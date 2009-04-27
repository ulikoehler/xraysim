#ifndef GLDIALOG_H
#define GLDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class gldialog;
}

class gldialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(gldialog)
public:
    explicit gldialog(QWidget *parent = 0);
    virtual ~gldialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::gldialog *m_ui;
};

#endif // GLDIALOG_H
