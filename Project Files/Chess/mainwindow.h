#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <vector>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    int squareSize;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsRectItem* board[8][8];

    void generate_board(QColor black = Qt::black, QColor white = Qt::white);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
