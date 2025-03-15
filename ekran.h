#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <vector>
#include <iostream>
#include <QPainter>
#include <map>

using namespace std;

struct Punkt{
    int x;
    int y;

};

struct Punkt2{
    double x;
    double y;
};

struct Punkt3D{
    double x;
    double y;
    double z;
};

struct Punkt3DSimple{
    int x;
    int y;
    int z;
};



struct Sciana{
    Punkt3D p1;
    Punkt3D p2;
    Punkt3D p3;
    Punkt3D p4;
};

struct Rgb{
    int r;
    int g;
    int b;
};

struct ZBuffor{
    Rgb rgb;
    int z;
};

struct RgbT{
    double r;
    double g;
    double b;
};

struct HSV{
    int h;
    double s;
    double v;
};

struct Cos{
    QImage image;
    string name;
    int indexTrybu;
    int sila;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
    explicit Ekran(QWidget *parent = nullptr);
    void kalener(Rgb, Rgb);
    void krzywaBezieraZaladuj();
    void bsplineZaladuj();
    void blend();
    char option = 'p';
    Rgb chooseRgb = {124,54,23};
    HSV hsv = {0,0,0};
    void updateHSV();
    void drawMacierz(double* macierz, double* macierzOdwrotna);
    void drawMacierz3D(double* macierz3D, int f);
    Cos zdjecia[3];
    QImage im;
    QImage imKelner;

    int ekranZ[602][526];

    bool perspectiveMode = false;

    string tryby[9] = {
        "Normal mode",
        "Multiply mode",
        "Screen mode",
        "Overlay mode",
        "Darken mode",
        "Lighten mode",
        "Difference mode",
        "Additive mode",
        "Subtractive mode"
    };

    int kelnerSize = 1;

protected:
    void paintEvent(QPaintEvent *);

private:

    QImage imCopy;

    //ZLEEEEE
    Punkt kostka[8]={
        {0,0},
        {400,0},
        {400,300},

        {0,400},
        {0,0},
        {400,0},
        {400,400},

        {0,400}
    };

    Punkt3D kostka2[8]={
        {0,0,0},
        {400,0,0},
        {400,400,0},
        {0,400,0},

        {0,0,400},
        {400,0,400},
        {400,400,400},
        {0,400,400}
    };

    Punkt3D kostka3[8];

    vector<Punkt> ve;
    vector<Punkt> zamalujPunkty;
    vector<Punkt> polygonPoints;

    using t = Rgb (Ekran::*)(Rgb, Rgb);

    map<int, t> mapa;

    int indexOptionD;

    void drawPixel(int x, int y, int r, int g, int b);
    void drawPixel(int x, int y, int r, int g, int b, QImage* im);
    void drawPixel(int x, int y, Rgb rgb, QImage* im);
    void drawPixel(int x, int y, Rgb rgb);

    Rgb getColor(int x, int y);
    Rgb getColor(QImage* im, int x, int y);

    int zwrocY(int x, int x1, int y1, int x2, int y2);
    int zwrocX(int y, int x1, int y1, int x2, int y2);
    void drawFigura(double*);
    void rysujSciane(Punkt3D A, Punkt3D B, Punkt3D C, Punkt3D D);
    void zamaluj(Rgb, Rgb);
    void ustawZdjecia();
    void ustawMape();
    void rysujOkrag(int,int,int);
    void rysujElipse(int x0, int y0, int R1, int R2, int N);
    void rysujLinie(int x1, int y1, int x2, int y2);
    void rysujKrzywaBeziera(Punkt,Punkt,Punkt, Punkt, int, bool);
    void rysujBspline(Punkt,Punkt,Punkt, Punkt, int, bool);
    int krzywaBeziera(int,int,int,int, double);
    int krzywaBspline(int,int,int,int, double);
    void rysujPoligon(vector<Punkt>);
    void findX(vector<int>&, vector<Punkt>, int y);
    int findXDeep(Punkt, Punkt, int y);
    void wybierzPunkt(int, int);
    int countR(int,int,int,int);
    void wypelnij(vector<int> x, int y);
    double getCountS(double delta, double max);
    int getCountH(double delta, double max, double r2, double g2, double b2);
    HSV getHSVColor(Rgb rgb);
    Rgb getRgbColor(HSV hsv);
    Rgb getBlendColor(int, int);
    void giveMeZ(Punkt3D A, Punkt3D B, Punkt3D C, Punkt3D D, double* macierz);
    void zBufforScianke(Punkt3D A, Punkt3D B, Punkt3D C, Punkt3D D, double* macierze);
    Punkt3D giveMeMax(Punkt3D[]);
    Punkt3D giveMeMin(Punkt3D[]);

    Rgb zblendujNormalMode(Rgb now, Rgb then);
    Rgb zblendujMultiplyMode(Rgb now, Rgb then);
    Rgb zblendujScreenMode(Rgb now, Rgb then);
    Rgb zblendujOverlayMode(Rgb now, Rgb then);
    Rgb zblendujDarkenMode(Rgb now, Rgb then);
    Rgb zblendujLightenMode(Rgb now, Rgb then);
    Rgb zblendujDifferenceMode(Rgb now, Rgb then);
    Rgb zblendujAdditiveMode(Rgb now, Rgb then);
    Rgb zblendujSubtractiveMode(Rgb now, Rgb then);

    void rysujLinieTrojka(int x1, int x2, int y, double W, Punkt3DSimple A, Punkt3DSimple B, Punkt3DSimple C);
    void wypelnij2(vector<int> x, int y, Punkt3DSimple A, Punkt3DSimple B, Punkt3DSimple C);
    void rysujPoligon2(Punkt3DSimple A, Punkt3DSimple B, Punkt3DSimple C);

    Rgb funkcjaBlendujaca(Rgb (Ekran::*f)(Rgb now, Rgb then), int index, int x, int y, double alfa, Rgb background);
    bool isColorKelner(Rgb findThatColor, int x, int y);
    Punkt getNewPoint(Punkt p, double* macierz);
    Punkt3D getNewPoint3D(Punkt3D p, double* macierz3D);
    Punkt3D getNewPoint3DPerpective(Punkt3D p, int f, int width, int height);
    void changeKostka(int width, int height);

    int x1;
    int y1;
    int x2;
    int y2;
    int xOldLinia = -1;
    int yOldLinia = -1;
    bool second = false;
signals:

};

#endif // EKRAN_H
