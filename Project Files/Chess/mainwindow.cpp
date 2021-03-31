#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,800);

    scene = new QGraphicsScene;
    view = new QGraphicsView(this);
    view->resize(800,800);
    squareSize = 64;

    generate_board();

    view->setScene(scene);
    view->show();

}

MainWindow::~MainWindow()
{
}

void MainWindow::generate_board(QColor black, QColor white){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = new QGraphicsRectItem(squareSize*i, squareSize*j, squareSize, squareSize);
            board[i][j]->setBrush((i+j)%2 ? black : white);
            scene->addItem(board[i][j]);
        }
    }
}

