#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    int centerX;
    int centerY;

    struct parametrMacierz{
        double translacjaX;
        double translacjaY;
        double startX;
        double startY;
        double rotacja;
        double skalaX;
        double sklalaY;
        double pochylX;
        double pochylY;

    };

    struct parametrMacierz3D{
        int translacjaX;
        int translacjaY;
        int translacjaZ;

        int rotacjaX;
        int rotacjaY;
        int rotacjaZ;

        int skalaX;
        int sklalaY;
        int sklalaZ;

        int f;
    };

    parametrMacierz pm = {0,0,0,0,0,10,10,0,0};

    parametrMacierz3D pm3D = {
        0,0,100,
        0,0,0,
        10,10,10,
        100
    };

private slots:


    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

    void on_pushButton_clicked();

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_5_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);


    double* zwrocMacierz(bool);

    double* setMacierzTranslacji(bool);

    double* setMacierzSkalowanie(bool);

    double* setMacierzTranslacjiStart(bool arbuz);

    double* setMacierzPochyleniaX(bool);

    double* setMacierzPochyleniaY(bool);

    double* setMacierzRotacji(bool);

    double* pomnurzMacierzeWszystkie(double* TS, double* TSR, double* T, double* S, double* PX, double* PY, double* R, bool o);

    double* setMacierzTranslacjiStart3D(bool arbuz);

    double* pomnurzMacierze(double* mLewa, double* mPrawa);

    double* pomnurzMacierzeWszystkie3D(double* T, double* S, double* RX, double* RY, double* RZ, double* ST, double* STR, bool original);

    double* wyswietlMacierz(double* macierz);

    double* setMacierzTranslacji3D(bool regular);

    double* setMacierzSkalowanie3D(bool regular);

    double* setMacierzRotacjiX3D(bool original);

    double* setMacierzRotacjiY3D(bool original);

    double* setMacierzRotacjiZ3D(bool original);

    double* pomnurzMacierze3D(double* mLewa, double* mPrawa);

    double* zwrocMacierz3D(bool original);

    void on_horizontalSlider_8_valueChanged(int value);

    void on_horizontalSlider_9_valueChanged(int value);

    void on_horizontalSlider_6_valueChanged(int value);

    void on_horizontalSlider_7_valueChanged(int value);

    void wypiszMacierz3D(double* macierz);

    void on_horizontalSlider_10_valueChanged(int value);



    void on_radioButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
