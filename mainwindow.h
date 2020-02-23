#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>

namespace Ui {
    class MainWindow;
}

enum pieceType { Rook = 'r', Knight = 'n', Bishop = 'b', Queen = 'q', King = 'k', Pawn ='p', Empty = ' ' };
enum pieceColor { White = 'w', Black = 'b' };

struct boardElement {
    pieceType piece;
    pieceColor color;
    QGraphicsPixmapItem *icon;
    int xPos;
    int yPos;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVector<QGraphicsPixmapItem*> whiteFigures;
    QVector<QGraphicsPixmapItem*> blackFigures;

    boardElement board[8][8];

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void initBoard(QString fen);
    void drawBoard();
    void drawFigure(boardElement);
    void swapBoard();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *figure;
    bool boardViewBlack = false;
};

#endif // MAINWINDOW_H
