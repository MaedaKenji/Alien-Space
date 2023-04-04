#include <iostream>
#include <graphics.h>
#include "graphics.h"
#include <time.h>
#include "cls.cpp"
#include "story.h"
#include <windows.h>
#include "mmsystem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;


int CGO=0;
int page=0,flag=0;
//char str[100]="src/image/laser00001.jpg";
                    //   15
string filename,num;
int i=1;

int Fcollision(CPesawat p, CPesawat a)
{
    if (
        p.hx < a.hx+a.hw &&
        p.hx + p.hw > a.hx &&
        p.hy < a.hy+a.hl &&
        p.hy + p.hl > a.hy
        ) return 1;
    else return 0;
}

int Fcollision2(CPesawat p, CPesawat a)
{
    if (
        p.hx < a.hx+a.hw &&
        p.hx + p.hw > a.hx &&
        p.hy < a.hl+a.hy &&
        p.hy + p.hl > a.hy
        )
        {
            return 1;
        }
    else return 0;
}

int FCPlayer(CPesawat p, CPesawat a)
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
    cleardevice();
    readimagefile("src/loading/Loading2.jpg",0,0,800,600);
    rectangle(328,555,475,565);
    for (int i=0;i<140;i++)
    {
        rectangle(328+i,555,335+i,565);
        delay(1);
    }
}

int Fmainmenu()
{
    PlaySound(TEXT("src/sfx/bgm.wav"),NULL,SND_ASYNC||SND_LOOP);
    int fe=0;
    flag=1;
    delay(100);

    while(1)
        {
        if (GetAsyncKeyState(49)) flag=1;
        if (GetAsyncKeyState(50)) flag=2;
        if (GetAsyncKeyState(51)) flag=3;
        if (GetAsyncKeyState(13)) fe=1;

            if (flag==1)
            {
                readimagefile("src/menu/1.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/2.jpg",0,0,800,600);
                delay(500);
            }
            else if (flag==2)
            {
                readimagefile("src/menu/1.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/3.jpg",0,0,800,600);
                delay(500);

            }
            else if (flag==3)
            {
                readimagefile("src/menu/1.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/4.jpg",0,0,800,600);
                delay(500);

            }

            if (flag==1 && fe==1)
            {
                fe=0;
                return 1;
            }

            else if (flag==2 && fe==1)
            {
                fe=0;
                return 2;
            }

            else if (flag==3 && fe==1)
            {
                fe=0;
                return 3;
            }
        }
}

int Flevel()
{
    int flag = 1,fe=0;

    while(1)
    {
        if (GetAsyncKeyState(49)) { flag=1; fe=0;}
        if (GetAsyncKeyState(50)) { flag=2; fe=0;}
        if (GetAsyncKeyState(51)) { flag=3; fe=0;}
        if (GetAsyncKeyState(13)) fe=1;

        if (flag==1)
            {
                readimagefile("src/menu/Level.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/Level 1.jpg",0,0,800,600);
                delay(500);
            }
        else if (flag==2)
            {
                readimagefile("src/menu/Level.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/Level 2.jpg",0,0,800,600);
                delay(500);
            }
        else if (flag==3)
            {
                readimagefile("src/menu/Level.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/Level 3.jpg",0,0,800,600);
                delay(500);
            }
        if (flag==1 && fe==1)
        {
            PlaySound(NULL,NULL,SND_ASYNC);
            return 1;
        }
        else if (flag==2 && fe==1)
        {
            PlaySound(NULL,NULL,SND_ASYNC);
            return 2;
        }
        else if (flag==3 && fe==1)
        {
            PlaySound(NULL,NULL,SND_ASYNC);
            return 3;
        }

    }
}

int Freturn()
{
        int a=0;
        while(a)
        {

            if (GetAsyncKeyState(32)) { return 1;}
            else if (GetAsyncKeyState(27)) { return 0;}
        }
    return 0;
}


void Game(int flag)
{
    srand(time(0));
    CPesawat a[10];
    CPesawat p;
    CPesawat peluru[10];
    int gerak[10],cscore=0,score=0,counter=0,music=0;
    p.c=1;

    char str[5]="0";

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
    //PlaySound(TEXT("Tetris.wav"),NULL,SND_ASYNC || SND_LOOP);

    if (flag==1)
    {
        while(1)
    {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        readimagefile("src/SpaceBG.jpg",0,0,800,600);
//        setbkcolor(BLACK);
        p.FDPlayer();

        for (int i=0;i<10;i++)
        {
            //a[i].FGerak();
            a[i].FDraw();
            a[i].FDPEnemy();
            peluru[i].FDPeluru();
        }
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            PlaySound(TEXT("src/sfx/laser.wav"),NULL,SND_ASYNC);
            peluru[counter].counter=0;
            counter++;
        }
        // if (ismouseclick(WM_RBUTTONDOWN))
        // {
        //     clearmouseclick(WM_RBUTTONDOWN);
        //     music++;
        //     if(music > 1) music=0;
        //     //if (music) PlaySound(TEXT("Tetris.wav"),NULL,SND_ASYNC || SND_LOOP);
        //     else PlaySound(0,0,0);
        // }
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
                        CGO=1;
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
        // for(int i=0;i<10;i++)
        // {

        // }
        sprintf(str,"%d",score);
        settextstyle(0,HORIZ_DIR,2);
        setcolor(YELLOW);
        outtextxy(20,580,"Score: ");
        outtextxy(108,580,str);

        page=1-page;
        //delay(20);
        if (CGO==1)
        {
            break;
        }
    }
    }
    else if (flag==2)
    {
            while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();
            readimagefile("src/SpaceBG.jpg",0,0,800,600);
    //        setbkcolor(BLACK);
            p.FDPlayer();

            for (int i=0;i<10;i++)
            {
                //a[i].FGerak();
                a[i].FDraw2();
                a[i].FDPEnemy();
                peluru[i].FDPeluru();
            }
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                PlaySound(TEXT("src/sfx/laser.wav"),NULL,SND_ASYNC);
                peluru[counter].counter=0;
                counter++;
            }
            // if (ismouseclick(WM_RBUTTONDOWN))
            // {
            //     clearmouseclick(WM_RBUTTONDOWN);
            //     music++;
            //     if(music > 1) music=0;
            //     //if (music) PlaySound(TEXT("Tetris.wav"),NULL,SND_ASYNC || SND_LOOP);
            //     else PlaySound(0,0,0);
            // }
                for (int i=0;i<10;i++)
                {
                for (int j=0;j<10;j++)
                    {
                        if(Fcollision2(peluru[i],a[j]))
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
                            CGO=1;
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
            // for(int i=0;i<10;i++)
            // {

            // }
            sprintf(str,"%d",score);
            settextstyle(0,HORIZ_DIR,2);
            setcolor(YELLOW);
            outtextxy(20,580,"Score: ");
            outtextxy(108,580,str);

            page=1-page;
            //delay(20);
            if (CGO==1)
            {
                break;
            }
        }
    }
    else if (flag==3)
    {
        void *enemy,*player;
        unsigned int size,sizep,sizeb;
        float x=100,y=100,vx=2,vy=1;
        float xp;
        float yp;
        page=0;

        // outtextxy(10,0,"Ini page 0");
        // getch();
        // setactivepage(1);
        // outtextxy(10,0,"Ini page 1");
        setactivepage(1);

        readimagefile("src/object/3.jpg",x,y,x+255,y+225);
        size = imagesize(x,y,x+255,y+225);
        enemy = malloc(size);
        getimage(x,y,x+255,y+225,enemy);
        cleardevice();

        p.FDPlayer2(x,y);
        sizep = imagesize(x-35,y-5,x+35,y+40);
        player = malloc(sizep);
        getimage(x-35,y-5,x+35,y+40,player);
        cleardevice();

        peluru[0].FGTorpedo();
        for(int i=0;i<10;i++)
        {
            peluru[i].torpedo=peluru[0].torpedo;
        }

        //Laser
        void* laser[265];
        for (int i=0;i<=265;i++)
        {
        string num = to_string(i);
        string filename = "src/image/laser/laser" + string(5 - num.length(), '0') + num+".jpg";
        const char* str = filename.c_str();
        readimagefile(str,0,0,800,600);
        size = imagesize(306,0,496,576);
        laser[i] = malloc(size);
        getimage(306,0,496,576,laser[i]);
        cleardevice();
        }

//void* laser;
//readimagefile("src/image/laser/laser00010.jpg",0,0,800,600);
//sizeb=(0,0,800,600);
//laser = malloc(sizeb);
//getimage(0,0,800,600,laser);
//cleardevice();

cout<<"Selesai for";

        int i=0;
        counter=0;
        y=0;
        PlaySound(TEXT("src/sfx/BGBoss.wav"),NULL,SND_LOOP | SND_ASYNC);
        while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();

            xp=mousex();yp=mousey();
            x += vx;
            y += vy;
            if (x >= 575 || x<0) vx *= -1;
            if (y >= 60  || y <=0 ) vy*=-1;
            //rectangle(x+127.5,y+225,800,600);
            putimage(x+38,y+215,laser[i],XOR_PUT);
            putimage(xp-35,yp,player,XOR_PUT);
            putimage(x,y,enemy,XOR_PUT);

            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                //PlaySound(TEXT("src/sfx/laser.wav"),NULL,SND_ASYNC);
                peluru[counter].counter=0;
                counter++;
            }
            if(counter>10)counter=0;
            for (int j=0;j<10;j++)
            {
                peluru[j].FDPeluru2();
            }



            i++;
            if(i>=265) i=0;

            //rectangle(0,30,100,30);
            //putimage(xp,yp,player,XOR_PUT);
            // setvisualpage(1-page);

            page=1-page;
            delay(10);
        }
        free(enemy);
        free(player);
        free(laser);
        PlaySound(NULL,NULL,SND_ASYNC);

    }

closegraph();
}


int main()
{
    int cgo=0;
    int flag=0;
    //char str[10000]="Terdapat sebuah planet yang telah dikuasai oleh para alien jahat yang ingin menguasai seluruh galaksi. Para alien tersebut telah melakukan serangan ke berbagai planet yang ada di sekitarnya, dan mereka berencana untuk menyerang planet yang berada di pusat galaksi. Untuk menghentikan para alien jahat ini, diperlukan kehadiran prajurit luar angkasa yang handal dan berani. Prajurit luar angkasa yang dipilih untuk misi ini adalah Kapten John. Ia telah memiliki pengalaman bertempur yang cukup banyak, dan telah melalui berbagai pelatihan dan simulasi pertempuran melawan alien. Kapten John bersama timnya diberi misi untuk mencegah para alien jahat ini menyerang planet pusat galaksi. Misi Kapten John dimulai dengan menyusup ke dalam kapal musuh dan menghancurkan pusat kendali kapal. Setelah berhasil menghancurkan pusat kendali, Kapten John dan timnya berhasil mendarat di planet yang dijadikan markas oleh para alien jahat.";
    initwindow(800,600,"Alien Space");
    CPesawat p;


    mainmenu:
        int key=Fmainmenu();
        if (key==1) goto story;
        else if (key==2) return 0;
        else if (key==3) return 0;

    story:
        Fstory2();
    level:
       flag=Flevel();
       FLoading();
    game:
        Game(flag);
        initwindow(800,600,"Alien Space");
        delay(100);
        readimagefile("src/gover/GOver.jpg",0,0,800,600);
        PlaySound(TEXT("src/sfx/SFXGover.wav"),NULL,SND_ASYNC);
        delay(6000);
        if (Freturn()==1) goto mainmenu;
    esc:
        system("cls");
return 0;
}



