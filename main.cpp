#include <time.h>
#include <graphics.h>
#include <windows.h>
#include "mmsystem.h"

class CPesawat {
public:
    float x,y,s=1;
    float w;
    float xp=0,yp=530;
    float vx,vy,vp=5;
    float xpeluru,ypeluru;
    //Peluru
    float xm,ym;
    //float x,y;
    int c=0;
    int counter=-1;
    float v=20;
    float hx=0,hy=0,hw=70,hl=40;

//Peluru
void FDPeluru()
{
    if (counter==0)
    {
        xm=mousex();
        ym=mousey();
        if(ym<500) ym=500;
        xpeluru=xm,ypeluru=ym;
        hx=xm-5;
        hy=ym-13;
        hw=5;hl=5;


        setcolor(YELLOW);
        circle(xm,ym-13,5);

        ym-=v;

        counter=1;
    }

    if (counter==1)
    {
        hx=xpeluru-5;
        hy=ypeluru-13;
        hw=5;hl=5;

        setcolor(YELLOW);
        circle(xpeluru,ypeluru-13,5);

        ypeluru-=v;
        if(ypeluru<0) counter=-1;
    }

    if (counter == 2)
    {
        xpeluru=10000;
        ypeluru=10000;
        hx=xpeluru-5;
        hy=ypeluru-5;
    }

}
//Player
void FDPlayer()
{
    xp=mousex();
    hx= x-35;
    hy= y-40;

    setcolor(LIGHTCYAN);
    line(xp,yp,xp-35*s,yp+35*s);
    line(xp,yp,xp+35*s,yp+35*s);

    line(xp-35*s,yp+35*s,xp-30*s,yp+40*s);
    line(xp+35*s,yp+35*s,xp+30*s,yp+40*s);

    line(xp-30*s,yp+40*s,xp-20*s,yp+30*s);
    line(xp+30*s,yp+40*s,xp+20*s,yp+30*s);

    line(xp-20*s,yp+30*s,xp-10*s,yp+40*s);
    line(xp+20*s,yp+30*s,xp+10*s,yp+40*s);

    line(xp-10*s,yp+40*s,xp,yp+30*s);
    line(xp+10*s,yp+40*s,xp,yp+30*s);

    //Pembatas permainan
}

void FDraw()
{
    hx= x-35;
    hy= y-40;

    setcolor(w);
    line(x,y,x-35*s,y-35*s);
    line(x,y,x+35*s,y-35*s);

    line(x-35*s,y-35*s,x-30*s,y-40*s);
    line(x+35*s,y-35*s,x+30*s,y-40*s);

    line(x-30*s,y-40*s,x-20*s,y-30*s);
    line(x+30*s,y-40*s,x+20*s,y-30*s);

    line(x-20*s,y-30*s,x-10*s,y-40*s);
    line(x+20*s,y-30*s,x+10*s,y-40*s);

    line(x-10*s,y-40*s,x,y-30*s);
    line(x+10*s,y-40*s,x,y-30*s);

}

void FGerak()
{
    if (y<0 || y>400) vy*=-1;
    if (x<0 || x>765) vx*=-1;
    y+=vy;
    x+=vx;
}

void FDGaris()
{
    setcolor(getmaxcolor());
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    rectangle(0,500,798,520);
    floodfill(500,510,getmaxcolor());
}
};



bool Fcollision(CPesawat p, CPesawat a)
{
    if (
        p.hx < a.hx+a.hw &&
        p.hx + p.hw > a.hx &&
        p.hy < a.hy+a.hl &&
        p.hy + p.hl > a.hy
        ) return 1;
    else return 0;
}

int main()
{
    initwindow(800,600,"Alien Space");
    srand(time(0));
    CPesawat a[10];
    CPesawat p;
    CPesawat peluru[10];
    int counter=0;
    int page =0;
    int ccolision=0;
    p.c=1;
    int music=0;

    for (int i=0;i<10;i++)
    {
    a[i].x=rand()%750;
    a[i].y=rand()%400;
    a[i].vx=rand()%10+5;
    a[i].vy=rand()%10+5;
    a[i].w=rand()%16;
    //Permisi peluru ngikut loop :)
    peluru[i].counter=-1;
    }

    rectangle(0, 0, getmaxx(), getmaxy());

    while(!kbhit())
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        p.FDPlayer();
        p.FDGaris();
        for (int i=0;i<10;i++)
        {
            a[i].FGerak();
            a[i].FDraw();
        }
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            peluru[counter].counter=0;
            counter++;
        }
        if (ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            music++;
            if(music > 1) music=0;
            if (music) PlaySound(TEXT("Tetris.wav"),NULL,SND_ASYNC || SND_LOOP);
            else PlaySound(0,0,0);
        }
            for (int i=0;i<10;i++)
            {
            for (int j=0;j<10;j++)
                {
                    if(Fcollision(peluru[i],a[j]))
                    {
                        peluru[i].counter=2;
                        a[j].x=-1000;
                        a[j].y=-1000;
                        outtextxy(100,530,"Kena");
                        ccolision++;

                        if (ccolision>15)
                        {

                            delay(1000);
                            ccolision=0;
                        }
                    }
                }
            }

        if(counter>10)counter=0;
        for(int i=0;i<10;i++)
        {
            peluru[i].FDPeluru();
        }

        page=1-page;
        delay(20);
    }
    //End While loop
    return 0;
}
