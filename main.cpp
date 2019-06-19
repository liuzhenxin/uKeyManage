#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));
    MainWindow w;
    w.setWindowTitle("UsbKeyFile");
    w.show();

    return a.exec();
}
