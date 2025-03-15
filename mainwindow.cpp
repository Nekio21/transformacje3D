#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QColorDialog>
#include <math.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centerX = ui->widget->im.width();
    centerY = ui->widget->im.height();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_10_valueChanged(int value)
{
   pm3D.f = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}

void MainWindow::on_radioButton_toggled(bool checked)
{
    ui->widget->perspectiveMode = checked;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    pm3D.translacjaX = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    pm3D.translacjaY = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}


void MainWindow::on_horizontalSlider_8_valueChanged(int value)
{
    pm3D.translacjaZ = value;


    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value)
{
    pm3D.skalaX = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}


void MainWindow::on_horizontalSlider_5_valueChanged(int value)
{
    pm3D.sklalaY = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}



void MainWindow::on_horizontalSlider_9_valueChanged(int value)
{
    pm3D.sklalaZ = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    pm3D.rotacjaX = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}

void MainWindow::on_horizontalSlider_6_valueChanged(int value)
{
    pm3D.rotacjaY = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}


void MainWindow::on_horizontalSlider_7_valueChanged(int value)
{
    pm3D.rotacjaZ = value;

    ui->widget->drawMacierz3D(zwrocMacierz3D(true), pm3D.f);
}


void MainWindow::on_pushButton_clicked()
{
    pm3D = {
        0,0,100,
        0,0,0,
        10,10,10,
        100
    };

    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider_2->setValue(0);
    ui->horizontalSlider_8->setValue(100);

    ui->horizontalSlider_3->setValue(0);
    ui->horizontalSlider_6->setValue(0);
    ui->horizontalSlider_7->setValue(0);


    ui->horizontalSlider_4->setValue(10);
    ui->horizontalSlider_5->setValue(10);
    ui->horizontalSlider_9->setValue(10);

    double* macierz = zwrocMacierz3D(true);

    wypiszMacierz3D(macierz);

    ui->widget->drawMacierz3D(macierz, pm3D.f);
}


double* MainWindow::zwrocMacierz(bool original){

    double* macierzTranslacjiStart;
    double* macierzTranslacjiStartReverse;
    double* macierzTranslacji;
    double* macierzSkali;
    double* macierzPochyleniaX;
    double* macierzPochyleniaY;
    double* macierzRotacyjnie;
    double* macierzFinalna;
    double* macierzStartowa;

    macierzTranslacjiStart = setMacierzTranslacjiStart(original);
    macierzTranslacjiStartReverse = setMacierzTranslacjiStart(!original);
    macierzTranslacji = setMacierzTranslacji(original);
    macierzSkali = setMacierzSkalowanie(original);
    macierzPochyleniaX = setMacierzPochyleniaX(original);
    macierzPochyleniaY = setMacierzPochyleniaY(original);
    macierzRotacyjnie = setMacierzRotacji(original);


    macierzFinalna = pomnurzMacierzeWszystkie(macierzTranslacjiStart, macierzTranslacjiStartReverse, macierzTranslacji,macierzSkali, macierzPochyleniaX, macierzPochyleniaY, macierzRotacyjnie,original);


    return macierzFinalna;
}

double* MainWindow::zwrocMacierz3D(bool original){

    double* macierzTranslacji;
    double* macierzScali;

    double* macierzRotacjiX;
    double* macierzRotacjiY;
    double* macierzRotacjiZ;

    double* macierzStart;
    double* macierzStartReverse;

    double* macierzFinalna;


    macierzTranslacji = setMacierzTranslacji3D(original);
    macierzScali = setMacierzSkalowanie3D(original);

    macierzRotacjiX = setMacierzRotacjiX3D(original);
    macierzRotacjiY = setMacierzRotacjiY3D(original);
    macierzRotacjiZ = setMacierzRotacjiZ3D(original);

    macierzStart = setMacierzTranslacjiStart3D(true);
    macierzStartReverse = setMacierzTranslacjiStart3D(false);

    macierzFinalna = pomnurzMacierzeWszystkie3D(macierzTranslacji, macierzScali, macierzRotacjiX, macierzRotacjiY, macierzRotacjiZ, macierzStart, macierzStartReverse, true);

    return macierzFinalna;
}

double* MainWindow::setMacierzTranslacji(bool regular){

    double* macierz;
    int znak = 1;

    if(regular){
        macierz = new double[9]{
            1, 0,  pm.translacjaX,
            0, 1,  pm.translacjaY,
            0, 0, 1
        };
    }else{
        macierz = new double[9]{
            1, 0,  -pm.translacjaX,
            0, 1,  -pm.translacjaY,
            0, 0, 1
        };
    }

    return macierz;
}

double* MainWindow::setMacierzTranslacji3D(bool regular){

    double* macierz;
    int znak = 1;

    if(regular){
        macierz = new double[16]{
            1, 0, 0, (double)pm3D.translacjaX,
            0, 1, 0, (double)pm3D.translacjaY,
            0, 0, 1, (double)pm3D.translacjaZ,
            0, 0, 0, 1
        };
    }else{
        macierz = new double[16]{
            1, 0, 0, -(double)pm3D.translacjaX,
            0, 1, 0, -(double)pm3D.translacjaY,
            0, 0, 1, -(double)pm3D.translacjaZ,
            0, 0, 0, 1
        };
    }

    return macierz;
}

double* MainWindow::setMacierzTranslacjiStart(bool arbuz){

    double* macierz;

    if(arbuz){
        macierz = new double[9]{
            1, 0,  ui->widget->imKelner.width()/2.0,
            0, 1,  ui->widget->imKelner.height()/2.0,
            0, 0, 1
        };
    }else{
        macierz = new double[9]{
            1, 0,  -ui->widget->imKelner.width()/2.0,
            0, 1,  -ui->widget->imKelner.height()/2.0,
            0, 0, 1
        };
    }

    return macierz;
}

double* MainWindow::setMacierzTranslacjiStart3D(bool arbuz){

    double* macierz;

    cout<<"centerX:"<<centerX<<endl;

    if(arbuz){
        macierz = new double[16]{
            1, 0, 0, (double)ui->widget->im.width()/2,
            0, 1, 0, (double)ui->widget->im.height()/2,
            0, 0, 1, 200,
            0, 0, 0, 1
        };
    }else{
        macierz = new double[16]{
            1, 0, 0, (double)-ui->widget->im.width()/2,
            0, 1, 0, (double)-ui->widget->im.height()/2,
            0, 0, 1, -200,
            0, 0, 0, 1
        };
    }

    return macierz;
}

double* MainWindow::setMacierzSkalowanie(bool regular){

    double* macierz;

    if(regular){
        macierz = new double[9]{
                pm.skalaX/10, 0, 0,
                0, pm.sklalaY/10, 0,
                0, 0,1
        };
    }else{
        macierz = new double[9]{
                10/pm.skalaX, 0, 0,
                0, 10/pm.sklalaY, 0,
                0, 0,1
        };
    }



    return macierz;
}

double* MainWindow::setMacierzSkalowanie3D(bool regular){

    double* macierz;

    if(regular){
        macierz = new double[16]{
                pm3D.skalaX/(double)10, 0, 0,0,
                0, pm3D.sklalaY/(double)10, 0,0,
                0, 0,pm3D.sklalaZ/(double)10, 0,
                0, 0, 0, 1
        };
    }else{
        macierz = new double[16]{
                10/(double)pm3D.skalaX, 0, 0,0,
                0, 10/(double)pm3D.sklalaY, 0,0,
                0, 0, 10/(double)pm3D.sklalaZ, 0,
                0, 0, 0, 1
        };
    }



    return macierz;
}

double* MainWindow::setMacierzRotacji(bool original){

    double* macierz;

    if(original){
        macierz = new double[9]{
            cos(pm.rotacja*M_PI/(double)180), -sin(pm.rotacja*M_PI/(double)180), 0,
            sin(pm.rotacja*M_PI/(double)180), cos(pm.rotacja*M_PI/(double)180), 0,
            0, 0, 1
        };
    }else{
        macierz = new double[9]{
            cos(pm.rotacja*M_PI/(double)180), sin(pm.rotacja*M_PI/(double)180), 0,
            -sin(pm.rotacja*M_PI/(double)180), cos(pm.rotacja*M_PI/(double)180), 0,
            0, 0, 1
        };
    }



    return macierz;
}


double* MainWindow::setMacierzRotacjiZ3D(bool original){

    double* macierz;

    if(original){
        macierz = new double[16]{
            cos(pm3D.rotacjaZ*M_PI/(double)180), -sin(pm3D.rotacjaZ*M_PI/(double)180), 0, 0,
            sin(pm3D.rotacjaZ*M_PI/(double)180), cos(pm3D.rotacjaZ*M_PI/(double)180), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
    }else{
        macierz = new double[16]{
                cos(pm3D.rotacjaZ*M_PI/(double)180), sin(pm3D.rotacjaZ*M_PI/(double)180), 0, 0,
                -sin(pm3D.rotacjaZ*M_PI/(double)180), cos(pm3D.rotacjaZ*M_PI/(double)180), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };
    }

    cout<<"****************** "<<endl;

    cout<<"ROTACJA Z => "<<pm3D.rotacjaZ<<endl;

    wypiszMacierz3D(macierz);

    cout<<"******************"<<endl;


    return macierz;
}

double* MainWindow::setMacierzRotacjiY3D(bool original){

    double* macierz;

    if(original){
        macierz = new double[16]{
                cos(pm3D.rotacjaY*M_PI/(double)180), 0, sin(pm3D.rotacjaY*M_PI/(double)180), 0,
                0, 1, 0, 0,
                -sin(pm3D.rotacjaY*M_PI/(double)180), 0, cos(pm3D.rotacjaY*M_PI/(double)180), 0,
                0, 0, 0, 1
        };
    }else{
        macierz = new double[16]{
                cos(pm3D.rotacjaY*M_PI/(double)180), 0, -sin(pm3D.rotacjaY*M_PI/(double)180), 0,
                0, 1, 0, 0,
                sin(pm3D.rotacjaY*M_PI/(double)180), 0, cos(pm3D.rotacjaY*M_PI/(double)180), 0,
                0, 0, 0, 1
        };
    }

    cout<<"******************"<<endl;

    cout<<"ROTACJA Y => "<<pm3D.rotacjaY<<endl;

    wypiszMacierz3D(macierz);

    cout<<"******************"<<endl;

    return macierz;
}

double* MainWindow::setMacierzRotacjiX3D(bool original){

    double* macierz;

    if(original){
        macierz = new double[16]{
            1, 0, 0, 0,
            0, cos(pm3D.rotacjaX*M_PI/180), -sin(pm3D.rotacjaX*M_PI/180), 0,
            0, sin(pm3D.rotacjaX*M_PI/180), cos(pm3D.rotacjaX*M_PI/180), 0,
            0, 0, 0, 1
        };
    }else{
        macierz = new double[16]{
                1, 0, 0, 0,
                0, cos(pm3D.rotacjaX*M_PI/180), sin(pm3D.rotacjaX*M_PI/180), 0,
                0, -sin(pm3D.rotacjaX*M_PI/180), cos(pm3D.rotacjaX*M_PI/180), 0,
                0, 0, 0, 1
        };
    }

    cout<<"******************"<<endl;

    cout<<"ROTACJA X => "<<pm3D.rotacjaX<<endl;

    wypiszMacierz3D(macierz);

    cout<<"******************"<<endl;

    return macierz;
}

double* MainWindow::setMacierzPochyleniaX(bool original){

    double* macierz;

    if(original){
        macierz = new double[9]{
            1, pm.pochylX, 0,
            0, 1, 0,
            0, 0, 1
        };
    }else{
        macierz = new double[9]{
            1, -pm.pochylX, 0,
            0, 1, 0,
            0, 0, 1
        };
    }

    return macierz;
}

double* MainWindow::setMacierzPochyleniaY(bool original){

    double* macierz;

    if(original){
        macierz = new double[9]{
            1, 0, 0,
            pm.pochylY, 1, 0,
            0, 0, 1
        };
    }else{
        macierz = new double[9]{
            1, 0, 0,
            -pm.pochylY, 1, 0,
            0, 0, 1
        };
    }

    return macierz;
}

double* MainWindow::pomnurzMacierze(double* mLewa, double* mPrawa){
    double* macierz = new double[9];

    for(int i=0;i<9;i++){
        macierz[i] = mLewa[3*(i/3)] * mPrawa[0 + (i%3)] + mLewa[3*(i/3)+1] * mPrawa[3+ (i%3)] + mLewa[3*(i/3)+2] * mPrawa[6 + (i%3)];
    }


    return macierz;
}

double* MainWindow::pomnurzMacierze3D(double* mLewa, double* mPrawa){
    double* macierz = new double[16];

    for(int i=0;i<16;i++){
        macierz[i] =
                mLewa[4*(i/4)] * mPrawa[0 + (i%4)]
                + mLewa[4*(i/4)+1] * mPrawa[4+ (i%4)]
                + mLewa[4*(i/4)+2] * mPrawa[8 + (i%4)]
                + mLewa[4*(i/4)+3] * mPrawa[12 + (i%4)];
    }


    return macierz;
}

double* MainWindow::wyswietlMacierz(double* macierz){
    for(int i=0;i<9;i++){
        cout<<macierz[i]<<" ";
        if(i%3==2)cout<<endl;
    }
}

double* MainWindow::pomnurzMacierzeWszystkie(double* ST, double* STR, double* T, double* S, double* PX, double* PY, double* R, bool original){

    double* macierz[] = {STR,S,R,PX,PY,T, ST};

    double* poprzedniaMacierz;
    double* newMacierz;

    if(!original){
        macierz[0] = ST;
        macierz[1] = T;
        macierz[2] = PY;

        macierz[3] = PX;
        macierz[4] = R;
        macierz[5] = S;

        macierz[6] = STR;
    }

    poprzedniaMacierz = macierz[0];

    for(int i=0;i<6;i++){

        newMacierz = pomnurzMacierze(macierz[i+1], poprzedniaMacierz);

        delete [] poprzedniaMacierz;

        poprzedniaMacierz = newMacierz;
    }

    return poprzedniaMacierz;
}


double* MainWindow::pomnurzMacierzeWszystkie3D(double* T, double* S, double* RX, double* RY, double* RZ, double* ST, double* STR, bool original){

    double* macierz[] = {STR, S, RX, RY, RZ, T, ST};

    double* poprzedniaMacierz;
    double* newMacierz;

    poprzedniaMacierz = macierz[0];

    for(int i=0;i<6;i++){

        newMacierz = pomnurzMacierze3D(macierz[i+1], poprzedniaMacierz);

        delete [] poprzedniaMacierz;

        poprzedniaMacierz = newMacierz;
    }

    wypiszMacierz3D(poprzedniaMacierz);

    return poprzedniaMacierz;
}

void MainWindow::wypiszMacierz3D(double* macierz){

    cout<<"- - - - - - - - - - - "<<endl;

    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            cout<<macierz[4*i+j]<<" ";
        }
        cout<<endl;
    }


    cout<<"- - - - - - - - - - - "<<endl;
}





