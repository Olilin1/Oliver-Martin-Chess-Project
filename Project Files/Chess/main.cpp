#include "mainwindow.h"
#include <QElapsedTimer>
#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();
    Game g;
    g.GenerateBishopBlockerBoards();
    g.GenerateRookBlockerBoards();
    for(Bitboard b : g.BishopBlockerBoards) {
        std::cout<<b.ToString()<<std::endl;
    }
}
