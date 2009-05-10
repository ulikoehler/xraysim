#ifndef CONFIGUREMATERIALDIALOG_H
#define CONFIGUREMATERIALDIALOG_H

#include <QtGui/QDialog>
#include "globaldef.h"

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

signals:
    void ambientChanged(vec4f values);
    void diffuseChanged(vec4f values);
    void specularChanged(vec4f values);
    void emissionChanged(vec4f values);
    void shininessChanged(int value);

private slots:
    void ambientValuesChanged(double);
    void diffuseValuesChanged(double);
    void specularValuesChanged(double);
    void emissionValuesChanged(double);
    void shininessValuesChanged(int value);


private:
    Ui::ConfigureMaterialDialog *m_ui;
};

#endif // CONFIGUREMATERIALDIALOG_H
