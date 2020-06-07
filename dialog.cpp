
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
QString Dialog :: getCurrentXML()
{
    return this->currentXML;
}
void Dialog :: loadXMLDir(QString dir)
{
    QDir directory(this->xmlDir);

    QStringList xmlFiles = directory.entryList(QStringList() << "*.xml" ,QDir::Files);
    this->currentXML = this->xmlDir;
    this->currentXML.append( xmlFiles.at(0) );

    // qDebug() << " TEST " << this->currentXML;
}

void Dialog::on_pushButton_4_clicked()
{

    if( !this->animate ) {
        ui->pushButton_4->setText("Stop animation");
        ui->checkBox_5->setEnabled(false);
        ui->spinBox_2->setEnabled(false);
        ui->comboBox->setEnabled(false);
        emit timerStart( ui->spinBox->value() );
        this->animate = true;
    } else  {
        ui->pushButton_4->setText("Start animation");
        ui->checkBox_5->setEnabled(true);
        ui->spinBox_2->setEnabled(true);
        ui->comboBox->setEnabled(true);
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
    QString filterStr;

    filterStr = ui->comboBox->currentText();
    if( ui->spinBox_2->value() < 10 ) {
        filterStr.append( QString::number(0) );
    }
    filterStr.append( QString::number(ui->spinBox_2->value()) );

    emit doFilter( filterStr, checked );

}

void Dialog::on_checkBox_4_clicked(bool checked)
{
    emit fullScreen(checked);
}

void Dialog::on_comboBox_currentIndexChanged(const QString &arg1)
{

}

void Dialog::on_spinBox_2_valueChanged(int arg1)
{

}

void Dialog::on_pushButton_4_clicked(bool checked)
{

}
