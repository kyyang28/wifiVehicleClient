#include <QtGui/QApplication>
//#include "mainwindow.h"
#include "logindialog.h"
#include "ctrlmodedialog.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    //MainWindow w;
    loginDialog login;
    ctrlModeDialog ctrlMode;
    if (login.exec() == QDialog::Accepted) {
        //w.show();
        ctrlMode.show();
        return a.exec();
    }else {
        return 0;
    }

    //return a.exec();
}
