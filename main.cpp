#include "mdiprogram.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MDIProgram w;
    w.show();
    return a.exec();
}
