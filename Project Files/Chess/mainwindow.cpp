#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(800,800);

    //TODO: Move this
    pieceImages['n'] = new QPixmap(":/ChessPieces/bN.png");
    pieceImages['r'] = new QPixmap(":/ChessPieces/bR.png");
    pieceImages['k'] = new QPixmap(":/ChessPieces/bK.png");
    pieceImages['q'] = new QPixmap(":/ChessPieces/bQ.png");
    pieceImages['b'] = new QPixmap(":/ChessPieces/bB.png");
    pieceImages['p'] = new QPixmap(":/ChessPieces/bP.png");
    pieceImages['N'] = new QPixmap(":/ChessPieces/wN.png");
    pieceImages['R'] = new QPixmap(":/ChessPieces/wR.png");
    pieceImages['K'] = new QPixmap(":/ChessPieces/wK.png");
    pieceImages['Q'] = new QPixmap(":/ChessPieces/wQ.png");
    pieceImages['B'] = new QPixmap(":/ChessPieces/wB.png");
    pieceImages['P'] = new QPixmap(":/ChessPieces/wP.png");

    scene = new QGraphicsScene;
    view = new QGraphicsView(this);
    view->resize(800,800);
    squareSize = 64;

    generate_board(Qt::gray);
    render_pieces("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");


    view->setScene(scene);
    view->show();

}

MainWindow::~MainWindow()
{
}

//This simply draws a board in the specified colors
void MainWindow::generate_board(QColor black, QColor white){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = new QGraphicsRectItem(squareSize*i, squareSize*j, squareSize, squareSize);
            board[i][j]->setBrush((i+j)%2 ? black : white);
            scene->addItem(board[i][j]);
        }
    }
}

//This function takes a string in fen notation(Only the first placement part)
//And places out pieces based on that.
void MainWindow::render_pieces(std::string fen){

    //Delete all previously rendered pieces
    for(auto a : pieces){
        scene->removeItem(a);
        delete a;
    }
    pieces.clear();

    //Pointers for where to place the pieces
    int i = 0;
    int j = 0;
    for(char a : fen){
        if(a == '/'){
            i=0;
            j++;
        }
        else if(a >= '0' && a <='9'){
            i+= (a-'0');
        }
        else{
            //Get piece path from map and add it to the scene
            QGraphicsPixmapItem *newItem=new QGraphicsPixmapItem(*pieceImages[a]);
            newItem->setOffset(squareSize * i-1, squareSize * j);
            scene->addItem(newItem);
            pieces.push_back(newItem);
            i++;
        }
    }
}


