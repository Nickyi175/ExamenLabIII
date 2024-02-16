#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();

    void on_addbtn_pressed();

    void on_volveradd_pressed();

    void on_add_pressed();

    void on_Buscar_pressed();

    void on_infobtn_pressed();

    void on_lisbtn_pressed();

    void on_crear_pressed();

    void on_volverSongs_pressed();

    void on_regresarInfo_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
