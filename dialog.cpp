
#include "mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{

    ui->setupUi(this);
    this->animate = false;
    this->xmlDir = QString ( BASE_DIR );
    this->loadXMLDir(this->xmlDir);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog :: loadXMLDir(QString dir)
{
    QDir directory(this->xmlDir);

    QStringList xmlFiles = directory.entryList(QStringList() << "*.xml" ,QDir::Files);

    int i;
    for( i = 0 ; i < xmlFiles.length() ; i++ ) {
        ui->listWidget->addItem(xmlFiles.at(i)); //(QListWidgetItem());
    }
    this->currentXML = this->xmlDir;
    this->currentXML.append( xmlFiles.at(0) );

    // qDebug() << " TEST " << this->currentXML;
}

void Dialog::on_pushButton_4_clicked()
{
    emit parseMovesXML( this->currentXML );
    if( !this->animate ) {
        ui->pushButton_4->setText("Stop animation");
        emit timerStart( ui->spinBox->value() );
        this->animate = true;
    } else  {
        ui->pushButton_4->setText("Start animation");
        emit timerStop();
        this->animate = false;
    }
}

void Dialog::setMoveNum( int val )
{
    ui->label_3->setText( QString::number( val ) );
}

void Dialog::on_checkBox_stateChanged(int arg1)
{

}

void Dialog::on_checkBox_clicked(bool checked)
{
      emit swapBoard();
}

void Dialog::on_checkBox_5_clicked(bool checked)
{
    ui->lineEdit->setEnabled(checked);
}

void Dialog::on_checkBox_4_clicked(bool checked)
{
    emit fullScreen(checked);
}
