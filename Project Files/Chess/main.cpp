#include "mainwindow.h"

#include <QApplication>
#include<assert.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool ok;
    QStringList items;
    items  << "DEBUG" << "PVP" << "PVEWHITE" << "PVEBLACK";
    QString item = QInputDialog::getItem(NULL, "Launch mode",
                                             "Mode:", items, 0, false, &ok);
    LaunchMode mode;//For now both PVEWhite and PVEBlack makes you play as black but whatevs.
    if(ok){
        if(item == "PVP") mode = PVP;
        else if (item == "DEBUG") mode = DEBUG;
        else if (item == "PVEWHITE") mode = PVEWHITE;
        else if (item == "PVEBLACK") mode = PVEBLACK;
        else assert(false);
    }
    else{
        return 0;
    }

    MainWindow w(mode);
    w.show();
    return a.exec();
}
