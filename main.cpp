#include "indexation.h"
#include "moteur_de_recherche.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Indexation w;
    w.show();

    return a.exec();
}
