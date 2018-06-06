#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QSerialPort *myserie;

public slots:
    void lecture_serie();
private slots:
    void on_pushButton_clicked();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
