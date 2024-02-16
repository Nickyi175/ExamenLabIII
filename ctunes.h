#ifndef CTUNES_H
#define CTUNES_H
#include <fstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <qfile.h>
#include <genero.h>
using namespace std;

class CTunes
{
public:
    CTunes();
    int getCodigo(long);
    void addSong(string, string, Genero::genero,double,QString);
    void reviewSong(int, int);
    string downloadSong(int , string );
    QString songs(string);
    string infoSong(int);
   // bool buscarCode(int);
    template <typename tipodato>
    void buscarCode(tipodato codigo);
private:
    int codecancion = 1;
    int codedownload = 1;

};

#endif // CTUNES_H
