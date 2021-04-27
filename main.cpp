#include "mainwindow.h"
#include"askdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AskDialog w;
    w.show();
    return a.exec();
}
