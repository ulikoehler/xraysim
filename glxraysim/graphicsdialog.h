#ifndef GRAPHICSDIALOG_H
#define GRAPHICSDIALOG_H

#include <QDialog>
#include <QSharedPointer>

namespace Ui {
    class GraphicsDialog;
}

class GraphicsDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(GraphicsDialog)

public:
    explicit GraphicsDialog(QWidget *parent = 0);
    virtual ~GraphicsDialog();

    void setImage(QImage& image);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::GraphicsDialog *m_ui;
};

#endif // GRAPHICSDIALOG_H
