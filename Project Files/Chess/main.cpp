#include "mainwindow.h"
#include <QElapsedTimer>
#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    QElapsedTimer timer;
    timer.start();
    Game g;
    std::cout<<g.SumOfAllMoves(4)<<std::endl;
    std::cout<<std::endl<<timer.elapsed()/(float)1000<<" seconds elapsed"<<std::endl;
}
