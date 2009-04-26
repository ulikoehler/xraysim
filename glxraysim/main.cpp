#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Generate a QStringList of the image name
    QStringList images;
    for(int i = 1; i < argc; i++)
    {
        images << argv[i];
    }


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
