#include <iostream>
#include <graphics.h>
#include <time.h>
#include "class.cpp"

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

bool FCPlayer(CPesawat p, CPesawat a)
{
    if (
        p.hx < a.hxp+a.hwp &&
        p.hx + p.hw > a.hxp &&
        p.hy < a.hyp+a.hlp &&
        p.hy + p.hl > a.hyp
        ) return 1;
    else return 0;
}

void FLoading()
{
    readimagefile("Loading2.jpg",0,0,800,600);
    rectangle(328,555,475,565);
    for (int i=0;i<140;i++)
    {
        rectangle(328+i,555,335+i,565);
        delay(1);
    }
}

void FGOver()
{
    readimagefile("GOver.jpg",0,0,800,600);
    for (int i=0;i<140;i++)
    {
        delay(1);
    }
    //delay(100);
    //outtextxy(100,100,"GAME");
}

void FDMoon()
{
    float s=10;
    float l,t;
    float rnd[10]={72,49,123,234,438,283,345,13,85,32};
    float rnd1[10]={532,439,123,234,438,283,345,13,85,232};

    setcolor(getmaxcolor());
    setfillstyle(SOLID_FILL,LIGHTBLUE);
    for (int i=0;i<10;i++)
    {
        arc(30+rnd[i],rnd1[i],67,294,s);
        arc(35+rnd[i],rnd1[i],113,246,s);
    }



    //floodfill(13,250,WHITE);

}

int main2()
{
    initwindow(800,600,"AlienSpace");
    FGOver();
}

int main()
{
    initwindow(800,600,"Alien Space");
    srand(time(0));
    CPesawat a[10];
    CPesawat p;
    CPesawat peluru[10];
    int gerak[10];
    int cscore=0;
    int score=0;
    bool CGO=0;
    int counter=0;
    int page =0;
    int ccolision=0;
    p.c=1;
    int music=0;
    char str[3];


        for (int i=0;i<10;i++)
            {
            a[i].x=rand()%750+1;
            a[i].y=0;
            gerak[i]=rand()%25+5;
            a[i].vx=gerak[i];
            if (i%2==0) a[i].vx*=-1;
            a[i].vy=rand()%25+5;
            a[i].w=LIGHTBLUE;
            a[i].xc=0;
            a[i].v=gerak[i];
            //Permisi peluru ngikut loop :)
            peluru[i].counter=10;
            peluru[i].v=25;
            }
    FLoading();
    while(CGO==0)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        setbkcolor(BLACK);
        //readimagefile("bg.jpg",0,0,800,600);
        sprintf(str,"%d",score);
        outtextxy(20,580,"Score: ");
        outtextxy(67,580,str);
        p.FDPlayer();
        //FDMoon();
        //p.FDGaris();
        for (int i=0;i<10;i++)
        {
            a[i].FGerak();
            a[i].FDraw();
            a[i].FDPEnemy();
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
                        a[j].y=-1000;
                        a[j].x=-2000;
                        a[j].hy=-1000;
                        a[j].hx=-2000;
                        peluru[i].counter=10;
                        score++;
                        cscore++;
                    }

                    if(FCPlayer(p,a[j]))
                    {
                        CGO =1;
                    }
                }
            }

        if(counter>10)counter=0;
        if (cscore%10==0 && cscore!=0)
            {
                for (int i=0;i<10;i++)
                {
                a[i].x=rand()%750+1;
                a[i].y=0;
                gerak[i]=rand()%25+5;
                a[i].vx=gerak[i];
                if (i%2==0) a[i].vx*=-1;
                a[i].vy=rand()%25+5;
                a[i].w=LIGHTBLUE;
                a[i].xc=0;
                a[i].v=gerak[i];
                cscore=0;
                //Permisi peluru ngikut loop :)
                }
            }
        for(int i=0;i<10;i++)
        {
            peluru[i].FDPeluru();
        }
        if (CGO==1)
        {
            cleardevice();
        }

        page=1-page;
        delay(20);
    }
    cleardevice();
    main2();
    //End While loop
}



