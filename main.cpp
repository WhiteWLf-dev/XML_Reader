#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
     qApp->setStyle(QStyleFactory::create("Fusion"));






    MainWindow w;
    w.resize(600,410);
    w.show();
    return a.exec();
}
