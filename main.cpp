#include "widget.h"
#include "graphwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphWidget w;
    w.resize(600, 600);
    w.show();
    return a.exec();
}
