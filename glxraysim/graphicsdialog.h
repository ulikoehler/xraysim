#ifndef GRAPHICSDIALOG_H
#define GRAPHICSDIALOG_H

#include <QDialog>
#include <tr1/memory>
using namespace std::tr1;

namespace Ui {
    class GraphicsDialog;
}

class GraphicsDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(GraphicsDialog)

public:
    explicit GraphicsDialog(QWidget *parent = 0);
    virtual ~GraphicsDialog();

    void setImage(shared_ptr<QImage> image);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::GraphicsDialog *m_ui;
    shared_ptr<QImage> image;
};

#endif // GRAPHICSDIALOG_H
