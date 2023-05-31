#include "ekran.h"
#include <QPainter>
#include <QMouseEvent>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <QColorDialog>
#include <iostream>
#include <algorithm>

using namespace std;

Ekran::Ekran(QWidget *parent)
    : QWidget{parent}
{
    im=QImage(1000, 500, QImage::Format_RGB32);
    im.fill(0);
    obrazek1=QImage(":/zdj/galio.jpg");
    obrazek2=QImage(":/zdj/twitch.jpg");
    lista1.push_back({250,150});
    lista1.push_back({100,300});
    lista1.push_back({400,300});
    lista3.push_back({250,150});
    lista3.push_back({100,300});
    lista3.push_back({400,300});
    lista2.push_back({750,150});
    lista2.push_back({600,300});
    lista2.push_back({900,300});
    resetScene();

}

void Ekran::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0,0,im);

}

void Ekran::mouseMoveEvent(QMouseEvent *e)
{
    coord pom;
    p1.x=e->pos().x();
    p1.y=e->pos().y();
    if(id!=-1)
    {
    if(!tryb)
    {
        changePosition(lista1);
    }
    else
    {
        changePosition(lista3);
    }
    }



}


void Ekran::mousePressEvent(QMouseEvent *e)
{

    coord pom;
    if(e->button()==Qt::LeftButton)
    {
        p1.x=e->pos().x();
        p1.y=e->pos().y();
        if(p1.x<im.width()&&p1.y<im.height())
        {
            id=-1;
            if(!tryb)
            {
                findId(lista1);
            }
            else
            {
                findId(lista3);
            }
        }

    }
}

void Ekran::setN(int newN)
{
    n = newN;
    changeLista2();
}

void Ekran::setTryb(bool newTryb)
{
    tryb = newTryb;
}

void Ekran::changeLista2()
{
    coord pom;
    for(int i=0;i<3;i++)
    {
        pom.x=(1-(n/100.0))*lista1[i].x+(n/100.0)*lista3[i].x;
        pom.y=(1-(n/100.0))*lista1[i].y+(n/100.0)*lista3[i].y;
        pom.x+=500;
        lista2[i]=pom;
    }
    resetScene();
}

void Ekran::drawPixel(int x,int y,int r,int g,int b,QImage *img)
{
    if((x<img->width()&&x>=0)&&(y<img->height()&&y>=0))
    {
        uchar *pix=img->scanLine(y)+4*x;
        pix[0]=b;
        pix[1]=g;
        pix[2]=r;
    }
}

void Ekran::getPixel(int x, int y, int &r, int &g, int &b,QImage *img)
{
    if((x<img->width()&&x>=0)&&(y<img->height()&&y>=0))
    {
        uchar *pix=img->scanLine(y)+4*x;
        b=pix[0];
        g=pix[1];
        r=pix[2];
    }
}

void Ekran::drawPunkt(int x,int y,int r,int g,int b)
{
    for(int i=y-2;i<=y+2;i++)
    {
        for(int j=x-2;j<=x+2;j++)
        {
          drawPixel(j,i,r,g,b,&im);
        }
    }
    update();
}

void Ekran::linia(int x1,int y1,int x2, int y2,int r,int g,int b)
{
    if(abs(y2-y1)<=abs(x2-x1))
    {
            float y=y1;
            float a=(float)(y2-y1)/(x2-x1);
            if(x1<x2)
            {
                for(int i=x1;i<=x2;i++)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b,&im);
                    y+=a;
                }
            }
            else
            {
                for(int i=x1;i>=x2;i--)
                {
                    drawPixel(i+0.5,y+0.5,r,g,b,&im);
                    y-=a;
                }
            }
        }
        else
        {
            float x=x1;
            float a=(float)(x1-x2)/(y1-y2);
            if(y1<y2)
            {
                for(int i=y1;i<=y2;i++)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b,&im);
                    x+=a;
                }
            }
            else
            {
                for(int i=y1;i>=y2;i--)
                {
                    drawPixel(x+0.5,i+0.5,r,g,b,&im);
                    x-=a;
                }
            }
        }
    update();
}

void Ekran::drawTriangle(int xA,int yA,int xB,int yB,int xC,int yC,int xAt,int yAt,int xBt,int yBt,int xCt,int yCt,int xAp,int yAp,int xBp,int yBp,int xCp,int yCp)
{
    color blend;
    int ymax=lista2[0].y,ymin=lista2[0].y;
    float v,w,u;
    int xt1,yt1,xt2,yt2;
    int a1,a2,b;
    bool raz1,raz2;
    float dolnadelta=1/(float)((xB-xA)*(yC-yA)-(yB-yA)*(xC-xA));
    QVector<wsp> wspl;
    QVector<int> tabX;
    for(coord i:lista2)
    {
        if(i.y>ymax)
        {
            ymax=i.y;
        }
        if(i.y<ymin)
        {
            ymin=i.y;
        }
    }
    for(int i=1;i<lista2.size();i++)
    {
        a1=lista2[i].y-lista2[i-1].y;
        a2=lista2[i].x-lista2[i-1].x;
        b=lista2[i].y*a2-lista2[i].x*a1;
        wspl.push_back({a1,a2,b});
    }
    a1=lista2[0].y-lista2[lista2.size()-1].y;
    a2=lista2[0].x-lista2[lista2.size()-1].x;
    b=lista2[0].y*a2-lista2[0].x*a1;
    wspl.push_back({a1,a2,b});
    for(int i=ymin;i<=ymax;i++)
    {
        tabX.clear();
        for(int j=1;j<lista2.size();j++)
        {
            check(tabX,wspl,j-1,j,i);
        }
        check(tabX,wspl,lista2.size()-1,0,i);
        sort(tabX.begin(),tabX.end());
        for(int j=1;j<tabX.size();j+=2)
        {
            p1.x=tabX[j-1];
            p2.x=tabX[j];
            raz1=false;
            raz2=false;
            v=dolnadelta*((p1.x-xA)*(yC-yA)-(i-yA)*(xC-xA));
            w=dolnadelta*((xB-xA)*(i-yA)-(yB-yA)*(p1.x-xA));
            u=1-v-w;
            for(int k=p1.x;k<=p2.x;k++)
            {
                findPosition(raz1,xt1,yt1,&obrazek1,xAt,yAt,xBt,yBt,xCt,yCt,u,v,w);
                findPosition(raz2,xt2,yt2,&obrazek2,xAp,yAp,xBp,yBp,xCp,yCp,u,v,w);
                getPixel(xt1,yt1,l1.red,l1.green,l1.blue,&obrazek1);
                getPixel(xt2,yt2,l2.red,l2.green,l2.blue,&obrazek2);
                blend.red=(1-(n/100.0))*l1.red+(n/100.0)*l2.red;
                blend.green=(1-(n/100.0))*l1.green+(n/100.0)*l2.green;
                blend.blue=(1-(n/100.0))*l1.blue+(n/100.0)*l2.blue;
                drawPixel(k,i,blend.red,blend.green,blend.blue,&im);
            }
        }

    }
}


void Ekran::maxMin(int &l1,int &l2)
{
    int pom;
    if(l1<l2)
    {
       pom=l1;
       l1=l2;
       l2=pom;
    }
}


void Ekran::check(QVector<int> &tabX,QVector <wsp> wspl,int index1,int index2,int i)
{
    int x;
    int point1,point2;
    point1=lista2[index1].y;
    point2=lista2[index2].y;
    maxMin(point1,point2);
    if(i<point1&&i>=point2)
    {
        if(wspl[index1].a1!=0)
        {
            x=(i*wspl[index1].a2-wspl[index1].b)/(float)wspl[index1].a1;
            point1=lista2[index1].x;
            point2=lista2[index2].x;
            maxMin(point1,point2);
            if(x<=point1&&x>=point2)
            {
                tabX.push_back(x);
            }
        }
    }
}

void Ekran::drawGranica()
{
    linia(498,0,498,500,158,154,142);
    linia(499,0,499,500,158,154,142);
    linia(500,0,500,500,158,154,142);
    linia(501,0,501,500,158,154,142);
    linia(502,0,502,500,158,154,142);
}

void Ekran::resetScene()
{

    im.fill(0);
    drawGranica();
    if(!tryb)
    {
        drawObrazek(&obrazek1);
        drawT(lista1);
    }
    else
    {
        drawObrazek(&obrazek2);
        drawT(lista3);
    }
    drawTriangle(lista2[0].x,lista2[0].y,lista2[1].x,lista2[1].y,lista2[2].x,lista2[2].y,lista1[0].x,lista1[0].y,lista1[1].x,lista1[1].y,lista1[2].x,lista1[2].y,lista3[0].x,lista3[0].y,lista3[1].x,lista3[1].y,lista3[2].x,lista3[2].y);
    drawT(lista2);
    update();
}


void Ekran::drawTriangleLines(QVector<coord> lista)
{
    for(int i=1;i<=2;i++)
    {
        linia(lista[i].x,lista[i].y,lista[i-1].x,lista[i-1].y,255,255,255);
    }
    linia(lista[2].x,lista[2].y,lista[0].x,lista[0].y,255,255,255);
}

void Ekran::drawT(QVector <coord> lista)
{
    drawTriangleLines(lista);
    for(int i=0;i<3;i++)
    {
        drawPunkt(lista[i].x,lista[i].y,203,206,212);
    }
}

void Ekran::drawObrazek(QImage *img)
{
    color pix;
    for(int i=0;i<img->height();i++)
    {
        for(int j=0;j<img->width();j++)
        {
            getPixel(j,i,pix.red,pix.green,pix.blue,img);
            drawPixel(j+50,i+100,pix.red,pix.green,pix.blue,&im);
        }
    }
}

void Ekran::findId(QVector<coord> lista)
{
    for(int i=0;i<3;i++)
    {
        if(sqrt(pow(lista[i].x-p1.x,2)+pow(lista[i].y-p1.y,2))<=10)
        {
            id=i;
            break;
        }
    }
}

void Ekran::findPosition(bool &raz,int &xt,int &yt,QImage *img,int xAp,int yAp,int xBp,int yBp,int xCp,int yCp,float u,float v,float w)
{

    if(!raz)
    {
        xt=u*xAp+v*xBp+w*xCp;
        yt=u*yAp+v*yBp+w*yCp;
        xt-=50;
        yt-=100;
        yt=yt%img->height();
        xt=xt%img->width();
        if(yt<0)
        {
            yt+=img->height();
        }
        if(xt<0)
        {
            xt+=img->width();
        }
        raz=true;
    }
    else
    {
        xt+=1;
        xt=xt%img->width();
    }

}

void Ekran::changePosition(QVector<coord> &lista)
{
    lista[id].x=p1.x;
    lista[id].y=p1.y;
    changeLista2();
}


