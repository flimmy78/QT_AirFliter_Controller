#include <QApplication>
#include "dabai.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dabai w;
    w.show();
    
    return a.exec();
}
