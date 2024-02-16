#include "ctunes.h"
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QDate>
#include <fstream>
#include <iostream>
#include <QMessageBox>
#include <stdlib.h>
#include <genero.h>
#include <QDebug>

struct Cancion
{
    int codigo;
    QString cancion;
    QString singer;
    QString genre;
    QString duracion;
    double precio;
    int estrellasT;
    int cantReviews;

};

struct descarga
{
    int codigoDownl;
    QString fecha;
    int codigoSong;
    QString Cname;
    double price;
};

QFile CodigosArchivos ("codigos.itn");
QFile SongsArchivo ("songs.itn");
QFile DownloadsArchivos ("downloads.itn");


QDataStream escribirS (&SongsArchivo);
QDataStream leerS (&SongsArchivo);
QDataStream leerC (&CodigosArchivos);
QDataStream escribirC (&CodigosArchivos);
QDataStream escribirD (&DownloadsArchivos);


CTunes::CTunes() {
    struct Cancion
    {
        int codigo;
        QString cancion;
        QString singer;
        QString genre;
        QString duracion;
        double precio;
        int estrellasT;
        int cantReviews;

    };

    struct descarga
    {
        int codigoDownl;
        QString fecha;
        int codigoSong;
        QString Cname;
        double price;
    };
    SongsArchivo.open(QIODevice::ReadWrite);
    DownloadsArchivos.open(QIODevice::ReadWrite);
    CodigosArchivos.open(QIODevice::ReadWrite);

    if(!SongsArchivo.isOpen()){
        exit(0);
    }
    if(!CodigosArchivos.isOpen()){
        exit(0);
    }
    if(!DownloadsArchivos.isOpen()){
        exit(0);
    }
  /*  if(CodigosArchivos.size()==0){
        escribirC<<1;
        CodigosArchivos.seek(CodigosArchivos.size());
        escribirC<<1;
    }
    }

/*int CTunes::getCodigo(long offset){
    if(offset==0){
        return
    }
}
*/

    if(CodigosArchivos.size() == 0) {
        int codecancion = 1;
        int codedownload = 1;
        escribirC << codecancion << codedownload;
    } else {
        leerC >> codecancion >> codedownload;
    }
    CodigosArchivos.close();
    }

    int CTunes::getCodigo(long offset){
        CodigosArchivos.open(QIODevice::ReadWrite);
        int code=1,download=0,valor=0;
        leerC>>code>>download;
        if(offset==0){
            valor=code;
            code++;
            CodigosArchivos.seek(0);
            escribirC<<code<<download;
        }else if(offset==4){
            valor=download;
            download++;
            CodigosArchivos.seek(0);
            escribirC<<code<<download;
        }
        CodigosArchivos.close();
        return valor;
    }

    void CTunes::addSong(string nombre,string Cantante, Genero::genero generoCantante,double precio,QString duracion){
        SongsArchivo.open(QIODevice::ReadWrite);

        string generoSong;
        if (generoCantante == Genero::DANCE) {
            generoSong = "Dance";
        } else if (generoCantante == Genero::ELECTRONICA) {
            generoSong = "Electronica";
        } else if (generoCantante == Genero::POP) {
            generoSong = "Pop";
        } else if (generoCantante == Genero::RANCHERA) {
            generoSong = "Ranchera";
        } else if (generoCantante == Genero::RAP) {
            generoSong = "Rap";
        } else if (generoCantante == Genero::REGGAE) {
            generoSong = "Reggae";
        } else if (generoCantante == Genero::ROCK) {
            generoSong = "Rock";
        }

        Cancion addS;
        addS.codigo=getCodigo(0);
        addS.cancion=QString::fromStdString(nombre).toUtf8();
        addS.singer=QString::fromStdString(Cantante).toUtf8();
        addS.genre = QString::fromStdString(generoSong);
        addS.precio=precio;
        addS.estrellasT=0;
        addS.cantReviews=0;
        addS.duracion=duracion;
        SongsArchivo.seek(SongsArchivo.size());
        escribirS<<addS.codigo<<addS.cancion<<addS.singer<<addS.genre<<addS.precio<<addS.estrellasT<<addS.cantReviews<<addS.duracion;
        SongsArchivo.flush();
        QMessageBox::information(nullptr, "Agregar Cancion", "Cancion Agregada Correctamente.");

    }

    /*void ctunes::reviewSong(int code, int stars) {

        /*if(stars<0||stars>5){
        throw std::invalid_argument("La cantidad de estrellas debe estar entre 0 y 5.");
    }*/
    /*
        int contarreview,estrellas;
        songsArchivo.seek(0);
        Cancion aggCancion;
        while (!songsArchivo.atEnd()) {
            qint64 pos = songsArchivo.pos();
            LeerCancion >> aggCancion.code>> aggCancion.nombre >> aggCancion.cantante >> aggCancion.generoCantante
                >> aggCancion.precio >> aggCancion.cantEstrellas >> aggCancion.reviews
                >> aggCancion.duracion;

            if (aggCancion.code == code) {
                if(stars>=0 && stars<=5){
                    contarreview=aggCancion.reviews+1;
                    estrellas=aggCancion.cantEstrellas+stars;
                    songsArchivo.seek(pos);
                    EscribirCancion << aggCancion.code<< aggCancion.nombre << aggCancion.cantante <<aggCancion.generoCantante<<aggCancion.precio << estrellas << contarreview<< aggCancion.duracion;
                    songsArchivo.flush();
                    QMessageBox::information(nullptr, "Review", "Review.");
                    break;
                }else
                    throw InvalidRateException(stars);
            }
        }


    }
*/
    string CTunes::downloadSong(int codeSong, string cliente) {
        SongsArchivo.seek(0);
        Cancion cancioncita;
        while(!SongsArchivo.atEnd()){
            leerS >> cancioncita.codigo >> cancioncita.cancion >> cancioncita.singer >> cancioncita.genre
                >> cancioncita.precio >> cancioncita.estrellasT >> cancioncita.cantReviews
                >> cancioncita.duracion;
            if (cancioncita.codigo == codeSong) {
                descarga dw;
                dw.codigoDownl = getCodigo(4);
                QDate fechainicial = QDate::currentDate();
                dw.fecha = QDate::currentDate().toString("yyyy-MM-dd");

                // Usar QString para cliente también
                dw.Cname = QString::fromStdString(cliente);
                dw.codigoSong = cancioncita.codigo;
                DownloadsArchivos.seek(DownloadsArchivos.size());
                escribirD << dw.codigoDownl<< dw.fecha << dw.codigoSong << dw.Cname;
                return "Codigo de descarga: "+to_string(dw.codigoDownl)+"\nFecha: "+dw.fecha.toStdString()+"\n "+dw.Cname.toStdString() + " Por bajar " + cancioncita.cancion.toStdString()+" a un costo de Lps. "+to_string(cancioncita.precio);

            }
        }
        return "Cancion no encontrada";
    }


    QString CTunes::songs(QString txtFile)
    {
        QString texto="";
        QFile archivo(txtFile);
        archivo.open(QIODevice::ReadWrite);
        //Validar que este abierto
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return "¡ERROR! ¡No se pudo abrir el archivo!";
        }

        archivo.resize(0);
        SongsArchivo.seek(0);
        QTextStream salida(&archivo);



        while (!SongsArchivo.atEnd()) {
            Cancion cancioncita;
            leerS >> cancioncita.codigo >> cancioncita.cancion >> cancioncita.singer >> cancioncita.genre
                >> cancioncita.precio >> cancioncita.estrellasT >> cancioncita.cantReviews
                >> cancioncita.duracion;

            double rating = cancioncita.cantReviews != 0 ? static_cast<double>(cancioncita.estrellasT) / cancioncita.cantReviews : 0.0;
            //CREAR TEXTO PARA EL REPORTE
            texto += " - Código ---- Título ---- Cantante ---- Duración ---- Precio ---- Rating de la Canción----\n"+QString::number(cancioncita.codigo) + "   -   " + cancioncita.cancion + "   -   " +
                    cancioncita.singer + " - " + cancioncita.duracion + " - " +
                    QString::number(cancioncita.precio) + "   -   " + QString::number(rating) + "\n";

        }

        salida<<texto+"\n";
        archivo.close();

        return texto;
    }



    string CTunes::infoSong(int codeSong) {
        SongsArchivo.seek(0);
        while (!SongsArchivo.atEnd()) {
            Cancion aggCancion;
            leerS >> aggCancion.codigo >> aggCancion.cancion >> aggCancion.singer >> aggCancion.genre
                >> aggCancion.precio >> aggCancion.estrellasT >> aggCancion.cantReviews
                >> aggCancion.duracion;
            if (aggCancion.codigo == codeSong) {
                string texto;
                double estrellas = static_cast<double>(aggCancion.estrellasT);
                double review= static_cast<double>(aggCancion.cantReviews);
                double rating=estrellas/review;
                texto = "Código: " + to_string(aggCancion.codigo) + "\nCanción: " + aggCancion.cancion.toStdString() + "\nCantante: "
                        + aggCancion.singer.toStdString() + "\nGénero: " + aggCancion.genre.toStdString() + "\nPrecio: " +
                        to_string(aggCancion.precio) + "\nReviews: " + to_string(aggCancion.cantReviews) + "\nEstrellas: " +
                        to_string(aggCancion.estrellasT)+"\nRating: "+ to_string(rating) + "\nDuración: " + aggCancion.duracion.toStdString();
                return texto;
            }
        }
        return "¡ERROR! ¡Cancion inexistente!";
    }




    template <class tipodato>
    void CTunes::buscarCode(tipodato codigo){
        CodigosArchivos.open(QIODevice::ReadOnly);
        CodigosArchivos.seek(0);
        int code,download;
        leerC>>code>>download;
        if(code==codigo){
            return;
        }

    }
