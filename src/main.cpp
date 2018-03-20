#include "pfe.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    glutInit(&argc, argv);
    PFE w;
    w.show();
    return a.exec();
}
