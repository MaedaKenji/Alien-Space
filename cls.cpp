#include <graphics.h>
#include <stdio.h>
#include <string>
#include <cmath>
using namespace std;

class CPesawat {
public:
    float x,y,s=1;
    float w;
    float xai,yai;
    float xc,yc;
    float xp=0,yp=-100;
    float vx=1,vy=1,vp=5;
    float xpeluru,ypeluru;
    float f=5,t=1,A=1.5,pi=3.14159265358979323846;
    //Exclusive enemy 3
    void *enemy;
    float xsize=255,ysize=225;
    unsigned int size;

    //Peluru
    float xm,ym;
    //Hitbox peluru
    float hx=0,hy=0,hw=0,hl=0;
    float hxp=0,hyp=0,hwp=0,hlp=0;


    int c=0;
    int counter=-1;
    float v=10;    
    float hx2,hy2;
    int weaponFlag=2,countdown_laser=0;
    void* torpedo;
    void* machinegun;
    void* laser[48];
    void *enemy1,*enemy2;



//Peluru
void FDPeluru()
{
    if (counter==0)
    {
        xm=mousex();
        ym=mousey();
        if(ym<500) ym=500;
        xpeluru=xm,ypeluru=ym;
        ypeluru-=v;
        hx=xpeluru-(hw/2);
        hy=ypeluru;
        hw=8;hl=-8;
        setcolor(YELLOW);
        circle(xm,ym-13,5);
        //rectangle(hx,hy,hx+hw,hy+hl);
        counter=1;
    }

    else if (counter==1)
    {
        ypeluru-=v;
        hx=xpeluru-(hw/2);
        hy=ypeluru-8;
        hw=8;hl=-8;

        setcolor(YELLOW);
        circle(xpeluru,ypeluru-13,5);
        //rectangle(xpeluru-2,ypeluru-2,xpeluru+2,ypeluru);  betul
        // rectangle(hx,hy,hx+hw,hy+hl);


    }

    else if (counter==10)
    {
        xm=1000;
        ym=1000;
        xpeluru=1000;
        ypeluru=1000;
        hx=xm;
        hy=ym;
        hw=8;hl=8;
    }
}

void FGTorpedo()
{
    readimagefile("src/image/torpedo.jpg",0,0,40,64);
    unsigned int size=imagesize(0,0,40,64);
    torpedo=malloc(size);
    getimage(0,0,40,64,torpedo);
    cleardevice();
}

void FGMachineGun()
{
    cleardevice();
    readimagefile("src/image/MachineGun.jpg",0,0,40,40);
    unsigned int size=imagesize(0,0,40,40);
    machinegun=malloc(size);
    getimage(0,0,40,40,machinegun);
    cleardevice();
}

void FGLaser () //Survival Mode
{
   for (int i=0;i<48;i++)
   {
        string num = to_string(i);
        string filename = "src/image/laser/laserp" + string(5 - num.length(), '0') + num +".bmp";
        const char* str = filename.c_str();
        readimagefile(str,0,0,64,464);
        size = imagesize(0,0,64,464);
        laser[i] = malloc(size);
        getimage(0,0,64,464,laser[i]);
        cleardevice();
        
        
   }
}

void FDLaser (float xp,float yp) // Survival Mode
{
    if (weaponFlag==3)
    {
         if (GetAsyncKeyState(VK_LBUTTON))
         {
            hx=xp-36;
            hy=yp-468;
            hw=56;
            hl=468;
            //rectangle(hx,hy,hx+hw,hy+hl);
            countdown_laser++;
            if (countdown_laser>47) countdown_laser=0;
            putimage(xp-36,yp-468,laser[countdown_laser],0);
         }

            else
            {
                countdown_laser=0;
                hx=0;
                hy=0;
                hw=0;
                hl=0;
                //rectangle(hx,hy,hx+hw,hy+hl);
            }
        
        
    }
    
}

void FDPeluru2(float yp) //Survival
{
    if (counter==0 && weaponFlag==1)
    {
        xm=mousex();
        ym=yp;
        putimage(xm-25,ym-63,torpedo,0);
        hx=xm-25;
        hy=ym+40;
        hw=40;
        hl=64;
        counter=1;
    }

    if (counter==0 && weaponFlag==2)
    {
        xm=mousex();
        ym=yp;
        //Kanan
        putimage(xm+55.5,ym-10,machinegun,1);
        //Kiri
        putimage(xm-82.5,ym-10,machinegun,1);
        hx=xm-66;
        hy=ym-10;
        hx2=xm+70;
        hy2=ym-10;
        hw=8;
        hl=40;
        counter=1;
        // rectangle(xm-66,ym-10,xm-58,ym+30);
        // rectangle(hx,hy,hx+hw,hy+hl);
        // rectangle(hx2,hy2,hx2+hw,hy2+hl);
    }

    if (counter==1 && weaponFlag==1)
    {
        ym-=v;
        hx=xm-25;
        hy=ym+10;
        putimage(xm-25,ym+10,torpedo,XOR_PUT);
        
    }

    if (counter==1 && weaponFlag==2)
    {
        ym-=v;
        hx=xm-66;
        hy=ym-10;
        hx2=xm+70;
        hy2=ym-10;
        putimage(xm-82.5,ym-10,machinegun,1);
        putimage(xm+55.5,ym-10,machinegun,1);
        // rectangle(hx,hy,hx+hw,hy+hl);
        // rectangle(hx2,hy2,hx2+hw,hy2+hl);
        //putimage(xm-81.5+81.5,ym,machinegun,1);
        //putimage(xm-81.5+115.3,ym,machinegun,1);
    }

    if (counter==10)
    {
        xm=1000;
        ym=1000;
        hx=xm;
        hy=ym;
        hw=0;
        hl=0;
        counter=-1;
        //putimage(xm-25,ym-63,torpedo,XOR_PUT);
    }
}
//Peluru Enemy versi line
void FDPEnemy()
{
    if (xc==0)
        {
        setcolor(LIGHTRED);
        xai=x;
        yai=y;
        // circle(xpeluru,ypeluru-13,5);
        yai+=v;
        rectangle(xai-2,yai-2,xai+2,yai);
        hxp=xai-2;
        hyp=yai-2;
        hwp=4;hlp=2;
        //rectangle(hxp,hyp-2,hxp+4,hyp);

        xc=1;
        }

    else if (xc == 1)
    {
        rectangle(xai-2,yai-2,xai+2,yai);
        yai+=v;
        hxp=xai-2;
        hyp=yai-2;
        hwp=4;hlp=2;
        // rectangle(hxp,hyp-2,hxp+4,hyp);

        if(yai>650) xc=0;
    }



}

//Player
void FDPlayer()
{
    xp=mousex();
    yp=mousey();
    if(yp<500) yp=500;
    hx= xp-70;
    hy= yp;
    hw=140;
    hl=80;
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
    line(xp-27*s,yp+27*s,xp-27*s,yp+10*s);
    line(xp-22*s,yp+22*s,xp-22*s,yp+10*s);
    //rectangle(xp-27*s,yp+13*s,xp-22*s,yp+8*s);

    //Machinegun Kanan
    line(xp+27*s,yp+27*s,xp+27*s,yp+10*s);
    line(xp+22*s,yp+22*s,xp+22*s,yp+10*s);
    //rectangle(xp+27*s,yp+13*s,xp+22*s,yp+8*s);

    //Senjata Depan
    line(xp,yp,xp-5*s,yp-5*s);
    line(xp-5*s,yp-5*s,xp+5*s,yp-5*s);
    line(xp,yp,xp+5*s,yp-5*s);
}
//Player
void FDPlayer2(float xp,float yp)
{
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
    //rectangle(xp-27*s,yp+13*s,xp-22*s,yp+8*s);
    //Machinegun Kanan
    line(xp+27*s,yp+27,xp+27*s,yp+10*s);
    line(xp+22*s,yp+22,xp+22*s,yp+10*s);
    //rectangle(xp+27*s,yp+13*s,xp+22*s,yp+8*s);

    //Senjata Depan
    line(xp,yp,xp-5*s,yp-5*s);
    line(xp,yp,xp+5*s,yp-5*s);
    line(xp-5*s,yp-5*s,xp+5*s,yp-5*s);
    //line(xp,0,xp,800);
    //line(xp-35,0,xp-35,800);

}
void Fgetplayer()
{
    readimagefile("/src/image/player.bmp",0,0,163,80);
    unsigned int sizep = imagesize(0,0,163,80);
    void *player = malloc(sizep);
    getimage(0,0,163,80,player);
}
//Enemy
void FDraw()
{
    if (y<0 || y>400) {vy*=-1;}
    if (x<0 || x>765) {vx*=-1;}
    //if (y!= -1000)
    y+=vy;
    x+=vx;

    hx= x-35;
    hy= y-40;
    hw= 70;
    hl= 40;

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
    //rectangle(x-27*s,y-13*s,x-22*s,y-8*s);
    //Machinegun Kanan
    line(x+27*s,y-27,x+27*s,y-10*s);
    line(x+22*s,y-22,x+22*s,y-10*s);
    //rectangle(x+27*s,y-13*s,x+22*s,y-8*s);


}
//Line Pesawat
void FDraw2()
{
    if (y<0 || y>400) {vy*=-1;}
    if (x<0 || x>765) {vx*=-1;}
    //if (y!= -1000)
    y+=vy;
    x+=vx;

    hx=x-40;hy=y-100;hw=80;hl=100,s=10;
    //rectangle(hx,hy,hx+hw,hy+hl);
        setcolor(YELLOW);
    	line(x,y-0.16*s,x-0.12*s,y-0.36*s);
        line(x-0.12*s,y-0.36*s,x-0.23*s,y-0.77*s);
        line(x-0.23*s,y-0.77*s,x-0.26*s,y-1.02*s);
        line(x-0.23*s,y-0.77*s,x-0.26*s,y-1.02*s);
        line(x-0.26*s,y-1.02*s,x-0.3*s,y-1.48*s);
        line(x-0.3*s,y-1.48*s,x-0.32*s,y-1.9*s);
        line(x-0.32*s,y-1.9*s,x-0.32*s,y-2.38*s);
        line(x-0.32*s,y-2.38*s,x-0.68*s,y-2.36*s);
        line(x-0.68*s,y-2.36*s,x-1.43*s,y-4.24*s);

        //Sayapp
        line(x-1.43*s,y-4.24*s,x-3.79*s,y-5.03*s);
        line(x-3.79*s,y-5.03*s,x-4.06*s,y-5.32*s);
        line(x-4.06*s,y-5.32*s,x-4.15*s,y-5.7*s);
        line(x-4.15*s,y-5.7*s,x-0.96*s,y-5.48*s);
        line(x-0.96*s,y-5.48*s,x-1*s,y-6*s);
        line(x-1*s,y-6*s,x-2.17*s,y-7.6*s);
        line(x-2.17*s,y-7.6*s,x-1.96*s,y-7.9*s);
        line(x-1.96*s,y-7.9*s,x-0.98*s,y-7.69*s);
        line(x-0.98*s,y-7.69*s,x-0.9*s,y-7.32*s);
        line(x-0.9*s,y-7.32*s,x-0.83*s,y-8.15*s);
        line(x-0.83*s,y-8.15*s,x-0.6*s,y-7.64*s);
        line(x-0.6*s,y-7.64*s,x-0.12*s,y-7.64*s);
        line(x-0.12*s,y-7.64*s,x-0.12*s,y-7.89*s);

        //Peluru satu
        line(x-1.63*s,y-4.28*s,x-1.62*s,y-3.78*s);
        line(x-1.62*s,y-3.78*s,x-1.66*s,y-3.54*s);
        line(x-1.66*s,y-3.54*s,x-1.71*s,y-3.4*s);
        line(x-1.71*s,y-3.4*s,x-1.81*s,y-3.15*s);

        line(x-1.81*s,y-3.15*s,x-1.9*s,y-3.4*s);
        line(x-1.9*s,y-3.4*s,x-1.95*s,y-3.55*s);
        line(x-1.95*s,y-3.55*s,x-1.99*s,y-3.76*s);
        line(x-1.99*s,y-3.76*s,x-1.99*s,y-4.43*s);

        //Peluru Dua
        line(x-2.4*s,y-4.5*s,x-2.4*s,y-4*s);
        line(x-2.4*s,y-4*s,x-2.46*s,y-3.84*s);
        line(x-2.46*s,y-3.84*s,x-2.5*s,y-3.74*s);
        line(x-2.5*s,y-3.74*s,x-2.55*s,y-3.65*s);

        line(x-2.55*s,y-3.65*s,x-2.6*s,y-3.74*s);
        line(x-2.6*s,y-3.74*s,x-2.64*s,y-3.84*s);
        line(x-2.64*s,y-3.84*s,x-2.72*s,y-4*s);
        line(x-2.72*s,y-4*s,x-2.72*s,y-4.64*s);


        //Kanan
        line(x,y-0.16*s,x+0.12*s,y-0.36*s);
        line(x+0.12*s,y-0.36*s,x+0.23*s,y-0.77*s);
        line(x+0.23*s,y-0.77*s,x+0.26*s,y-1.02*s);
        line(x+0.23*s,y-0.77*s,x+0.26*s,y-1.02*s);
        line(x+0.26*s,y-1.02*s,x+0.3*s,y-1.48*s);
        line(x+0.3*s,y-1.48*s,x+0.32*s,y-1.9*s);
        line(x+0.32*s,y-1.9*s,x+0.32*s,y-2.38*s);
        line(x+0.32*s,y-2.38*s,x+0.68*s,y-2.36*s);
        line(x+0.68*s,y-2.36*s,x+1.43*s,y-4.24*s);

        //Sayap
        line(x+1.43*s,y-4.24*s,x+3.79*s,y-5.03*s);
        line(x+3.79*s,y-5.03*s,x+4.06*s,y-5.32*s);
        line(x+4.06*s,y-5.32*s,x+4.15*s,y-5.7*s);
        line(x+4.15*s,y-5.7*s,x+0.96*s,y-5.48*s);
        line(x+0.96*s,y-5.48*s,x+1*s,y-6*s);
        line(x+1*s,y-6*s,x+2.17*s,y-7.6*s);
        line(x+2.17*s,y-7.6*s,x+1.96*s,y-7.9*s);
        line(x+1.96*s,y-7.9*s,x+0.98*s,y-7.69*s);
        line(x+0.98*s,y-7.69*s,x+0.9*s,y-7.32*s);
        line(x+0.9*s,y-7.32*s,x+0.83*s,y-8.15*s);
        line(x+0.83*s,y-8.15*s,x+0.6*s,y-7.64*s);
        line(x+0.6*s,y-7.64*s,x+0.12*s,y-7.64*s);
        line(x+0.12*s,y-7.64*s,x+0.12*s,y-7.89*s);
        //Peluru satu
        line(x+1.63*s,y-4.28*s,x+1.62*s,y-3.78*s);
        line(x+1.62*s,y-3.78*s,x+1.66*s,y-3.54*s);
        line(x+1.66*s,y-3.54*s,x+1.71*s,y-3.4*s);
        line(x+1.71*s,y-3.4*s,x+1.81*s,y-3.15*s);

        line(x+1.81*s,y-3.15*s,x+1.9*s,y-3.4*s);
        line(x+1.9*s,y-3.4*s,x+1.95*s,y-3.55*s);
        line(x+1.95*s,y-3.55*s,x+1.99*s,y-3.76*s);
        line(x+1.99*s,y-3.76*s,x+1.99*s,y-4.43*s);

        //Peluru Dua
        line(x+2.4*s,y-4.5*s,x+2.4*s,y-4*s);
        line(x+2.4*s,y-4*s,x+2.46*s,y-3.84*s);
        line(x+2.46*s,y-3.84*s,x+2.5*s,y-3.74*s);
        line(x+2.5*s,y-3.74*s,x+2.55*s,y-3.65*s);

        line(x+2.55*s,y-3.65*s,x+2.6*s,y-3.74*s);
        line(x+2.6*s,y-3.74*s,x+2.64*s,y-3.84*s);
        line(x+2.64*s,y-3.84*s,x+2.72*s,y-4*s);
        line(x+2.72*s,y-4*s,x+2.72*s,y-4.64*s);
}

void FSOLDAE(float x, float y)
{
    readimagefile("src/object/3.jpg",x,y,x+xsize,y+ysize);
}

void FDraw3(){
    readimagefile("src/object/3.jpg",x,y,x+xsize,y+ysize);
    size = imagesize(x,y,x+xsize,y+ysize);
    enemy = malloc(size);
    getimage(x,y,x+xsize,y+ysize,enemy);

}
//Survival Mode Structure
void FDSurvival()
{
    cleardevice();
    unsigned int sizep;
    //Enemy1
    readimagefile("src/image/enemy1.jpg",0,0,163,80);
    sizep = imagesize(0,0,163,80);
    enemy1 = malloc(sizep);
    getimage(0,0,163,80,enemy1);
    cleardevice();

    //Enemy2
    readimagefile("src/image/enemy2.jpg",0,0,137,140);
    sizep = imagesize(0,0,137,140);
    enemy2 = malloc(sizep);
    getimage(0,0,137,140,enemy2);
    cleardevice();
}
//Wandering
float Fwandering(int flag)
{
   if (flag == 0) return A * sin(2*pi*f*t);
   else if (flag == 1) return A * sin((2*pi*f*t) + pi/4);
   t+=10;
}
};


