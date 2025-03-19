#include "lab.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lab w;
    w.show();

    return a.exec();
}
