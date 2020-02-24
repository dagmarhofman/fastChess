#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QtXml>
#include <QFile>
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

struct chessMoves {
    QString eco;
    QString opening;
    QString variant;
    QStringList chessMoves;
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
    void parseMovesXML();

    QTimer *timer;
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void showFullScreen();
    void on_pushButton_6_clicked();
    void timerSlot();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *figure;
    bool boardViewBlack = false;
    QList<chessMoves> allMoves;
    int currentOpening;
    int currentMove;
    int openingShowCount;

};

#endif // MAINWINDOW_H
