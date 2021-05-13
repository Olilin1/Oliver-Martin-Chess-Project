#include "mainwindow.h"

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
        if(game.MakeMove(prevPress, {row,col})){
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
                if(mode == PVEBLACK || mode == PVEWHITE)
                    funcMakeAiMove();
            }
            else if (mode == PVEBLACK || mode == PVEWHITE){
                funcMakeAiMove();
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

MainWindow::MainWindow(LaunchMode Mode, QWidget *parent)
    : QMainWindow(parent)
{
    mode = Mode;
    prevPress = {-1,-1};
    if(mode != DEBUG)
        resize(800,800);
    else{
        resize(800, 850);
        btnMakeAiMove = new QPushButton("AI move",this);
        btnMakeAiMove->setGeometry(0,800,100,50);

        btnSetupGame = new QPushButton("Setup game",this);
        btnSetupGame->setGeometry(100,800,100,50);

        editSetupGame = new QLineEdit(this);
        editSetupGame->setGeometry(200,800, 400,25);

        connect(btnMakeAiMove, SIGNAL(clicked()), this, SLOT(funcMakeAiMove()));
        connect(btnSetupGame, SIGNAL(clicked()), this, SLOT(funcSetupGame()));
    }

    game.SetupGame("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");


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
    qApp->processEvents();
}

void MainWindow::funcMakeAiMove(){
    qDebug() << "AI";
    game.AiMove();
    if(game.awaitingPromotion()){
        game.AiMove();
    }
    render_pieces();
}

void MainWindow::funcSetupGame(){
    qDebug() << "SETUP";
    std::string fen = editSetupGame->text().toUtf8().constData();
    game.SetupGame(fen);
    render_pieces();
}


