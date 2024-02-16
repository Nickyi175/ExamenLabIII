#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ctunes.h"
#include "genero.h"
#include <QTimeEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    //ui->stackedWidget->setCurrentIndex(1);

}



void MainWindow::on_addbtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_volveradd_pressed()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_add_pressed()
{
CTunes ct;
Genero::genero Enumeracion;
QString nombre=ui->nombretxt->text();
string name=nombre.toStdString();
QString cantante=ui->cantantetxt->text();
string namecantante=cantante.toStdString();
double precio=ui->preciotxt->text().toDouble();
QString genero1=ui->generCB->currentText();
string gen2=genero1.toStdString();
QTime tiempo = ui->timeEdit->time();
QString timeString = tiempo.toString("mm:ss");
if(!ui->nombretxt->text().isEmpty() && !ui->cantantetxt->text().isEmpty() && !ui->preciotxt->text().isEmpty()){
    if (genero1 == "Pop") {
        Enumeracion = Genero::POP;
    } else if (genero1 == "Rock") {
        Enumeracion = Genero::ROCK;
    } else if (genero1 == "Rap") {
        Enumeracion = Genero::RAP;
    } else if (genero1 == "Dance") {
        Enumeracion = Genero::DANCE;
    } else if (genero1 == "Reggae") {
        Enumeracion = Genero::REGGAE;
    } else if (genero1 == "Electronica") {
        Enumeracion = Genero::ELECTRONICA;
    } else if (genero1 == "Ranchera") {
        Enumeracion = Genero::RANCHERA;
    }
    ct.addSong(name,namecantante,Enumeracion,precio,timeString);
    ui->nombretxt->setText("");
    ui->cantantetxt->setText("");
    ui->preciotxt->setText("");

}else
    QMessageBox::information(nullptr, "Error", "Espacios Vacios.");
}


void MainWindow::on_Buscar_pressed()
{
    CTunes ct;
    int cod=ui->codtxt->text().toInt();
    string info = ct.infoSong(cod);
    QString inf = QString::fromStdString(info);
    ui->textEdit->setText(inf);

}


void MainWindow::on_infobtn_pressed()
{
    ui->stackedWidget->setCurrentIndex(3);
}

