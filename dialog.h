#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

/**/
#define BASE_DIR "/usr/share/fastchess/"

namespace Ui {
class Dialog;
class MainWindow;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void setMoveNum(int val);
    void loadXMLDir(QString dir);
     QString getCurrentXML();
    ~Dialog();
private slots:
    void on_pushButton_4_clicked();
    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_clicked(bool checked);

    void on_checkBox_5_clicked(bool checked);

    void on_checkBox_4_clicked(bool checked);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_4_clicked(bool checked);



signals:
    void timerStart(int val);
    void timerStop();
    void swapBoard();
    void parseMovesXML(QString filename);
    void fullScreen(bool mode);
    void doFilter(QString eco, bool active);
private:
    Ui::Dialog *ui;
    QWindow *win;
    bool animate;
    QString xmlDir;
    QString currentXML;
};

#endif // DIALOG_H
