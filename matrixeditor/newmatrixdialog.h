#ifndef NEWMATRIXDIALOG_H
#define NEWMATRIXDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class NewMatrixDialog;
}

class NewMatrixDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(NewMatrixDialog)
public:
    explicit NewMatrixDialog(QWidget *parent = 0);
    virtual ~NewMatrixDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::NewMatrixDialog *m_ui;
};

#endif // NEWMATRIXDIALOG_H
