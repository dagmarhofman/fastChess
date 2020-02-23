#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(trUtf8("Chess"));

    parseJSON();

    initBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    drawBoard();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::parseJSON()
{

    QString data;
    QString fileName(":/eco_openings.txt");

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"filenot opened"<<endl;
    }
    else
    {
        qDebug()<<"file opened"<<endl;
        data = QString(file.readAll());
    }

    file.close();

    QRegExp regexTags("(\\[|\\])");
    QStringList tagList = data.split(regexTags);

    for ( const QString& field : tagList  )
    {

        printf("FIELD : %s\n", field.toStdString().c_str() );

    }

}


void MainWindow::drawFigure( boardElement el )
{
    switch( el.piece ) {
        case 'r':
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_rook.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_rook.png"));
        whiteFigures.append(figure);
        figure->setData(0, "Rook");
        figure->setPos( el.xPos, el.yPos);
        break;
        case Bishop:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_bishop.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_bishop.png"));
        figure->setData(0, "Bishop");
        figure->setPos(el.xPos, el.yPos);
        break;
        case King:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_king.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_king.png"));

        figure->setData(0, "King");
        figure->setPos(el.xPos, el.yPos);
        break;
        case Queen:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_queen.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_queen.png"));
        figure->setData(0, "Queen");
        figure->setPos(el.xPos, el.yPos);
        break;
        case Pawn:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_pawn.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_pawn.png"));
        figure->setData(0, "Pawn");
        figure->setPos(el.xPos, el.yPos);
        break;
        case Knight:
        if( el.color == Black )
            figure = scene->addPixmap(QPixmap("://images/black_horse.png"));
        else if( el.color == White )
            figure = scene->addPixmap(QPixmap("://images/white_horse.png"));
        figure->setData(0, "Knight");
        figure->setPos(el.xPos, el.yPos);
        break;
        case Empty:
        break;
    }

    if( el.color == Black ) {
        if(figure) blackFigures.append(figure);
    }
    else if( el.color == White )
    {
        if(figure) whiteFigures.append(figure);
    }

}


void MainWindow::initBoard( QString fen )
{

    char c = '\0';
    int thisChar;
    int rowNum=0, colNum=0;

    int i;
    int j;

    for(i = 0; i < 8;i++) {
        for(j = 0; j < 8;j++) {
            board[j][i].piece = Empty;
            board[j][i].color = White;
        }
    }

    for (i = 0; c != ' ' ; i++)
    {
        c = fen.toStdString().c_str()[i];
        thisChar = c - '0';

        if (c == '/')
        {
            rowNum++;
            colNum = 0;
        } else if(thisChar > 0 && thisChar <= 9)
        {
            for (int j = 0; j < thisChar; j++)
            {
                board[rowNum][colNum].piece = Empty;
                board[rowNum][colNum].color = White;
                colNum++;
            }
        } else {
            switch(c)
            {
            case 'R':
                board[rowNum][colNum].piece = Rook;
                board[rowNum][colNum].color = White;
                break;
            case 'N':
                board[rowNum][colNum].piece = Knight;
                board[rowNum][colNum].color = White;
                break;
            case 'B':
                board[rowNum][colNum].piece = Bishop;
                board[rowNum][colNum].color = White;
                break;
            case 'K':
                board[rowNum][colNum].piece = King;
                board[rowNum][colNum].color = White;
                break;
            case 'Q':
                board[rowNum][colNum].piece = Queen;
                board[rowNum][colNum].color = White;
                break;
            case 'P':
                board[rowNum][colNum].piece = Pawn;
                board[rowNum][colNum].color = White;
                break;
            case 'r':
                board[rowNum][colNum].piece = Rook;
                board[rowNum][colNum].color = Black;
                break;
            case 'n':
                board[rowNum][colNum].piece = Knight;
                board[rowNum][colNum].color = Black;
                break;
            case 'b':
                board[rowNum][colNum].piece = Bishop;
                board[rowNum][colNum].color = Black;
                break;
            case 'k':
                board[rowNum][colNum].piece = King;
                board[rowNum][colNum].color = Black;
                break;
            case 'q':
                board[rowNum][colNum].piece = Queen;
                board[rowNum][colNum].color = Black;
                break;
            case 'p':
                board[rowNum][colNum].piece = Pawn;
                board[rowNum][colNum].color = Black;
                break;
            }
            colNum++;
        }

    }


}


void MainWindow :: swapBoard()
{
    this->boardViewBlack = !this->boardViewBlack;
}

void MainWindow::drawBoard()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 800, 800);
    scene->setBackgroundBrush(Qt::lightGray);
    ui->graphicsView->setScene(scene);

    bool isWhite = true;
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

    int row =0, col=0;

    for(int col = 0; col < 8; col++)
    {
        for(int row = 0; row < 8; row++ )
        {
            if( this->boardViewBlack ) {
                board[row][col].xPos = col * 100;
                board[row][col].yPos = (7 - row) * 100;
            } else {
                board[row][col].xPos = col * 100;
                board[row][col].yPos = row * 100;
            }
            this->drawFigure(board[row][col]);
        }
    }

}

void MainWindow::on_pushButton_clicked()
{
    swapBoard();
    drawBoard();
}
