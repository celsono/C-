#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    int i = 0;
    MainWindow w;
    w.show();
    return a.exec();           // exec()������ʼ��Qt���¼�ѭ��������Ӧ�ó�����¼�
}