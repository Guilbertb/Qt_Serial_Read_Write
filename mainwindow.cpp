#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QDebug>


    QString Str="G28\n"; // Message à envoyer

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit->setText(Str);

    myserie = new QSerialPort(this);
    myserie->setPortName(QLatin1String("/dev/ttyUSB0"));
    // Ouverture en écriture et lecture
    if(myserie->open(QIODevice::ReadWrite) == true)
    {
    qDebug() << "open ok";
    }
    else
    {
    qDebug() << "open pb";
    return;
    }
    // Configuration du port
    myserie->setBaudRate(250000,QSerialPort::AllDirections);
    myserie->setDataBits(QSerialPort::Data8);
    myserie->setFlowControl(QSerialPort::NoFlowControl);
    myserie->setParity(QSerialPort::NoParity);
    myserie->setStopBits(QSerialPort::OneStop);
    myserie->waitForBytesWritten(50);
    myserie->waitForReadyRead(50);
    // Connexion du signal readyRead au slot lecture_serie()
    connect(myserie,SIGNAL(readyRead()),this,SLOT(lecture_serie()));


}

MainWindow::~MainWindow()
{
    myserie->close();
    // Fermeture du port

    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    Str=ui->lineEdit->text()+"\n";

    //int Nb=
    myserie->write(Str.toLocal8Bit(),Str.length());

    qDebug() << Str;
    // La méthode toAscii() de la classe QString Qt4.8 est remplacée
    // par toLocal8Bit()de la classe QString Qt5.2

}


void MainWindow::lecture_serie ()
{
char Data[200];
for (int i=0;i<sizeof(Data);i++)Data[i]=0;
int Nb= myserie->readLine(Data,sizeof(Data));
//int Nb= myserie->read(Data,sizeof(Data));
if(Nb)
{ // Des données ont été reçues
    ui->textBrowser->append(Data);

qDebug() << Data ;
}
}

