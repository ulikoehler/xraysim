#ifndef ALPHATESTDIALOG_H
#define ALPHATESTDIALOG_H

#include <QtGui/QDialog>
#include <QtOpenGL>

namespace Ui {
    class AlphaTestDialog;
}

class AlphaTestDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AlphaTestDialog)
public:
    explicit AlphaTestDialog(QWidget *parent = 0);
    virtual ~AlphaTestDialog();

protected:
    virtual void changeEvent(QEvent *e);

signals:
     void alphaTestChanged(uint mode, double val);

private slots:
     void guiStateChanged();

private:
    Ui::AlphaTestDialog *m_ui;
};

#endif // ALPHATESTDIALOG_H
