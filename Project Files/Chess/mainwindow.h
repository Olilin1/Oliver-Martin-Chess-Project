#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include <QDir>
#include <QDebug>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include"Logic/Game.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int squareSize;
    std::map<char, QImage*> pieceImages;
    std::vector<QGraphicsPixmapItem*> pieces;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsRectItem* board[8][8];
    Game game;


    void generate_board(QColor black = Qt::black, QColor white = Qt::white);
    void render_pieces();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
