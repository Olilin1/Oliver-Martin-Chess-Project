#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Logic/Game.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int squareSize;
    std::map<char, QPixmap*> pieceImages;
    std::vector<QGraphicsPixmapItem*> pieces;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsRectItem* board[8][8];
    Game engine;


    void generate_board(QColor black = Qt::black, QColor white = Qt::white);
    void render_pieces(std::string fen);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
