#include <graphics.h>
class CPesawat {
public:
    float x,y,s=1;
    float w;
    float xai,yai;
    float xc,yc;
    float xp=0,yp=530;
    float vx,vy,vp=5;
    float xpeluru,ypeluru;
    //Peluru
    float xm,ym;
    //float x,y;
    int c=0;
    int counter=-1;
    float v=20;
    float hx=0,hy=0,hw=70,hl=40,hxp=0,hyp=0,hwp=3,hlp=3;

//Peluru
void FDPeluru()
{
    if (counter==0)
    {
        xm=mousex();
        ym=mousey();
        if(ym<500) ym=500;
        xpeluru=xm,ypeluru=ym;

        setcolor(YELLOW);
        //circle(xm,ym-13,5);
        rectangle(xm-2,ym-2,xm+2,ym);

        hx=xm-5;
        hy=ym-13;
        hw=5;hl=5;
        ym-=v;
        counter=1;
    }

    else if (counter==1)
    {
        setcolor(YELLOW);
        //circle(xpeluru,ypeluru-13,5);
        rectangle(xpeluru-2,ypeluru-2,xpeluru+2,ypeluru);

        ypeluru-=v;
        hx=xpeluru-5;
        hy=ypeluru-13;
        hw=5;hl=5;
    }

    else if (counter==10)
    {
        xm=1000;
        ym=1000;
        xpeluru=1000;
        ypeluru=1000;
        hx=xm-5;
        hy=ym-13;
        hw=5;hl=5;
    }
}

void FDPEnemy()
{
    if (xc==0)
        {
        setcolor(LIGHTRED);
        xai=x;
        yai=y;
        //circle(xpeluru,ypeluru-13,5);
        yai+=v;
        //rectangle(xai-2,yai-2,xai+2,yai)
        hxp=xai-2;
        hyp=yai-2;
        hwp=4;hlp=2;
        rectangle(hxp,hyp-2,hxp+4,hyp);

        xc=1;
        }

    else if (xc == 1)
    {
        //rectangle(xai-2,yai-2,xai+2,yai);
        yai+=v;
        hxp=xai-2;
        hyp=yai-2;
        hwp=4;hlp=2;
        rectangle(hxp,hyp-2,hxp+4,hyp);

        if(yai>650) xc=0;
    }

}
//Player
void FDPlayer()
{
    xp=mousex();
    hx= xp-35;
    hy= yp;
    hw=70;
    hl=40;
    //rectangle(hx,hy,hx+70,hy-40);
    //line (hx,hy,hx,hy+hl);

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

    //Machinegun kiri
    line(xp-27*s,yp+27,xp-27*s,yp+10*s);
    line(xp-22*s,yp+22,xp-22*s,yp+10*s);
    rectangle(xp-27*s,yp+13*s,xp-22*s,yp+8*s);
    //Machinegun Kanan
    line(xp+27*s,yp+27,xp+27*s,yp+10*s);
    line(xp+22*s,yp+22,xp+22*s,yp+10*s);
    rectangle(xp+27*s,yp+13*s,xp+22*s,yp+8*s);

    //Senjata Depan
    line(xp,yp,xp-5*s,yp-5*s);
    line(xp-5*s,yp-5*s,xp+5*s,yp-5*s);
    line(xp,yp,xp+5*s,yp-5*s);
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

    //Machinegun kiri
    line(x-27*s,y-27,x-27*s,y-10*s);
    line(x-22*s,y-22,x-22*s,y-10*s);
    rectangle(x-27*s,y-13*s,x-22*s,y-8*s);
    //Machinegun Kanan
    line(x+27*s,y-27,x+27*s,y-10*s);
    line(x+22*s,y-22,x+22*s,y-10*s);
    rectangle(x+27*s,y-13*s,x+22*s,y-8*s);


}



void FGerak()
{
    if (y<0 || y>400) {vy*=-1;}
    if (x<0 || x>765) {vx*=-1;}
    //if (y!= -1000)
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
