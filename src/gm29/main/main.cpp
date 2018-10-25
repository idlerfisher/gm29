#include <QApplication>
#include <QTextCodec>
#include "cicadamainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

    CicadaMainWindow w;
    w.show();
    
    return a.exec();
}
