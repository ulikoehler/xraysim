#ifndef CONFIGUREMATERIALDIALOG_H
#define CONFIGUREMATERIALDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class ConfigureMaterialDialog;
}

class ConfigureMaterialDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(ConfigureMaterialDialog)
public:
    explicit ConfigureMaterialDialog(QWidget *parent = 0);
    virtual ~ConfigureMaterialDialog();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::ConfigureMaterialDialog *m_ui;
};

#endif // CONFIGUREMATERIALDIALOG_H
