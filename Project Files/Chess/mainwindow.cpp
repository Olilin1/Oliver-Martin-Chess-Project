#include "mainwindow.h"
#include <QThread>

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    //Delete all previously rendered pieces
    for(auto a : moveCircles){
        scene->removeItem(a);
        delete a;
    }
    moveCircles.clear();
    if(event->pos().y() < 145 || event->pos().y() > 145+8*squareSize || event->pos().x() < 145 || event->pos().x() > 145+8*squareSize){
        prevPress = {-1,-1};
        return;
    }
    int row = abs((event->pos().y()-145)/squareSize-7);
    int col = (event->pos().x()-145)/squareSize;

    if(prevPress != std::make_pair(-1,-1)){

        std::set<square> moves;
        game.LegalMoves(prevPress, moves);

        if(moves.count({row, col})){
            render_pieces();

            prevPress = {-1,-1};
            if(game.awaitingPromotion()){
                start:
                bool ok;
                QStringList items;
                items << tr("Rook") << tr("Knight") << tr("Queen") << tr("Bishop");
                QString item = QInputDialog::getItem(this, tr("Promotion"),
                                                         tr("Piece:"), items, 0, false, &ok);
                if(ok){
                    if(item == "Rook"){
                        game.MakeMove(nullSquare,nullSquare, Rook);
                    }
                    if(item == "Knight"){
                        game.MakeMove(nullSquare,nullSquare, Knight);
                    }
                    if(item == "Bishop"){
                        game.MakeMove(nullSquare,nullSquare, Bishop);
                    }
                    if(item == "Queen"){
                        game.MakeMove(nullSquare,nullSquare, Queen);
                    }
                }
                else goto start;
                render_pieces();
            }
            return;
        }
    }

    std::cout   << row<< ' '<< col  << std::endl;

    std::set<square> moves;
    game.LegalMoves({row,col},moves);
    for(square move : moves){
        QGraphicsEllipseItem* moveCircle = new QGraphicsEllipseItem(squareSize*move.second +squareSize/2 -5, squareSize*move.first +squareSize/2-5, 10, 10);
        moveCircles.push_back(moveCircle);
        moveCircle->setBrush(Qt::red);
        scene->addItem(moveCircle);
    }

    prevPress = {row,col};
    QMainWindow::mousePressEvent(event); // then call default implementation
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    prevPress = {-1,-1};
    resize(800,800);

    //TODO: Move this
    /*
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
    */


    pieceImages[BlackKnight] = new QImage(":/ChessPieces/bN.png");
    pieceImages[BlackRook] = new QImage(":/ChessPieces/bR.png");
    pieceImages[BlackKing] = new QImage(":/ChessPieces/bK.png");
    pieceImages[BlackQueen] = new QImage(":/ChessPieces/bQ.png");
    pieceImages[BlackBishop] = new QImage(":/ChessPieces/bB.png");
    pieceImages[BlackPawn] = new QImage(":/ChessPieces/bP.png");
    pieceImages[WhiteKnight] = new QImage(":/ChessPieces/wN.png");
    pieceImages[WhiteRook] = new QImage(":/ChessPieces/wR.png");
    pieceImages[WhiteKing] = new QImage(":/ChessPieces/wK.png");
    pieceImages[WhiteQueen] = new QImage(":/ChessPieces/wQ.png");
    pieceImages[WhiteBishop] = new QImage(":/ChessPieces/wB.png");
    pieceImages[WhitePawn] = new QImage(":/ChessPieces/wP.png");


    scene = new QGraphicsScene;
    view = new QGraphicsView(this);
    view->resize(800,800);
    squareSize = 64;

    generate_board(Qt::gray);
    render_pieces();


    view->setScene(scene);
    view->scale(1,-1);
    view->show();

}

MainWindow::~MainWindow()
{
}

//This simply draws a board in the specified colors
void MainWindow::generate_board(QColor black, QColor white){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = new QGraphicsRectItem(squareSize*j, squareSize*i, squareSize, squareSize);
            board[i][j]->setBrush((i+j)%2 ? white : black);
            scene->addItem(board[i][j]);
        }
    }

}

//This function takes a string in fen notation(Only the first placement part)
//And places out pieces based on that.
void MainWindow::render_pieces(){

    //Delete all previously rendered pieces
    for(auto a : pieces){
        scene->removeItem(a);
        delete a;
    }
    pieces.clear();

    Board b = game.getBoard();

    for(int i = 0; i < 8; i++){
        for(int j = 0; j<8; j++){
            if(b[{i,j}] == Empty) continue;

            QGraphicsPixmapItem* newItem = new QGraphicsPixmapItem(QPixmap::fromImage(pieceImages[b[{i,j}]]->mirrored(false,true)));
            newItem->setOffset(squareSize * j-1, squareSize * i);
            scene->addItem(newItem);
            pieces.push_back(newItem);
        }
    }
}



