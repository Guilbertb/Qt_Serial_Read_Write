#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myserie = new QSerialPort(this);
    myserie->setPortName(QLatin1String("/dev/ttyACM0"));
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
    myserie->setBaudRate(QSerialPort::Baud9600,QSerialPort::AllDirections);
    myserie->setDataBits(QSerialPort::Data8);
    myserie->setFlowControl(QSerialPort::NoFlowControl);
    myserie->setParity(QSerialPort::NoParity);
    myserie->setStopBits(QSerialPort::OneStop);
    myserie->waitForBytesWritten(100);
    myserie->waitForReadyRead(100);
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
    QString Str="Bonjour"; // Message à envoyer
    int Nb=myserie->write(Str.toLocal8Bit(),Str.length());
    // La méthode toAscii() de la classe QString Qt4.8 est remplacée
    // par toLocal8Bit()de la classe QString Qt5.2

}


void MainWindow::lecture_serie ()
{
char Data[10];
for (int i=0;i<sizeof(Data);i++)Data[i]=0;
int Nb= myserie->readLine(Data,sizeof(Data));
//int Nb= myserie->read(Data,sizeof(Data));
if(Nb)
{ // Des données ont été reçues
qDebug() << Data ;
}
}

