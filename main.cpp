#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    int i = 0;
    MainWindow w;
    w.show();
    return a.exec();           // exec()函数开始了Qt的事件循环来监听应用程序的事件
}