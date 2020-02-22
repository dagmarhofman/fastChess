#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(trUtf8("Chess"));

    mkBoard();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mkBoard()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 800);
    scene->setBackgroundBrush(Qt::lightGray);
    ui->graphicsView->setScene(scene);


    bool isWhite = true;  //Рисуем  игральну доску
    for(int y = 0; y < 800; y += 100)
    {
        for(int x = 0; x < 800; x += 100)
        {
            QBrush brush;
            if(isWhite) brush = QBrush(Qt::white);
            else brush = QBrush(Qt::gray);
            scene->addRect(x, y, 100, 100, QPen(Qt::black), brush);

            if(isWhite) isWhite = false;
            else isWhite = true;
        }
        if(isWhite) isWhite = false;
        else isWhite = true;
    }

      int posX = 0;
      int posY = 0;

      for(posX = 0; posX<800; posX += 700)
      {
          figure = scene->addPixmap(QPixmap("://images/black_rook.png"));
          figure->setPos(posX, posY);
          if(figure) blackFigures.append(figure);
          figure->setData(0, "Rook");
      }

      posX = 100;
      for(posX = 100; posX<800; posX += 500)
      {
      figure = scene->addPixmap(QPixmap("://images/black_horse.png"));
      figure->setPos(posX, posY);
      if(figure) blackFigures.append(figure);
      figure->setData(0,"Horse");
      }

      posX = 200;
      for(posX=200; posX<800; posX +=300)
      {
      figure = scene->addPixmap(QPixmap("://images/black_bishop.png"));
      figure->setPos(posX, posY);
      if(figure) blackFigures.append(figure);
      figure->setData(0, "Bishop");
      }

      posX = 300;
      figure = scene->addPixmap(QPixmap("://images/black_queen.png"));
      figure->setPos(posX, posY);
      if(figure) blackFigures.append(figure);
      figure->setData(0, "Queen");

      posX = 400;
      figure = scene->addPixmap(QPixmap("://images/black_king.png"));
      figure->setPos(posX, posY);
      if(figure) blackFigures.append(figure);
      figure->setData(0, "King");


      posX = 0;
      posY = 700;

      for(posX = 0; posX<800; posX += 700)
      {
      figure = scene->addPixmap(QPixmap("://images/white_rook.png"));
      figure->setPos(posX, posY);
      if(figure) whiteFigures.append(figure);
      figure->setData(0, "Rook");
      }

      posX = 100;
      for(posX = 100; posX<800; posX += 500)
      {
      figure = scene->addPixmap(QPixmap("://images/white_horse.png"));
      figure->setPos(posX, posY);
      if(figure) whiteFigures.append(figure);
      figure->setData(0, "Horse");
      }

      posX = 200;
      for(posX=200; posX<800; posX +=300)
      {
      figure = scene->addPixmap(QPixmap("://images/white_bishop.png"));
      figure->setPos(posX, posY);
      if(figure) whiteFigures.append(figure);
      figure->setData(0, "Bishop");
      }

      posX = 300;
      figure = scene->addPixmap(QPixmap("://images/white_queen.png"));
      figure->setPos(posX, posY);
      if(figure) whiteFigures.append(figure);
      figure->setData(0, "Queen");

      posX = 400;
      figure = scene->addPixmap(QPixmap("://images/white_king.png"));
      figure->setPos(posX, posY);
      if(figure) whiteFigures.append(figure);
      figure->setData(0, "King");

      posY = 100;
      for(posX = 0; posX < 800; posX += 100)
      {
          figure = scene->addPixmap(QPixmap("://images/black_pawn.png"));
          figure->setPos(posX, posY);
          if(figure) blackFigures.append(figure);
          figure->setData(0, "Pawn");
      }

      posY = 600;
      for(posX = 0; posX < 800; posX += 100)
      {
          figure = scene->addPixmap(QPixmap("://images/white_pawn.png"));
          figure->setPos(posX, posY);
          if(figure) whiteFigures.append(figure);
          figure->setData(0, "Pawn");
      }
}

void MainWindow::drawFigure( boardElement el )
{

    switch( el.piece ) {
        case Rook:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_rook.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_rook.png"));
        figure->setData(0, "Rook");
        break;
        case Bishop:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_bishop.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_bishop.png"));
        figure->setData(0, "Bishop");
        break;
        case King:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_king.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_king.png"));
        figure->setData(0, "King");
        break;
        case Queen:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_queen.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_queen.png"));
        figure->setData(0, "Queen");
        break;
        case Pawn:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_pawn.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_pawn.png"));
        figure->setData(0, "Pawn");
        break;
        case Knight:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_knight.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_knight.png"));
        figure->setData(0, "Knight");
        break;
        case Empty:
        break;

    }
    figure->setPos(el.xPos, el.yPos);

    if( el.color == Black )
        if(figure) blackFigures.append(figure);
    else if( el.color == White )
        if(figure) whiteFigures.append(figure);

}

void MainWindow::drawBoard()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 800);
    scene->setBackgroundBrush(Qt::lightGray);
    ui->graphicsView->setScene(scene);

    bool isWhite = true;
    int i=0,j=0;
    for(int y = 0; y < 800; y += 100)
    {
        for(int x = 0; x < 800; x += 100)
        {
            QBrush brush;
            if(isWhite) brush = QBrush(Qt::white);
            else brush = QBrush(Qt::gray);
            scene->addRect(x, y, 100, 100, QPen(Qt::black), brush);
            this->drawFigure(board[i][j]);
            if(isWhite) isWhite = false;
            else isWhite = true;
            i++;
        }
        if(isWhite) isWhite = false;
        else isWhite = true;
        j++;
    }





}
