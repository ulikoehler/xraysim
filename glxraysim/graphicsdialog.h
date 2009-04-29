#ifndef GRAPHICSDIALOG_H
#define GRAPHICSDIALOG_H

#include <QtGui/QDialog>

namespace Ui {
    class graphicsdialog;
}

class graphicsdialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(graphicsdialog)

public:
    explicit graphicsdialog(QWidget *parent = 0);
    virtual ~graphicsdialog();

    void setImage(QImage* image);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::graphicsdialog *m_ui;
};

#endif // GRAPHICSDIALOG_H
