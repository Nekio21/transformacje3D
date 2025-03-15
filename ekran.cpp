#include "ekran.h"

#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <cmath>
#include<iostream>
#include <algorithm>
#include <cmath>

using namespace std;

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{
    im = QImage(602, 526, QImage::Format_RGB32);
    im.fill(0);

    imKelner = QImage(im.width(),im.height(), QImage::Format_RGB32);
    imKelner.fill(0);
    imKelner.load("zdj3.png");

    changeKostka(im.width(), im.height());

    //drawFigura();

    srand( time(NULL));

    for(int i=0;i<602;i++){
        for(int j=0;j<526;j++){
            ekranZ[i][j] = -400000;
        }
    }
}

void Ekran::paintEvent(QPaintEvent *){
    QPainter p(this);
    p.fillRect(0,0, width(), height(), Qt::green);
    p.drawImage(0,0, im);

    //drawFigura();
}

void Ekran::drawPixel(int x, int y, int r, int g, int b){

    if((x<0) || (y<0) || (im.width()<=x) || (im.height()<=y)) return;

    uchar *pix = im.scanLine(y) + 4*x;
    pix[0] = b;
    pix[1] = g;
    pix[2] = r;
}

void Ekran::drawPixel(int x, int y, int r, int g, int b, QImage* im){

    if((x<0) || (y<0) || (im->width()<=x) || (im->height()<=y)) return;

    uchar *pix = im->scanLine(y) + 4*x;
    pix[0] = b;
    pix[1] = g;
    pix[2] = r;

}

void Ekran::drawPixel(int x, int y, Rgb rgb){

   drawPixel(x, y, rgb.r, rgb.g, rgb.b);

}

void Ekran::drawPixel(int x, int y, Rgb rgb, QImage* im){

   drawPixel(x, y, rgb.r, rgb.g, rgb.b, im);

}

Rgb Ekran::getColor(int x, int y){
    return getColor(&im, x, y);
}

Rgb Ekran::getColor(QImage* im, int x, int y){
    if((x<0) || (y<0) || (im->width()<=x) || (im->height()<=y)) return {-1,-1,-1};

    uchar *pix = im->scanLine(y) + 4*x;

    return {pix[2], pix[1], pix[0]};
}

void Ekran::wybierzPunkt(int x, int y){
    int linia;
    int liniaMin = width();

    for(int i=0;i<ve.size(); i++){
        linia = countR(x,y, ve[i].x, ve[i].y);

        if((linia <= 5)&&(liniaMin > linia)){
            indexOptionD = i;
            liniaMin = linia;
            cout<<"wybrano index: "<<indexOptionD<<endl;
        }
    }
}

void Ekran::krzywaBezieraZaladuj(){
    im.fill(0);

    int ilosc = ve.size()-1;

    bool pokazKropki;

    if(option!='c'){
        pokazKropki = true;
    }

    for(int i=0;i<(ilosc/3);i++){
        rysujKrzywaBeziera(ve[i*3], ve[i*3+1], ve[i*3+2], ve[i*3+3],50, pokazKropki);
    }

    update();
}

void Ekran::bsplineZaladuj(){
    im.fill(0);

    int ilosc = ve.size()-1;

    bool pokazKropki;

    if(option!='c'){
        pokazKropki = true;
    }


    if(ilosc >= 3){
        for(int i=0;i<ilosc-2;i++){
            rysujBspline(ve[i], ve[i+1], ve[i+2], ve[i+3],50, pokazKropki);
        }
    }

    update();
}

int Ekran::zwrocY(int x, int x1, int y1, int x2, int y2){
    int y;

    y = y1 + (x-x1)*(double)(((y2-y1)/(double)(x2-x1))) + 0.5;

    return y;
}

int Ekran::zwrocX(int y, int x1, int y1, int x2, int y2){
    int x;

    x = ( (double)(y-y1) / ((double)(y2-y1)/(x2-x1)) ) + x1 + 0.5;



    return x;
}


int Ekran::countR(int x1, int y1, int x2, int y2){
   int value1 = (x2-x1) * (x2-x1);
   int value2 = (y2-y1) * (y2-y1);

   int suma = value1 + value2;

   int R = sqrt(suma);

   return R;
}

void Ekran::rysujOkrag(int x0, int y0, int R){

    for(int x=0;;x++){

        int y = sqrt(R*R-x*x)+0.5;
        if(x>y)break;


        drawPixel(x+x0,y+y0,134,144,22);
        drawPixel(y+x0,x+y0,134,144,22);
        drawPixel(-x+x0,-y+y0,134,144,22);
        drawPixel(-y+x0,-x+y0,134,144,22);

        drawPixel(-x+x0,y+y0,134,144,22);
        drawPixel(-y+x0,x+y0,134,144,22);
        drawPixel(x+x0,-y+y0,134,144,22);
        drawPixel(y+x0,-x+y0,134,144,22);
    }

}


void Ekran::rysujElipse(int x0,int  y0,int R1,int R2,int N){

    int x, xOld;
    int y, yOld;

    xOld = R1 * cos(0);
    yOld = R2 * sin(0);


    for(int i=1;i<=N;++i){
        double alfa = (2*M_PI*i)/(double)N;

        x = R1 * cos(alfa);
        y = R2 * sin(alfa);


        rysujLinie(x+x0, y+y0, xOld+x0, yOld+y0);

        xOld = x;
        yOld = y;
    }
}



void Ekran::rysujKrzywaBeziera(Punkt p1, Punkt p2, Punkt p3, Punkt p4, int iloscLini, bool show){

    int xOld = p1.x;
    int yOld = p1.y;

    if(show){
        rysujOkrag(p1.x, p1.y,4);
        rysujOkrag(p2.x, p2.y,4);
        rysujOkrag(p3.x, p3.y,4);
        rysujOkrag(p4.x, p4.y,4);
    }


    for(int k=1;k<=iloscLini;k++){

        int x = krzywaBeziera(p1.x, p2.x, p3.x, p4.x, k/(float)iloscLini);
        int y = krzywaBeziera(p1.y, p2.y, p3.y, p4.y, k/(float)iloscLini);

        rysujLinie(xOld, yOld, x, y);

        xOld = x;
        yOld = y;
    }
}


void Ekran::rysujBspline(Punkt p1, Punkt p2, Punkt p3, Punkt p4, int iloscLini, bool show){

    int xOld = krzywaBspline(p1.x, p2.x, p3.x, p4.x, 0);
    int yOld = krzywaBspline(p1.y, p2.y, p3.y, p4.y, 0);


    if(show){
        rysujOkrag(p1.x, p1.y,4);
        rysujOkrag(p2.x, p2.y,4);
        rysujOkrag(p3.x, p3.y,4);
        rysujOkrag(p4.x, p4.y,4);
    }

    for(int k=1;k<=iloscLini;k++){

        int x = krzywaBspline(p1.x, p2.x, p3.x, p4.x, k/(float)iloscLini);
        int y = krzywaBspline(p1.y, p2.y, p3.y, p4.y, k/(float)iloscLini);

        rysujLinie(xOld, yOld, x, y);

        xOld = x;
        yOld = y;
    }

}


//jesli chcesz wynik krzywej dla y wpisz y, a jesli dla x wpisz x;
//czym jest t??? T jest jakby ulamkniem
//jesli chcemy znac paremetry punktu w 1/2 w krzywej to t=0.5
//jesli na koncu to t = 1
//jesli na poczatku to t= 0
int Ekran::krzywaBeziera(int p1,int p2, int p3, int p4, double t){
    int wynik = 0;

    double wynikPart1 = (1-t)*(1-t)*(1-t) * p1;
    double wynikPart2 = 3 * (1-t)*(1-t)*t * p2;
    double wynikPart3 = 3 * (1-t)*t*t * p3;
    double wynikPart4 = t*t*t * p4;

    wynik = wynikPart1 + wynikPart2 + wynikPart3 + wynikPart4;

    return wynik;
}


int Ekran::krzywaBspline(int p1,int p2, int p3, int p4, double t){
    int wynik = 0;

    double wynikPart1 = (-t*t*t + 3*t*t -3*t + 1)/(double)6 * p4;
    double wynikPart2 = (3*t*t*t-6*t*t+4)/(double)6 * p3;
    double wynikPart3 = (-3*t*t*t+3*t*t+3*t+1)/(double)6 * p2;
    double wynikPart4 = t*t*t/(double)6 * p1;

    wynik = wynikPart1 + wynikPart2 + wynikPart3 + wynikPart4;

    return wynik;
}


void Ekran::rysujLinie(int x1, int y1, int x2, int y2){
    if(abs(y2-y1) <= abs(x2-x1)){

        if(x2 > x1){
         for(int x = x1;x<x2;x++){
             int y = zwrocY(x, x1, y1, x2, y2);
             drawPixel(x+0.5,y+0.5, chooseRgb);
         }
        }else{
            for(int x = x1;x>x2;x--){
                int y = zwrocY(x, x1, y1, x2, y2) ;
                drawPixel(x+0.5,y, chooseRgb);
            }
        }
     }else{
        if(y2 > y1){
            for(int y = y1;y<y2;y++){
                int x = zwrocX(y, x1, y1, x2, y2);
                drawPixel(x+0.5,y+0.5, chooseRgb);
            }
        }else{
            for(int y = y1;y>y2;y--){
                int x = zwrocX(y, x1, y1, x2, y2);
                drawPixel(x+0.5,y+0.5, chooseRgb);
            }
        }

    }
}

//zamaluj bierze z zamalujPunkty(taki vector) pukty do obrowbki
//wiec nalezy przed wywolaniem metody wywolac push back zamalujPunkty :)
void Ekran::zamaluj(Rgb color, Rgb background){

    if((color.r == background.r) &&
            (color.g == background.g) &&
            (color.b == background.b)){

        zamalujPunkty.pop_back();
        return;
    }

    while(!zamalujPunkty.empty()){
        Punkt punkt = zamalujPunkty.back();
        zamalujPunkty.pop_back();

        if((getColor(punkt.x,punkt.y).r == background.r) &&
            (getColor(punkt.x,punkt.y).g == background.g) &&
            (getColor(punkt.x,punkt.y).b == background.b)){

            drawPixel(punkt.x, punkt.y, chooseRgb);

            zamalujPunkty.push_back({punkt.x+1,punkt.y});
            zamalujPunkty.push_back({punkt.x-1,punkt.y});
            zamalujPunkty.push_back({punkt.x,punkt.y+1});
            zamalujPunkty.push_back({punkt.x,punkt.y-1});
        }
    }

    update();
}


void Ekran::rysujPoligon(vector<Punkt> ve){
    int minY = (*min_element(ve.begin(), ve.end(),[](Punkt a,Punkt b){return a.y<b.y;})).y;
    int maxY = (*max_element(ve.begin(), ve.end(),[](Punkt a,Punkt b){return a.y<b.y;})).y;

    vector<int> output;

    cout<<minY<<", "<<maxY<<endl;

    for(int y=minY; y<=maxY; y++){

        cout<<"siema"<<endl;
        findX(output, ve, y);

        sort(output.begin(), output.end());

        for(int i=0;i<(int)output.size();i++){
            cout<<"Pozycja nr "<<i<<": "<<output[i]<<endl;
        }

        wypelnij(output, y);
    }
}

void Ekran::rysujPoligon2(Punkt3DSimple A, Punkt3DSimple B, Punkt3DSimple C){
    int minY = min(A.y, min(B.y, C.y));
    int maxY = max(A.y, max(B.y, C.y));

    vector<int> output;

    ve.clear();
    ve.push_back({A.x, A.y});
    ve.push_back({B.x, B.y});
    ve.push_back({C.x, C.y});


    for(int y=minY; y<=maxY; y++){

        findX(output, ve, y);

        sort(output.begin(), output.end());

        wypelnij2(output, y, A, B, C);
    }

    update();
}


void Ekran::wypelnij2(vector<int> x, int y, Punkt3DSimple A, Punkt3DSimple B, Punkt3DSimple C){

    double W = (B.x - A.x) * (C.y - A.y)
            - (B.y-A.y) * (C.x - A.x);

   // zBufforVector.clear();

    for(int i=1; i<(int)x.size();i++){

        if(i%2==0)continue;

        rysujLinieTrojka(x[i-1], x[i], y, W, A, B, C);
    }
}

void Ekran::rysujLinieTrojka(int x1, int x2, int y, double W, Punkt3DSimple A, Punkt3DSimple B, Punkt3DSimple C){
    double Wv;
    double Ww;

    double v;
    double w;
    double u;

    for(int i=x1;i<=x2;i++){

     Wv = (i - A.x) * (C.y - A.y)
            - (y - A.y) * (C.x - A.x);

     Ww = (B.x - A.x) * (y - A.y)
            - (B.y - A.y) * (i - A.x);

     v = Wv/W;
     w = Ww/W;
     u = 1-v-w;

     Punkt2 punktAbroad;

     Punkt2 punktAbroadA, punktAbroadB, punktAbroadC;

     punktAbroadA = {0,0};
     punktAbroadB = {500,0};
     punktAbroadC = {500,500};

     punktAbroad.x = u * punktAbroadA.x + v * punktAbroadB.x + w * punktAbroadC.x;
     punktAbroad.y = u * punktAbroadA.y + v * punktAbroadB.y + w * punktAbroadC.y;

     punktAbroad.x = fmod((abs(punktAbroad.x)),(imKelner.width()));
     punktAbroad.y = fmod((abs(punktAbroad.y)),(imKelner.height()));

     double a = punktAbroad.x - floor(punktAbroad.x);
     double b = punktAbroad.y - floor(punktAbroad.y);

     Rgb rgbP1, rgbP2, rgbP3, rgbP4, rgb;

     Punkt2 P4 = {(double)floor(punktAbroad.x), (double)floor(punktAbroad.y)};
     Punkt2 P3 = {(double)floor(punktAbroad.x)+1, (double)floor(punktAbroad.y)};
     Punkt2 P2 = {(double)floor(punktAbroad.x)+1, (double)floor(punktAbroad.y)+1};
     Punkt2 P1 = {(double)floor(punktAbroad.x), (double)floor(punktAbroad.y)+1};

     rgbP1 = getColor(&imKelner,P1.x, P1.y);
     rgbP2 = getColor(&imKelner,P2.x, P2.y);
     rgbP3 = getColor(&imKelner,P3.x, P3.y);
     rgbP4 = getColor(&imKelner,P4.x, P4.y);

     double newR = b * ((1-a)*rgbP1.r+a*rgbP2.r) + (1-b)*((1-a)*rgbP4.r+a*rgbP3.r);
     double newG = b * ((1-a)*rgbP1.g+a*rgbP2.g) + (1-b)*((1-a)*rgbP4.g+a*rgbP3.g);
     double newB = b * ((1-a)*rgbP1.b+a*rgbP2.b) + (1-b)*((1-a)*rgbP4.b+a*rgbP3.b);

     rgb = {(int)newR, (int)newG, (int)newB};

     int sredZ = u * A.z + v * B.z + w * C.z;

     if((i >= 0 && i < 602) && (y >=0 && y < 526)){
         if(ekranZ[i][y] == -400000){
                 ekranZ[i][y] = sredZ;
                 drawPixel(i,y, rgb);
        }

         if(ekranZ[i][y] > sredZ){
             ekranZ[i][y] = sredZ;
             drawPixel(i,y, rgb);
         }
    }


    }
}

void Ekran::wypelnij(vector<int> x, int y){

    for(int i=1; i<x.size();i++){

        if(i%2==0)continue;

        rysujLinie(x[i-1], y, x[i], y);
    }
}

void Ekran::findX(vector<int>& output, vector<Punkt> ve, int y){
    int k=0;

    output.clear();

    for(int i=0; i<(int)ve.size(); i++){
        int y1 = ve[i].y;
        int y2 = ve[(i+1)%ve.size()].y;

        if((y1>=y && y2<y) || (y2>=y && y1<y)){
            int x = findXDeep(ve[i],ve[(i+1)%ve.size()], y);

            output.push_back(x);
        }
    }
}

int Ekran::findXDeep(Punkt p1, Punkt p2, int y){
   int returnValue;
   int returnValuePart1;
   int returnValuePart2;
   int returnValuePart3;

   //if(p1.y == p2.y) return

   returnValuePart1 = p1.x;
   returnValuePart2 = (p2.x - p1.x) * (y-p1.y);
   returnValuePart3 = p2.y-p1.y;

   returnValue = returnValuePart1 + returnValuePart2/(double)returnValuePart3;

   return returnValue;
}

//type=1 => H
//type=2 => S
//type=3 => V
void Ekran::updateHSV(){


    for(int y=0;y<im.height();y++){
        for(int x=0;x<im.width();x++){
            Rgb rgb = getColor(x,y);
            HSV hsvTemplate = getHSVColor(rgb);

            //cout<<"-------------"<<endl;
            //cout<<"RGB: {"<<rgb.r<<", "<<rgb.g<<", "<<rgb.b<<"}"<<endl;
            //cout<<"HSV: {"<<hsvTemplate.h<<", "<<hsvTemplate.s<<", "<<hsvTemplate.v<<"}"<<endl;

            hsvTemplate.h = max(0, min(hsvTemplate.h + hsv.h, 360));
            hsvTemplate.s = max(0.0, min(hsvTemplate.s + hsv.s, 1.0));
            hsvTemplate.v = max(0.0, min(hsvTemplate.v + hsv.v, 1.0));

            //cout<<"HSV_NEW: {"<<hsvTemplate.h<<", "<<hsvTemplate.s<<", "<<hsvTemplate.v<<"}"<<endl;

            Rgb newRgb = getRgbColor(hsvTemplate);

           // cout<<"RGB_NEW: {"<<newRgb.r<<", "<<newRgb.g<<", "<<newRgb.b<<"}"<<endl;
            //cout<<"-------------"<<x<<","<<y<<endl;

            drawPixel(x,y, newRgb, &imCopy);
        }
    }

    update();
}

Rgb Ekran::getRgbColor(HSV hsv){
    double c = hsv.v * hsv.s;
    double x = c * (1-abs((fmod ((hsv.h/60.0),2)-1)));
    double m = hsv.v - c;

    RgbT rgbT;

    int h = hsv.h;

    if(0<= h && h < 60){
        rgbT.r = c;
        rgbT.g = x;
        rgbT.b = 0;
    }else if(60<= h && h < 120){
        rgbT.r = x;
        rgbT.g = c;
        rgbT.b = 0;
    }else if(120<=h && h<180){
        rgbT.r = 0;
        rgbT.g = c;
        rgbT.b = x;
    }else if(180<=h && h<240){
        rgbT.r = 0;
        rgbT.g = x;
        rgbT.b = c;
    }else if(240<=h && h<300){
        rgbT.r = x;
        rgbT.g = 0;
        rgbT.b = c;
    }else if(300<=h && h<=360){
        rgbT.r = c;
        rgbT.g = 0;
        rgbT.b = x;
    }

    Rgb returnRgb;

    returnRgb.r = (rgbT.r+m)*255;
    returnRgb.g = (rgbT.g+m)*255;
    returnRgb.b = (rgbT.b+m)*255;

    return returnRgb;
}

HSV Ekran::getHSVColor(Rgb rgb){
    double r2 = rgb.r/255.0;
    double g2 = rgb.g/255.0;
    double b2 = rgb.b/255.0;

    double valueMax = max(r2, max(g2,b2));
    double valueMin = min(r2, min(g2,b2));

    double delta = valueMax - valueMin;

    HSV returnHSV;


    returnHSV.h = getCountH(delta, valueMax, r2,g2,b2);
    returnHSV.s = getCountS(delta, valueMax);
    returnHSV.v = valueMax;

    return returnHSV;
}


int Ekran::getCountH(double delta, double max, double r2, double g2, double b2){
    if(delta == 0){
        return 0;
    }else if(max == r2){
        return (60*(fmod(((g2-b2)/delta),6)));
    }else if(max == g2){
         return (60*(((b2-r2)/delta)+2));
    }else if(max == b2){
         return (60*(((r2-g2)/delta)+4));
    }
}

double Ekran::getCountS(double delta, double max){
    if(max == 0) return 0;
    else return delta/max;
}

void Ekran::ustawZdjecia(){

    QString path[3][2] = {
      {"C:\\Jakub\\Informatyka rok 2\\qt\\blendMode\\zdj1.png", "Twitch"},
      {"C:\\Jakub\\Informatyka rok 2\\qt\\blendMode\\zdj2.png", "Braund"},
      {"C:\\Jakub\\Informatyka rok 2\\qt\\blendMode\\zdj3.png", "Pantheon"}
    };

    for(int i=0;i<3;i++){

        QImage image = QImage(1215, 717, QImage::Format_RGB32);
        image.fill(0);
        image.load(path[i][0]);

        zdjecia[i] = {image, path[i][1].toStdString(), 0, 0};
    }
}

void Ekran::ustawMape(){
    mapa[0] = &Ekran::zblendujNormalMode;
    mapa[1] = &Ekran::zblendujMultiplyMode;
    mapa[2] = &Ekran::zblendujScreenMode;

    mapa[3] = &Ekran::zblendujOverlayMode;
    mapa[4] = &Ekran::zblendujDarkenMode;
    mapa[5] = &Ekran::zblendujLightenMode;

    mapa[6] = &Ekran::zblendujDifferenceMode;
    mapa[7] = &Ekran::zblendujAdditiveMode;
    mapa[8] = &Ekran::zblendujSubtractiveMode;
}

void Ekran::blend(){
    im.fill(0);

    for(int i=0; i<im.height(); i++){
        for(int j=0; j<im.width(); j++){
            Rgb rgb = getBlendColor(j,i);

            drawPixel(j,i, rgb);
        }
    }

    update();
}

Rgb Ekran::getBlendColor(int x, int y){
    Rgb returnRgb = {1,1,1};

    for(int i=2;i>=0;i--){

        double alfa = zdjecia[i].sila/100.0;
        int tryb = zdjecia[i].indexTrybu;

        returnRgb = funkcjaBlendujaca(mapa[tryb],i,x,y,alfa,returnRgb);
    }

    return returnRgb;
}

Rgb Ekran::funkcjaBlendujaca(Rgb (Ekran::*funkcja)(Rgb now, Rgb then), int index, int x, int y, double alfa, Rgb background){
    Rgb newRgb;
    Rgb rgbZbledowane;

    rgbZbledowane = (this->*funkcja)(getColor(&zdjecia[index].image, x, y), background);

    newRgb.r = alfa * rgbZbledowane.r + (1-alfa) * background.r;
    newRgb.g = alfa * rgbZbledowane.g + (1-alfa) * background.g;
    newRgb.b = alfa * rgbZbledowane.b + (1-alfa) * background.b;

    return newRgb;
}

Rgb Ekran::zblendujNormalMode(Rgb now, Rgb then){
    return now;
}

Rgb Ekran::zblendujMultiplyMode(Rgb now, Rgb then){
    Rgb newRgb;

    newRgb.r = (now.r * then.r)>>8;
    newRgb.g = (now.g * then.g)>>8;
    newRgb.b = (now.b * then.b)>>8;

    return newRgb;
}

Rgb Ekran::zblendujScreenMode(Rgb now, Rgb then){
    Rgb newRgb;

    newRgb.r = 255 - ((255-then.r)*(255-now.r) >> 8);
    newRgb.g = 255 - ((255-then.g)*(255-now.g) >> 8);
    newRgb.b = 255 - ((255-then.b)*(255-now.b) >> 8);

    return newRgb;
}

Rgb Ekran::zblendujOverlayMode(Rgb now, Rgb then){
    Rgb newRgb;

    if(then.r<128){
        newRgb.r = (then.r*now.r)>>7;
    }else{
        newRgb.r = 255 - ((255-then.r)*(255-now.r) >> 7);
    }

    if(then.g<128){
        newRgb.g = (then.g*now.g)>>7;
    }else{
        newRgb.g = 255 - ((255-then.g)*(255-now.g) >> 7);
    }

    if(then.b<128){
        newRgb.b = (then.b*now.b)>>7;
    }else{
        newRgb.b = 255 - ((255-then.b)*(255-now.b) >> 7);
    }

    return newRgb;
}

Rgb Ekran::zblendujDarkenMode(Rgb now, Rgb then){
    Rgb newRgb;

    if(then.r<now.r){
        newRgb.r = then.r;
    }else{
        newRgb.r = now.r;
    }

    if(then.g<now.g){
        newRgb.g = then.g;
    }else{
        newRgb.g = now.g;
    }

    if(then.b<now.b){
        newRgb.b = then.b;
    }else{
        newRgb.b = now.b;
    }

    return newRgb;
}

Rgb Ekran::zblendujLightenMode(Rgb now, Rgb then){
    Rgb newRgb;

    if(then.r<now.r){
        newRgb.r = now.r;
    }else{
        newRgb.r = then.r;
    }

    if(then.g<now.g){
        newRgb.g = now.g;
    }else{
        newRgb.g = then.g;
    }

    if(then.b<now.b){
        newRgb.b = now.b;
    }else{
        newRgb.b = then.b;
    }

    return newRgb;
}


Rgb Ekran::zblendujDifferenceMode(Rgb now, Rgb then){
    Rgb newRgb;


    newRgb.r = abs(then.r - now.r);
    newRgb.g = abs(then.g - now.g);
    newRgb.b = abs(then.b - now.b);

    return newRgb;
}

Rgb Ekran::zblendujAdditiveMode(Rgb now, Rgb then){
    Rgb newRgb;


    newRgb.r = min(then.r + now.r, 255);
    newRgb.g = min(then.g + now.g, 255);
    newRgb.b = min(then.b + now.b, 255);

    return newRgb;
}

Rgb Ekran::zblendujSubtractiveMode(Rgb now, Rgb then){
    Rgb newRgb;


    newRgb.r = max(then.r + now.r - 255, 0);
    newRgb.g = max(then.g + now.g - 255, 0);
    newRgb.b = max(then.b + now.b - 255, 0);

    return newRgb;
}


void Ekran::kalener(Rgb colorDraw, Rgb colorNotDraw){
    imKelner.fill(0);

    for(int i=0; i<im.height(); i++){
        for(int j=0; j<im.width(); j++){
            bool stan = isColorKelner(colorDraw, j,i);

            if(stan){

                drawPixel(j,i, colorDraw, &imKelner);
            }else{

                drawPixel(j,i, colorNotDraw, &imKelner);
            }
        }
    }


    for(int i=0; i<im.height(); i++){
        for(int j=0; j<im.width(); j++){
            Rgb color = getColor(&imKelner, j,i);

            drawPixel(j,i, color);
        }
    }

    update();
}



bool Ekran::isColorKelner(Rgb findThatColor, int x, int y){
    bool stan = false;

    int newX = x -  kelnerSize;
    int newY = y - kelnerSize;

    for(int i=kelnerSize*2; i >= 0; i--){
        for(int j=kelnerSize*2; j>=0; j--){
            Rgb color = getColor(newX+i, newY+j);

            if(color.r == findThatColor.r && color.g == findThatColor.g & color.b == findThatColor.b){
                return true;
            }

        }
    }

    return stan;
}

void Ekran::drawFigura(double* macierz){

    for(int i=0;i<602;i++){
        for(int j=0;j<526;j++){
            ekranZ[i][j] = -400000;
        }
    }

    rysujSciane(kostka3[0], kostka3[1], kostka3[2], kostka3[3]);


    rysujSciane(kostka3[4], kostka3[5], kostka3[6], kostka3[7]);


    rysujSciane(kostka3[0], kostka3[4], kostka3[7], kostka3[3]);


    rysujSciane(kostka3[1], kostka3[5], kostka3[6], kostka3[2]);


    rysujSciane(kostka3[4], kostka3[5], kostka3[1], kostka3[0]);


    rysujSciane(kostka3[7], kostka3[6], kostka3[2], kostka3[3]);
}

void Ekran::giveMeZ(Punkt3D A, Punkt3D B, Punkt3D C, Punkt3D D, double* macierz){
    zBufforScianke(A, B, C, D, macierz);
}


//To powinnien byc kwadrat :o
void Ekran::zBufforScianke(Punkt3D A, Punkt3D B, Punkt3D C, Punkt3D D, double* macierze){
    Punkt3D p[4] = {A,B,C,D};

    ZBuffor buf2 = {{-2,-2,-2}, -1};

    Punkt3D pointMax = giveMeMax(p);
    Punkt3D pointMin = giveMeMin(p);


    if(pointMax.x == pointMin.x){

        for(int i=pointMin.y; i <= pointMax.y; i++){
            for(int j=pointMin.z; j <= pointMax.z; j++){
                Punkt3D newPoint = getNewPoint3D({pointMax.x, (double)i, (double)j}, macierze);
//                if(perspectiveMode == true){
//                    newPoint = getNewPoint3DPerpective(newPoint, f, im.width()/2, im.height()/2);
//                }

                //Punkt a = {(int)newPoint.x, (int)newPoint.y};
               // ZBuffor buf = {{-1,-1,-1}, (int)newPoint.z};
            }
        }

    }
    else if(pointMax.y == pointMin.y){
        pointMax.y = -1;

        for(int i=pointMin.x; i <= pointMax.x; i++){
            for(int j=pointMin.z; j <= pointMax.z; j++){

                Punkt3D newPoint = getNewPoint3D({(double)i, pointMax.y, (double)j}, macierze);
//                if(perspectiveMode == true){
//                    newPoint = getNewPoint3DPerpective(newPoint, f, im.width()/2, im.height()/2);
//                }

                Punkt a = {(int)newPoint.x, (int)newPoint.y};
                ZBuffor buf = {{-1,-1,-1}, (int)newPoint.z};

               // zBufforMap.insert(make_pair(a,buf));
                //zBufforMapCalosc.insert(make_pair(a,buf2));
            }
        }

    }else{
         pointMax.z = -1;


         for(int i=pointMin.x; i <= pointMax.x; i++){
             for(int j=pointMin.y; j <= pointMax.y; j++){

                 Punkt3D newPoint = getNewPoint3D({(double)i, (double)j, pointMax.z}, macierze);
 //                if(perspectiveMode == true){
 //                    newPoint = getNewPoint3DPerpective(newPoint, f, im.width()/2, im.height()/2);
 //                }

                 Punkt a = {(int)newPoint.x, (int)newPoint.y};
                 ZBuffor buf = {{-1,-1,-1}, (int)newPoint.z};

                // zBufforMap.insert(make_pair(a,buf));
                // zBufforMapCalosc.insert(make_pair(a,buf2));
             }
         }
    }
}

Punkt3D Ekran::giveMeMax(Punkt3D punkty[]){
    Punkt3D maxPoint;

    maxPoint = punkty[0];

    for(int i=1;i<4;i++){
        maxPoint.x = max(maxPoint.x, punkty[i].x);
        maxPoint.y = max(maxPoint.y, punkty[i].y);
        maxPoint.z = max(maxPoint.z, punkty[i].z);
    }

    return maxPoint;
}

Punkt3D Ekran::giveMeMin(Punkt3D punkty[]){
    Punkt3D minPoint;

    minPoint = punkty[0];

    for(int i=1;i<4;i++){
        minPoint.x = min(minPoint.x, punkty[i].x);
        minPoint.y = min(minPoint.y, punkty[i].y);
        minPoint.z = min(minPoint.z, punkty[i].z);
    }

    return minPoint;
}

void Ekran::rysujSciane(Punkt3D A, Punkt3D B, Punkt3D C, Punkt3D D){
    //TODO: Potem zrob moze vector<Trojkat> gdzie trojkat To bedzie 2 pierwsze i ostatnie i 2 kolejne i ostatnie hahahhha

    if((A.z > 130 && A.z < 2000) && (B.z > 130 && B.z < 2000) && (C.z > 130 && C.z < 2000)){
//        rysujLinie(A.x, A.y, B.x, B.y);
//        rysujLinie(B.x, B.y, C.x, C.y);
//        rysujLinie(A.x, A.y, C.x, C.y);

        rysujPoligon2({(int)A.x, (int)A.y, (int)A.z}, {(int)B.x, (int)B.y, (int)B.z}, {(int)C.x, (int)C.y, (int)C.z});
    }

    if((A.z > 130 && A.z < 2000) && (D.z > 130 && D.z < 2000) && (C.z > 130 && C.z < 2000)){
//        rysujLinie(C.x, C.y, D.x, D.y);
//        rysujLinie(D.x, D.y, A.x, A.y);
//        rysujLinie(A.x, A.y, C.x, C.y);

        rysujPoligon2({(int)D.x, (int)D.y, (int)D.z}, {(int)A.x, (int)A.y, (int)A.z}, {(int)C.x, (int)C.y, (int)C.z});

    }
}



void Ekran::drawMacierz(double* macierz, double* macierzOdwrotna){

    im.fill(0);
    im.fill(Qt::GlobalColor::white);

//    for(int i=0; i<imKelner.height(); i++){
//        for(int j=0; j<imKelner.width(); j++){
//            Rgb rgb;
//            Punkt newPoint = getNewPoint({(double)j,(double)i}, macierz);

//            rgb = getColor(&imKelner, newPoint.x, newPoint.y);
//            drawPixel((int)newPoint.x, (int)newPoint.y, rgb);
//        }
//    }

//    for(int i=0; i<imKelner.height(); i++){
//        for(int j=0; j<imKelner.width(); j++){
//            Rgb rgb, rgbP1, rgbP2, rgbP3, rgbP4;

//            Punkt colorPoint = getNewPoint({(double)j,(double)i}, macierzOdwrotna);

//            double a = colorPoint.x - floor(colorPoint.x);
//            double b = colorPoint.y - floor(colorPoint.y);



//            Punkt P4 = {(double)floor(colorPoint.x), (double)floor(colorPoint.y)};
//            Punkt P3 = {(double)floor(colorPoint.x)+1, (double)floor(colorPoint.y)};
//            Punkt P2 = {(double)floor(colorPoint.x)+1, (double)floor(colorPoint.y)+1};
//            Punkt P1 = {(double)floor(colorPoint.x), (double)floor(colorPoint.y)+1};

//            rgbP1 = getColor(&imKelner, P1.x, P1.y);
//            rgbP2 = getColor(&imKelner, P2.x, P2.y);
//            rgbP3 = getColor(&imKelner, P3.x, P3.y);
//            rgbP4 = getColor(&imKelner, P4.x, P4.y);

//            double newR = b * ((1-a)*rgbP1.r+a*rgbP2.r) + (1-b)*((1-a)*rgbP4.r+a*rgbP3.r);
//            double newG = b * ((1-a)*rgbP1.g+a*rgbP2.g) + (1-b)*((1-a)*rgbP4.g+a*rgbP3.g);
//            double newB = b * ((1-a)*rgbP1.b+a*rgbP2.b) + (1-b)*((1-a)*rgbP4.b+a*rgbP3.b);

//            rgb = {(int)newR, (int)newG, (int)newB};

//            drawPixel(j, i, rgb);
//        }
//    }

    update();

    delete [] macierz;
}

void Ekran::drawMacierz3D(double* macierz3D, int f){
    im.fill(0);
    im.fill(Qt::GlobalColor::white);

    for(int i=0; i<8; i++){
            Punkt3D newPoint = getNewPoint3D(kostka2[i], macierz3D);

            if(perspectiveMode == true){
                newPoint = getNewPoint3DPerpective(newPoint, f, im.width()/2, im.height()/2);
            }

            kostka3[i] = newPoint;
    }

    drawFigura(macierz3D);

    update();

    delete [] macierz3D;
}

Punkt Ekran::getNewPoint(Punkt p, double* macierz){
    Punkt returnPoint;

    returnPoint.x = macierz[0] * p.x + macierz[1] * p.y + macierz[2];
    returnPoint.y = macierz[3] * p.x + macierz[4] * p.y + macierz[5];


    return returnPoint;
}

Punkt3D Ekran::getNewPoint3D(Punkt3D p, double* macierz3D){
    Punkt3D returnPoint;

    p.x += im.width()/2-200;
    p.y += im.height()/2-200;

    returnPoint.x = macierz3D[0] * p.x + macierz3D[1] * p.y + macierz3D[2] * p.z + macierz3D[3];
    returnPoint.y = macierz3D[4] * p.x + macierz3D[5] * p.y + macierz3D[6] * p.z + macierz3D[7];
    returnPoint.z = macierz3D[8] * p.x + macierz3D[9] * p.y + macierz3D[10] * p.z + macierz3D[11];

    return returnPoint;
}

Punkt3D Ekran::getNewPoint3DPerpective(Punkt3D p, int f, int width, int height){
    Punkt3D returnPoint;

    if(p.z == 0){
        return {-1,-1,-1};
    }

    returnPoint.x = (p.x/p.z) * f + width;
    returnPoint.y = (p.y/p.z) * f + height;
    returnPoint.z = p.z;

    return returnPoint;
}


//Jednak nie to :<
void Ekran::changeKostka(int width, int height){
    cout<<width<<",  "<<height<<endl;

//    for(int i=0;i<8;i++){
//        kostka2[i].x += width/2 - 200;
//        kostka2[i].y += height/2 - 200;

//    }
}


