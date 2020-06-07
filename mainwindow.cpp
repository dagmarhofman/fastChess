#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setWindowTitle(trUtf8("Chess"));

    this->currentMove = 0;
    this->currentOpening = 0;
    this->openingShowCount = 0;

    for(int i=0;i<allMoves.size();i++) {
        qDebug() << i << " " << allMoves.at(i).opening;
    }

    initBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    drawBoard();

    ui->ecoLabel->setAlignment(Qt::AlignCenter);
    ui->variantLabel->setAlignment(Qt::AlignCenter);
    ui->openingLabel->setAlignment(Qt::AlignCenter);

    ui->ecoLabel->setStyleSheet("color: blue; ");
    ui->openingLabel->setStyleSheet("color: blue;");
    ui->variantLabel->setStyleSheet("color: blue;");

    this->timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));


    myPanel = new Dialog(this);
    connect(myPanel, SIGNAL(parseMovesXML(QString)), this, SLOT(parseMovesXML(QString)));
    connect(myPanel, SIGNAL(timerStart(int)), this, SLOT(timerStart(int)));
    connect(myPanel, SIGNAL(timerStop()), this, SLOT(timerStop()));
    connect(myPanel, SIGNAL(swapBoard()), this, SLOT(swapBoard()));
    connect(myPanel, SIGNAL(fullScreen(bool)), this, SLOT(showFullScreen(bool)));
    connect(myPanel, SIGNAL(doFilter(QString)), this, SLOT(filterSlot(QString)));
    this->myPanel->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::timerStart( int val )
{
    this->timer->setInterval(val);
    this->timer->start();
}

void MainWindow::timerStop()
{
    this->timer->stop();
}

void MainWindow::showFullScreen(bool mode)
{
    mode ? QMainWindow::showFullScreen() : QMainWindow::showNormal();
}

void MainWindow::parseMovesXML( QString filename )
{
    QDomDocument doc;

    QFile file( filename );
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() <<"Could not read file";
        return;
    }
    else{
        if(!doc.setContent(&file)){
            qDebug()<<"Could not read xml document";
            file.close();
            return;
        }
        file.close();
    }

    QDomElement element = doc.documentElement();

    chessMoves fieldRecord;

    QDomElement root = doc.firstChildElement("chessmoves");
    QDomElement elt = root.firstChildElement("item");
    QString FEN;
    for (; !elt.isNull(); elt = elt.nextSiblingElement("item")) {

        QString tmp;
        tmp = elt.firstChildElement("ECO").text().toUtf8();
        fieldRecord.eco = tmp.trimmed() ;
        fieldRecord.opening = elt.firstChildElement("Opening").text().toUtf8();
        fieldRecord.variant = elt.firstChildElement("Variation").text().toUtf8();
        fieldRecord.display = true;

        QDomElement moves = elt.firstChildElement("Moves");
        QDomElement moveItem = moves.firstChildElement("item");

        fieldRecord.chessMoves.clear();

        fieldRecord.chessMoves.append( "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" );

        for (; !moveItem.isNull(); moveItem = moveItem.nextSiblingElement("item")) {
            FEN = moveItem.firstChildElement("FEN").text().toUtf8();
            fieldRecord.chessMoves.append( FEN );
        }

        this->allMoves.append(fieldRecord);
    }

    return;

}

void MainWindow::filterSlot(QString eco)
{
    int i;
    for( i = 0; i < this->allMoves.size() ; i++) {
        chessMoves tmp = this->allMoves.at(i);
        tmp.display = false;

        qDebug() << "TEST" << tmp.eco << "TEST" << eco << "TEST";
        if( tmp.eco.compare(eco) == 0  )
            tmp.display = true;

        this->allMoves.replace(i,tmp );
    }
    this->currentOpening = 0;
}

void MainWindow::timerSlot()
{
    myPanel->setMoveNum(this->currentMove);

    while( this->allMoves.at(this->currentOpening).display == false )
        this->currentOpening++;


    //draw next move
    if(this->currentMove < this->allMoves.at(this->currentOpening).chessMoves.size() - 1 )    {
        this->currentMove++;
        initBoard(QString(this->allMoves.at(this->currentOpening).chessMoves.at(this->currentMove)));
        drawBoard();
    } else { //last move ?

        //draw that last move
        if(this->currentMove < this->allMoves.at(this->currentOpening).chessMoves.size() - 1 )    {
            initBoard(QString(this->allMoves.at(this->currentOpening).chessMoves.at(this->currentMove)));
            drawBoard();
            this->currentMove++;
        } else { // check next opening
            initBoard(QString(this->allMoves.at(this->currentOpening).chessMoves.at(this->currentMove)));
            drawBoard();

            this->openingShowCount++;

            this->currentMove = 0;

            if( this->openingShowCount > 1) {
                this->currentOpening++;
                this->openingShowCount = 0;
            }


            initBoard(" rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            drawBoard();
            ui->ecoLabel->setText(QString(allMoves.at(this->currentOpening).eco.toUtf8()));
            ui->variantLabel->setText(QString(allMoves.at(this->currentOpening).variant.toUtf8()));
            ui->openingLabel->setText(QString(allMoves.at(this->currentOpening).opening.toUtf8()));


        }
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

    i = 0;
    do
    {
        c = fen.toStdString().c_str()[i++];

        if( c == ' ' || c == '\n')
            continue;

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

    } while( !(colNum == 8 && rowNum == 7) );


}


void MainWindow :: swapBoard()
{
    this->boardViewBlack = !this->boardViewBlack;
    drawBoard();
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

}

void MainWindow::on_pushButton_2_clicked()
{

    if(this->currentOpening < this->allMoves.size() ) {
        this->currentOpening++;
    }

    ui->ecoLabel->setText(QString(allMoves.at(this->currentOpening).eco.toUtf8()));
    ui->variantLabel->setText(QString(allMoves.at(this->currentOpening).variant.toUtf8()));
    ui->openingLabel->setText(QString(allMoves.at(this->currentOpening).opening.toUtf8()));

    this->currentMove = 0;

    drawBoard();
}

void MainWindow::on_pushButton_3_clicked()
{
    qDebug() << allMoves.at(this->currentOpening).opening;

    if(this->currentOpening > 0 )
        this->currentOpening--;

    ui->ecoLabel->setText(QString(allMoves.at(this->currentOpening).eco.toUtf8()));
    ui->variantLabel->setText(QString(allMoves.at(this->currentOpening).variant.toUtf8()));
    ui->openingLabel->setText(QString(allMoves.at(this->currentOpening).opening.toUtf8()));

    this->currentMove = 0;

    drawBoard();

}

void MainWindow::on_pushButton_5_clicked()
{
    if(this->currentMove < this->allMoves.at(this->currentOpening).chessMoves.size() - 1 )    {
        this->currentMove++;
        initBoard(QString(this->allMoves.at(this->currentOpening).chessMoves.at(this->currentMove)));
        drawBoard();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(this->currentMove > 0 )    {
        this->currentMove--;
        initBoard(QString(this->allMoves.at(this->currentOpening).chessMoves.at(this->currentMove)));
        drawBoard();
    }
}
