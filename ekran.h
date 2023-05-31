#ifndef EKRAN_H
#define EKRAN_H

#include <QWidget>
#include <QVector>
#include <QColor>

struct color
{
    int red;
    int green;
    int blue;
};

struct coord
{
    int x;
    int y;
};

struct wsp
{
    int a1;
    int a2;
    int b;
};

class Ekran : public QWidget
{
    Q_OBJECT
public:
        explicit Ekran(QWidget *parent = nullptr);
        void linia(int x1,int y1, int x2,int y2,int r,int g,int b);
        void drawPixel(int x,int y,int r, int g,int b,QImage *img);
        void drawPunkt(int x,int y,int r, int g,int b);
        void maxMin(int &l1,int &l2);
        void check(QVector<int> &tabX,QVector <wsp> wspl,int index1,int index2,int i);
        void drawGranica();
        void resetScene();
        void drawTriangle(int xA,int yA,int xB,int yB,int xC,int yC,int xAt,int yAt,int xBt,int yBt,int xCt,int yCt,int xAp,int yAp,int xBp,int yBp,int xCp,int yCp);
        void drawTriangleLines(QVector<coord> lista);
        void drawT(QVector <coord> lista);
        void drawObrazek(QImage *img);
        void findId(QVector <coord> lista);
        void findPosition(bool &raz,int &xt,int &yt,QImage *img,int xAp,int yAp,int xBp,int yBp,int xCp,int yCp,float u,float v,float w);
        void changePosition(QVector <coord> &lista);
        void getPixel(int x,int y,int &r,int &g,int &b,QImage *img);
        void setTryb(bool newTryb);
        void changeLista2();
        void setN(int newN);

protected:
        void paintEvent(QPaintEvent *);
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *e);
private:
        QImage im,obrazek1,obrazek2;
        QVector <coord> lista1,lista2,lista3;
        coord p1,p2;
        bool tryb=0;
        int id=-1;
        color l1;
        color l2;
        int n=0;
signals:

};

#endif // EKRAN_H
