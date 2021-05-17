#include "mainwindow.h"

#include <QApplication>

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

//    This if for testing move generation speed
//    std::clock_t start = std::clock();
//    int sum = game.SumOfAllMoves(5, true);
//    std::cout<<std::endl<<"Nodes searched: "<<sum<<std::endl;
//    float time = ((std::clock()-start)/(double)CLOCKS_PER_SEC);
//    std::cout<<time<<" seconds elapsed"<<std::endl;
//    std::cout<<"Nodes/seconds: "<<sum/time<<std::endl;
//    return 0;
}
