#include "infogeneral.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    InfoGeneral w;
    w.show();
    return a.exec();
}


