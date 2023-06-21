#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <cmath>
#include <sstream>
#include <vector>

#include "mmsystem.h"
#include "graphics.h"
#include "cls.cpp"
#include "story.h"
using namespace std;

int CGO=0;
int page=0,flag=0;
string filename,num;
int i=1;
int currency;
int shop_senjata;
float A=0.5f,f=10,dt=1,pi=3.14159265358979323846;



int Fcollision(CPesawat p, CPesawat a)
{
    // rectangle(p.hx,p.hy,p.hx+p.hw,p.hy+p.hl);
    // rectangle(a.hx,a.hy,a.hx+a.hw,a.hy+a.hl);
    if (
        p.hx < a.hx+a.hw &&
        p.hx + p.hw > a.hx &&
        p.hy < a.hy+a.hl &&
        p.hy + p.hl > a.hy
        ) return 1;
    else return 0;
}
int FCPlayer(CPesawat p, CPesawat a)
{    
    // rectangle(p.hx,p.hy,p.hx+p.hw,p.hy+p.hl);
    // rectangle(a.hxp,a.hyp,a.hxp+a.hwp,a.hyp+a.hlp);
    if (
        p.hx < a.hxp+a.hwp &&
        p.hx + p.hw > a.hxp &&
        p.hy < a.hyp+a.hlp &&
        p.hy + p.hl > a.hyp
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
int Fcollision3A(float a[], CPesawat b)
{
    // rectangle(a[0],a[1],a[0]+a[1],a[2]+a[3]);
    // rectangle(b.hx,b.hy,b.hx+b.hw,b.hy+b.hl);
    if (
        a[0] < b.hx+b.hw &&
        a[0] + a[1] > b.hx &&
        a[2] < b.hy+b.hl &&
        a[2] + a[3] > b.hy
        ) return 1;
    else return 0;
}
int Fcollision3B(float a[],float b[])
{
    //rectangle(a[0],a[1],a[0]+a[2],a[1]+a[3]);
    //rectangle(b[0],b[1],b[0]+b[2],b[1]+b[3]);
    /*
    0 = x
    1 = y
    2 = width
    3 = length
    */
    if (
        a[0] < b[0]+b[2] &&
        a[1] < b[1]+b[3] &&
        a[0] + a[2] > b[0] &&
        a[1] + a[3] > b[2]
        ) return 1;
    else return 0;
}
bool Fcollision3C(float a[], CPesawat b)
{
    // rectangle(a[0],a[1],a[0]+a[2],a[1]+a[3]);
    // rectangle(b.hx,b.hy,b.hx+b.hw,b.hy+b.hl);
    if (
        a[0] < b.hx+b.hw &&
        a[1] < b.hy+b.hl &&
        a[0] + a[2] > b.hx &&
        a[1] + a[3] > b.hy
        ) 
        {
            return 1;
        }
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
void Ftutorial()
{
    cleardevice();
    while(getch() != 27)    readimagefile("src/image/tutorial.jpg",0,0,800,600);
}
int Fmainmenu()
{
    PlaySound(TEXT("src/sfx/bgm.wav"),NULL,SND_ASYNC||SND_LOOP);
    int fe=0;
    flag=1;
    delay(1);
    
    while(1)
        {
            setactivepage(0);
            setvisualpage(0);
            if (GetAsyncKeyState(49)) flag=1;
            if (GetAsyncKeyState(50)) flag=2;
            if (GetAsyncKeyState(51)) flag=3;
            if (GetAsyncKeyState(52)) flag=4;
            if (GetAsyncKeyState(13)) fe=1;

                if (flag==1)
                {
                    readimagefile("src/menu/plain.jpg",0,0,800,600);
                    delay(500);
                    readimagefile("src/menu/play.jpg",0,0,800,600);
                    delay(500);
                }
                else if (flag==2)
                {
                    readimagefile("src/menu/plain.jpg",0,0,800,600);
                    delay(500);
                    readimagefile("src/menu/tutorial.jpg",0,0,800,600);
                    delay(500);

                }
                else if (flag==3)
                {
                    readimagefile("src/menu/plain.jpg",0,0,800,600);
                    delay(500);
                    readimagefile("src/menu/shop.jpg",0,0,800,600);
                    delay(500);

                }
                //Save file
                else if(flag==4)
                {
                    readimagefile("src/menu/plain.jpg",0,0,800,600);
                    delay(500);
                    readimagefile("src/menu/exit.jpg",0,0,800,600);
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

                else if (flag==4 && fe==1)
                {
                    fe=0;
                    return 4;
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
        if (GetAsyncKeyState(52)) { flag=4; fe=0;}
        if (GetAsyncKeyState(13)) fe=1;

        if (flag==1)
            {
                readimagefile("src/menu/level/plain.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/level/level1.jpg",0,0,800,600);
                delay(500);
            }
        else if (flag==2)
            {
                readimagefile("src/menu/level/plain.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/level/level2.jpg",0,0,800,600);
                delay(500);
            }
        else if (flag==3)
            {
                readimagefile("src/menu/level/plain.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/level/level3.jpg",0,0,800,600);
                delay(500);
            }
        else if (flag==4)
            {
                readimagefile("src/menu/level/plain.jpg",0,0,800,600);
                delay(500);
                readimagefile("src/menu/level/level4.jpg",0,0,800,600);
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
        else if (flag==4 && fe==1)
        {
            PlaySound(NULL,NULL,SND_ASYNC);
            return 4;
        }

    }
}
int Freturn()
{
        cout<<"Tekan tombol P untuk kembali ke menu utama"<<endl;
        cout<<"Tekan tombol ESC untuk keluar dari game"<<endl;
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        while(1)
        {
            int a = getch();
            if (a == 80) {return 1;} //80 == P, 112 == p
            else if (a==112) {return 1;}
            else if (a==27) {return 0;} //27==escape
        }
}
int FreadCurrency()
{
    //Note: Sekalian baca nilai shop_weapon
    
    ifstream file("currency.txt");
     if (file.is_open()) {
        // Membaca nilai variabel dari file
        file >> currency;
        file >> shop_senjata;
        cout<<shop_senjata<<endl;

        // Menutup file
        file.close();

        std::cout << "Nilai currency: " << currency << std::endl;
        return 1;
    } else {
        std::cout << "Gagal membuka file." << std::endl;
        return 0;
    }
}
int FsaveGame()
{
    ofstream file("currency.txt");
    if (file.is_open()) {
        // Change nilai variabel dari file
        file << currency<<endl;
        file << shop_senjata;

        // Menutup file
        file.close();

        std::cout << "Nilai yang ditulis dari file: " << currency << std::endl;
        return 1;
    } else {
        std::cout << "Gagal membuka file." << std::endl;
        return 0;
    }
}
float randomInRange(float min, float max) {
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}
void wander(float& x, float& y, float& vx, float& vy, float minX, float maxX, float minY, float maxY, float& stepSizeX, int& Vmax) {
    
    if(vx<Vmax || vy< Vmax)
    {
        float sudut = randomInRange(0,pi);

        float dx = 0.1* cos(sudut);
        float dy = 0.1* cos(sudut);
        vx+=dx;
        vy+=dy;

        if(y<-50) vy*=-1;
        if(y>300) vy*=-1;
        if(x<0) vx*=-1;
        if(x>700) vx*=-1;

        //printf("Dx: %lf dan Dy: %lf\n",dx,dy);
        x += vx;
        y += vy;
    }
    if(vx>=Vmax || vx<=-Vmax) vx=0;
    if(vy>=Vmax || vy<=-Vmax) vy=0;
    
    
}
void readimage(void *laser[],void *space[],void **enemy,void **player,void **love, CPesawat weapon[],float x,float y,void *powerup[],int weapon_size)
{
    unsigned int size,sizep;
    //hp
    readimagefile("src/image/hp.bmp",0,0,47.4,47.4);
    size = imagesize(0,0,47.4,47.4);
    *love = malloc(size);
    getimage(0,0,47.4,47.4,*love);
    cleardevice();

    //Sol Dae
    readimagefile("src/object/3.bmp",x,y,x+255,y+225);
    size = imagesize(x,y,x+255,y+225);
    *enemy = malloc(size);
    getimage(x,y,x+255,y+225,*enemy);
    cleardevice();
        
    //Player
    readimagefile("src/image/player.bmp",0,0,163,80);
    sizep = imagesize(0,0,163,80);
    *player = malloc(sizep);
    getimage(0,0,163,80,*player);
    cleardevice();
    
    //Weapon Power Up
    readimagefile("src/image/PowerUp/1.jpg",0,0,51,51);
    size = imagesize(0,0,51,51);
    powerup[0] = malloc(size);
    getimage(0,0,51,51,powerup[0]);
    cleardevice();
    
    readimagefile("src/image/PowerUp/2.jpg",0,0,51,51);
    powerup[1] = malloc(size);
    getimage(0,0,51,51,powerup[1]);
    cleardevice();

    readimagefile("src/image/PowerUp/3.jpg",0,0,51,51);
    powerup[2] = malloc(size);
    getimage(0,0,51,51,powerup[2]);
    cleardevice();
    
    //Torpedo,dll.
    weapon[0].FGLaser();
    cout<<"Weapon sizenya adalah "<< weapon_size <<endl;
    for(int i=0;i< weapon_size ;i++) //size weapon tidak perlu dibagi dengan index 0
    {
        weapon[i].FGTorpedo();
        weapon[i].FGMachineGun();
    }
    for (int i=1;i< weapon_size;i++)
    {
        for (int j=0;j<49;j++)
        {
            weapon[i].laser[j] = weapon[0].laser[j];
        }
    }

    
    //Laser + Bg
    auto laser_bg = [](void* laser[],void* space[])
    {
        for (int i=0; i < 206;i++)
        {
            string num = to_string(i);
            string filename = "src/image/laser/laser" + string(5 - num.length(), '0') + num +".bmp";
            const char* str = filename.c_str();
            //readimagefile(str,0,0,800,600);
            readimagefile(str,306,0,496,576);
            int size = imagesize(306,0,496,576);
            laser[i] = malloc(size);
            getimage(306,0,496,576,laser[i]);
    
            /*
            filename = "src/image/laser/laser" + string(5 - num.length(), '0') + num +".bmp";
            const char* str_laser = filename.c_str();
            writeimagefile(str_laser,306,0,496,576);
            */
            cleardevice();

            if (i < 152)
            {
                string num2 = to_string(i);
                string filename2 = "src/image/bg/laser" + string(5 - num2.length(), '0') + num2 +".jpg"; //Harusnya nama filenya space bukan laser
                const char* str2 = filename2.c_str();
                readimagefile(str2,0,0,800,600);
                size = imagesize(0,0,800,600);
                space[i] = malloc(size);
                getimage(0,0,800,600,space[i]);
                cleardevice();
            }
        }
    };
    laser_bg(laser,space);
}   
void readimage_stage1(void *enemy1,void *enemy2)
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

int Game(int flag)
{
    time_t t;
    CPesawat a[10];
    CPesawat p;
    CPesawat peluru[10];
    int gerak[10],cscore=0,score=0,counter=0;
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
        p.s=2;
        int darah = 20;

        while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();
            readimagefile("src/SpaceBG.jpg",0,0,800,600);
            p.FDPlayer();

            for (int i=0;i<10;i++)
            {
                // a[i].FGerak();
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
                            a[j].hxp=-1000;
                            a[j].hyp=-2000;
                            peluru[i].counter=10;
                            score++;
                            cscore++;
                        }
                    }
                }
                for (int i=0;i<10;i++)
                {
                    if(FCPlayer(p,a[i]))
                    {
                        darah--;
                        a[i].xc=0;
                        break;
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
                    }

                }
            
            sprintf(str,"%d",score);
            settextstyle(0,HORIZ_DIR,2);
            setcolor(YELLOW);
            outtextxy(20,580,"Score: ");
            outtextxy(108,580,str);

            page=1-page;
            delay(1);
            if (darah <= 0)
            {
                return 0;
            }
        }
    }
    else if (flag==2)
    {
        p.s=2;
        int darah = 20;
        while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();
            readimagefile("src/SpaceBG.jpg",0,0,800,600);
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
                            darah--;
                            a[j].xc=0;
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
            delay(1);
            if (darah <= 0)
            {
                return 0;
            }
        }
    }
    else if (flag==3)
    {
        //Awal flag 3
        void *enemy,*player,*love,*laser[206],* space[153];
        void *powerup[3];
        CPesawat weapon[10];
        float x=100,y=0,vx=2,vy=1;
        float xp,darah=250;
        float yp;
        page=0;

        setvisualpage(0);
        setactivepage(1);
        readimage(laser,space,&enemy,&player,&love,weapon,x,y,powerup,sizeof (weapon)/sizeof(weapon[0]));

        int i=0,ybg=0,vbg=1,l=0,love_countdown=0,love_flag=0;
        int powerup_flag=-1,powerup_countdown=0;
        float rx=rand()%800,ry=0,powerup_x=rand()%750,powerup_y=0;
        int powerup_label;
        counter=0;

        //Set shop_senjata
        for (int i=0;i<sizeof(weapon)/sizeof(weapon[0]);i++)
        {
            weapon[i].weaponFlag=shop_senjata;
            // cout<<weapon[i].weaponFlag<<endl;
        }
        
        //Hitblox
        float hl[4]; //Hitblox laser Sol Dae
        float hitbox_powerup[4]; //Hitbox Power Up
        
        int hitpoint=667;
        cout<<"Tekan tombol apapun untuk mulai mainnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn";
        int a = 0;
        while (a != 112)
        {
            a=getch();
        } 
        PlaySound(TEXT("src/sfx/BGBoss.wav"),NULL,SND_LOOP | SND_ASYNC);
        while(1)
        {
            setvisualpage(1-page);
            setactivepage(page);
            cleardevice();
    
            //Declaration and condition
            xp=mousex();    yp=mousey();
            x += vx;    y += vy;
            if (x >= 575 || x<0) vx *= -1;
            if (y >= 80 || y<0) vy*=-1;
            if (yp < 400) yp=400;
            
            //Bg, Sol Dae, Player, Enemy
            if(space[l] != NULL) putimage(0,0,space[l],1);
            putimage(xp-81.5,yp,player,0);
            putimage(x,y,enemy,0); //Sol Dae
            if(laser[i] != NULL) if (i>=0 && i<=205) putimage(x+38,y+215,laser[i],1);
            
            //Hitbox Value
            float hp[4] = {xp-81,yp,163,50}; //Hitbox Player
            float hs[4] = {x,255,y,225}; // Hitbox Sol Dae: Kiri, lebar, atas,tinggi
            //Hitbox power up dan weapon terpisah

            //Love Related
            if (love_flag != 1 && love_countdown % 400 == 399) love_flag=1;
            if (love_flag==1)
            {
                ry+=3;
                if(ry>600){
                    ry=0;
                    rx=rand()%750;
                    love_countdown=rand()%50;
                    love_flag=0;
                } 
                float hhp[4] = {rx,ry,47.4,47.4};
                putimage(rx,ry,love,1);
                if(Fcollision3B(hp,hhp))
                {
                    darah+=50;
                    if (darah>=250) darah=250;
                    ry=0;
                    rx=rand()%750;
                    love_flag=0;
                    love_countdown=rand()%50;
                }
            }
            if (powerup_flag == -1 && powerup_countdown % 500 == 499) powerup_flag=rand()%3;
            if (powerup_flag != -1)
            {
                powerup_y+=3;
                
                //Hitbox
                hitbox_powerup[0]=powerup_x;
                hitbox_powerup[1]=powerup_y;
                hitbox_powerup[2]=51;
                hitbox_powerup[3]=51;
                //rectangle(hitbox_powerup[0],hitbox_powerup[1],hitbox_powerup[0]+hitbox_powerup[2],hitbox_powerup[1]+hitbox_powerup[3]);
                if(powerup[powerup_flag] != NULL) putimage(powerup_x,powerup_y,powerup[powerup_flag],1);
                if (powerup_y>600) {
                    powerup_flag=-1;
                    powerup_countdown=rand()%100;
                    powerup_y=0;
                    powerup_x=rand()%750;
                }
            }
            
            //Draw Laser Sol Dae
            if (i>= 41 && i<= 186)
                {
                    hl[0]=x+78;
                    hl[1]=y+215;
                    hl[2]=108;
                    hl[3]=300;

                    //rectangle(hl[0],hl[1],hl[0]+hl[2],hl[1]+hl[3]);
                    if(Fcollision3B(hl,hp))
                    {
                    darah--;
                    }
                }
            else
                {
                hl[0] = 0;
                hl[1] = 0;
                hl[2] = 0;
                hl[3] = 0;
                }
            
            //If Mouse Is Clicked
            if (ismouseclick(WM_LBUTTONDOWN))
            {
                clearmouseclick(WM_LBUTTONDOWN);
                //PlaySound(TEXT("src/sfx/laser.wav"),NULL,SND_ASYNC);
                weapon[counter].counter=0;
                counter++;
            }                
            if(counter>9)counter=0;
            for (int j=0;j<10;j++)
            {
                weapon[j].FDPeluru2(yp);
                weapon[0].FDLaser(xp,yp);
            }
            
            //Collision
            for (int j=0;j<10;j++)
            {
                //Collision between weapon and sol dae
                // rectangle(weapon[j].hx,weapon[j].hy,weapon[j].hx+weapon[j].hw,weapon[j].hy+weapon[j].hl);
                if(Fcollision3A(hs,weapon[j]))
                {
                    weapon[j].counter=10;
                    if(weapon[j].weaponFlag==1) hitpoint-=10;
                    else if (weapon[j].weaponFlag==2) hitpoint -=3;
                    else if (weapon[j].weaponFlag==3) hitpoint -=0.01;
                }
            }
            //Collision between player and power up
                // rectangle(hitbox_powerup[0],hitbox_powerup[1],hitbox_powerup[0]+hitbox_powerup[2],hitbox_powerup[1]+hitbox_powerup[3]);
                // rectangle(hp[0],hp[1],hp[0]+hp[2],hp[1]+hp[3]);
                if(Fcollision3B(hp,hitbox_powerup)) //Urutan parameter dapat menyebabkan error logic
                {    
                    for (int k=0;k<10;k++)
                    {
                        weapon[k].weaponFlag=powerup_flag+1;
                        weapon[k].counter=10;
                    }
                    powerup_flag=-1;
                    powerup_countdown=0;
                    powerup_y=0;
                    powerup_x=rand()%750;
                    hitbox_powerup[0]=0;
                    hitbox_powerup[1]=0;
                    hitbox_powerup[2]=0;
                    hitbox_powerup[3]=0;
                    
                }


            //End of The Scene
            delay(1);
            page=1-page;
            i++;
            l++;
            love_countdown++;
            powerup_countdown++;
            ybg -= vbg;
            //if(ybg < -100) vbg*= -1;
            if(i > 285) i=0;
            if(l > 151) l=0;
            if(hitpoint<=0) break;
            if(darah<=0) break;

            setcolor(RED);
            setfillstyle(SOLID_FILL,RED);
            rectangle(44,35,darah+44,50);
            floodfill(45,36,RED);

            setcolor(RED);
            setfillstyle(SOLID_FILL,RED);
            rectangle(42,566,hitpoint+42,566+13);
            floodfill(44,568,RED);

            setcolor(WHITE);
            setfillstyle(SOLID_FILL,WHITE);
            rectangle(42,33,250+46,52);

            setcolor(WHITE);
            setfillstyle(SOLID_FILL,WHITE);
            rectangle(40,564,667+44,564+15);
        }
        setactivepage(0);
        setvisualpage(0);
        cleardevice();
        // free(enemy);
        // free(player);
        free(laser);
        free(space);
        // free(love);
        // free(powerup);
        PlaySound(NULL,NULL,SND_ASYNC);
        if (hitpoint<=0) 
        {   
            currency+=1000;
            FsaveGame();
            return 1;
        }
        if (darah<=0) return 0;
    }
    else if (flag==4)
    {   //Awal Flag 4
        void *enemy,*player,*love,*laser[206],* space[153];
        void *powerup[3],*enemy1,*enemy2;
        CPesawat weapon[5];
        CPesawat survival_enemy[5];
        int jumlah_enemy=sizeof(survival_enemy)/sizeof(survival_enemy[0]);
        float x=100,y=0,vx=0,vy=0;
        float xp,yp,darah=250;
        float xsoldae=300,ysoldae=50,vxsoldae=1,vysoldae=1;
        float hs[4]; //Hitbox Soldae
        int enemy_killed=0,Vmax=5,flag;
        int flag_spawn=1,flag_spawn_enemy_killed=0; // 1 Jika harus di spawn 
        float minX=100,maxX=550,minY=20,maxY=400,stepSizeX=3,batasVx=2.5,batasVy=2.5;
        vector <int> random;
        string scoreText;
        

        int i=0,ybg=0,vbg=1,l=0,love_countdown=0,love_flag=0;
        int powerup_flag=-1,powerup_countdown=0;
        float rx=rand()%800,ry=0,powerup_x=rand()%750,powerup_y=0;
        int powerup_label;
        float hitbox_player[4];
        int counter1=0; //Counter Bg
        int hitpoint = 200; //Default Hitpoint For Survival Mode
        counter=0;
        page=0;

        setvisualpage(0);
        setactivepage(1);
        readimage(laser,space,&enemy,&player,&love,weapon,x,y,powerup,sizeof (weapon)/sizeof(weapon[0]));

        //Set shop_senjata
        for (int i=0;i<sizeof(weapon)/sizeof(weapon[0]);i++)
        {
            weapon[i].weaponFlag=shop_senjata;
            // cout<<"Weapon flag: "<<weapon[i].weaponFlag<<endl;
        }
        
        //Draw Enemy
        survival_enemy[0].FDSurvival();
        survival_enemy[0].FGMachineGun();
        //survival_enemy[0].FGTorpedo();
        for (int i=1;i<jumlah_enemy;i++)
        {
            survival_enemy[i].enemy1 = survival_enemy[0].enemy1;
            survival_enemy[i].enemy2 = survival_enemy[0].enemy2;
            survival_enemy[i].machinegun = survival_enemy[0].machinegun;
        }

        //Hitblox
        float hl[4]; //Hitblox laser Sol Dae
        float hitbox_powerup[4]; //Hitbox Power Up

        //Auto Lambda Function
        auto spawn_bg = [](void *space[],int& counter) {
                putimage(0,0,space[counter],1);
                counter++;
                if (counter > 151) counter =0;           
                };
        //Initialize X,Y Enemy
        auto spawn_enemy = [](CPesawat survival_enemy[], int jumlah_enemy) 
        {   // lambda function body
            survival_enemy[0].x=rand()%600+10;
            survival_enemy[0].y= 0;
            survival_enemy[0].hwp = 155;
            survival_enemy[0].hlp = 80;
            for (int i=1;i<jumlah_enemy;i++)
            {
                survival_enemy[i].x=survival_enemy[i-1].x+100;
                survival_enemy[i].y=survival_enemy[i-1].y+rand()%50+50;
                survival_enemy[i].vx = 0;
                survival_enemy[i].vy = 0;
                survival_enemy[i].hwp = 155;
                survival_enemy[i].hlp = 80;

                if (survival_enemy[i].x >= 575 || survival_enemy[i].x<0) survival_enemy[i].x=50;
                if (survival_enemy[i].y >= 400 || survival_enemy[i].y<0) survival_enemy[i].y=50;
            }
        };
        auto spawn_enemy2 = [](CPesawat survival_enemy[], int jumlah_enemy) 
        {
            survival_enemy[0].x=rand()%600+10;
            survival_enemy[0].y= 0;
            survival_enemy[0].hwp = 137;
            survival_enemy[0].hlp = 140;
            for (int i=1;i<jumlah_enemy;i++)
            {
                survival_enemy[i].x=survival_enemy[i-1].x+100;
                survival_enemy[i].y=survival_enemy[i-1].y+rand()%50+50;
                survival_enemy[i].vx = 0;
                survival_enemy[i].vy = 0;
                survival_enemy[i].hwp = 137;
                survival_enemy[i].hlp = 140;

                if (survival_enemy[i].x >= 575 || survival_enemy[i].x<0) survival_enemy[i].x=50;
                if (survival_enemy[i].y >= 400 || survival_enemy[i].y<0) survival_enemy[i].y=50;
            }
        };
        auto spawn_enemy4 = [](CPesawat survival_enemy[],int jumlah_enemy, vector <int> &random,float &xsoldae,float& ysoldae,int& hitpoint)
        {            
            random.clear();
            srand(time(NULL));
            for(int i=0;i<jumlah_enemy;i++)
            {
                random.push_back(rand()%2);
                // cout<<random[i]<<endl;
            }
            
            survival_enemy[0].x=rand()%600+10;
            survival_enemy[0].y= 0;
            survival_enemy[0].hwp = 137;
            survival_enemy[0].hlp = 140;
            for (int i=1;i<jumlah_enemy;i++)
            {
                survival_enemy[i].x=survival_enemy[i-1].x+100;
                survival_enemy[i].y=survival_enemy[i-1].y+rand()%50+50;
                survival_enemy[i].vx = 0;
                survival_enemy[i].vy = 0;
                survival_enemy[i].hwp = 137;
                survival_enemy[i].hlp = 140;

                if (survival_enemy[i].x >= 575 || survival_enemy[i].x<0) survival_enemy[i].x=50;
                if (survival_enemy[i].y >= 400 || survival_enemy[i].y<0) survival_enemy[i].y=50;
            }
            hitpoint = 200;
            xsoldae=rand()%600+50;
            ysoldae=0;
        };

        //Powerup
        auto powerANDhp = [] (int& love_flag,int& love_countdown,float& rx,float& ry,void* love, float& darah,float hitbox_player[],int& powerup_countdown,float hitbox_powerup[],int& powerup_flag, float& powerup_x, float& powerup_y,CPesawat weapon[],void* powerup[])         
        {
            //Love related
            if (love_flag != 1 && love_countdown % 400 == 399) love_flag=1;
            if (love_flag==1)
            {
                ry+=3;
                if(ry>600){
                    ry=0;
                    rx=rand()%750;
                    love_countdown=rand()%50;
                    love_flag=0;
                } 
                float hhp[4] = {rx,ry,47.4,47.4};
                putimage(rx,ry,love,1);
                if(Fcollision3B(hitbox_player,hhp))
                {
                    darah+=50;
                    if (darah>=250) darah=250;
                    ry=0;
                    rx=rand()%750;
                    love_flag=0;
                    love_countdown=rand()%50;
                }
            }
            if (powerup_flag == -1 && powerup_countdown % 500 == 499) powerup_flag=rand()%3;
            if (powerup_flag != -1)
            {
                powerup_y+=3;
                
                //Hitbox
                hitbox_powerup[0]=powerup_x;
                hitbox_powerup[1]=powerup_y;
                hitbox_powerup[2]=51;
                hitbox_powerup[3]=51;
                //rectangle(hitbox_powerup[0],hitbox_powerup[1],hitbox_powerup[0]+hitbox_powerup[2],hitbox_powerup[1]+hitbox_powerup[3]);
                if(powerup[powerup_flag] != NULL) putimage(powerup_x,powerup_y,powerup[powerup_flag],1);
                if (powerup_y>600) {
                    powerup_flag=-1;
                    powerup_countdown=rand()%100;
                    powerup_y=0;
                    powerup_x=rand()%750;
                }
            }
            
            //Collision between player and power up
                if(Fcollision3B(hitbox_player,hitbox_powerup)) //Urutan parameter dapat menyebabkan error logic
                {    
                    for (int k=0;k<10;k++)
                    {
                        weapon[k].weaponFlag=powerup_flag+1;
                        weapon[k].counter=10;
                    }
                    powerup_flag=-1;
                    powerup_countdown=0;
                    powerup_y=0;
                    powerup_x=rand()%750;
                    hitbox_powerup[0]=0;
                    hitbox_powerup[1]=0;
                    hitbox_powerup[2]=0;
                    hitbox_powerup[3]=0;
                }

            //End
            love_countdown++;
            powerup_countdown++;
        };


        cout<<"Tekan tombol apapun untuk mulai mainnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn"<<endl;
        int a = 0;

        while (a != 112)    a=getch();
        PlaySound(TEXT("src/sfx/BGBoss.wav"),NULL,SND_LOOP | SND_ASYNC);
        //While Game
        while(1)
        {
            setvisualpage(1-page);
            setactivepage(page);
            cleardevice();
            x = mousex() - 77;    y = mousey();
            if (y < 400 ) y = 400;
            putimage(x,y,player,1);
            if (space[counter1] != NULL) spawn_bg(space,counter1);
            hitbox_player[0] = x;
            hitbox_player[1] = y;
            hitbox_player[2] = 163;
            hitbox_player[3] = 80;
            
    
            //Inside Graphics
            setfillstyle(SOLID_FILL,RED);
            rectangle(42,33,darah+42,50);
            floodfill(43,34,WHITE);
            // Convert the score to a string
            stringstream ss;
            ss<<"Score: "<<enemy_killed;
            scoreText = ss.str(); 
            //Convert string to char*
            char* scoreTextPtr = new char[scoreText.length()+1];
            strcpy(scoreTextPtr,scoreText.c_str());
            outtextxy(42,10,scoreTextPtr);


            //Peluru tembak
            if (ismouseclick(WM_LBUTTONDOWN))
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    weapon[counter].counter=0;
                    counter++;
                }
            if(counter>sizeof(weapon)/sizeof(weapon[0]))counter=0;
            for (int j=0;j<sizeof(weapon)/sizeof(weapon[0]);j++)
                {
                    weapon[j].FDPeluru2(y);
                    weapon[0].FDLaser(x+80,y);
                }    
            
            //Powerup
            powerANDhp(love_flag,love_countdown,rx,ry,love,darah,hitbox_player,powerup_countdown,hitbox_powerup,powerup_flag,powerup_x,powerup_y,weapon,powerup);

            //Khusus Stage 1
            phase1:
            if (enemy_killed<10)
            {
                //Putimage Enemy and enemy weapon
                for(int i=0;i<jumlah_enemy;i++)
                {
                    putimage(survival_enemy[i].x,survival_enemy[i].y,survival_enemy[i].enemy1,1);
                    putimage(survival_enemy[i].xp,survival_enemy[i].yp,survival_enemy[i].machinegun,1);
                }

                //X,Y Settings for Enemy + collision
                for(int i=0;i<jumlah_enemy;i++)
                {
                    // X,Y Changes
                    wander(survival_enemy[i].x,survival_enemy[i].y,survival_enemy[i].vx,survival_enemy[i].vy ,minX , maxX, minY, maxY, stepSizeX, Vmax);                
                    survival_enemy[i].yp +=5;

                    //Hitbox Senjata Enemy
                    survival_enemy[i].hx = survival_enemy[i].xp+10;
                    survival_enemy[i].hy = survival_enemy[i].yp;
                    survival_enemy[i].hw = 20;
                    survival_enemy[i].hl = 40;

                    //Hitbox enemy
                    survival_enemy[i].hxp = survival_enemy[i].x;
                    survival_enemy[i].hyp = survival_enemy[i].y;


                    //X,Y Machine Gun
                    if (survival_enemy[i].yp >= 800)
                    {
                        survival_enemy[i].xp = survival_enemy[i].x;
                        survival_enemy[i].yp = survival_enemy[i].y;
                    }

                    //Musuh -> Player
                    if (Fcollision3C(hitbox_player,survival_enemy[i]))
                    {
                        darah-= 2;
                    }

                    //Player -> Musuh Hitbox
                    for (int j=0;j<sizeof(weapon)/sizeof(weapon[0]);j++)
                    {
                        if (FCPlayer(weapon[j],survival_enemy[i])) 
                        {
                            survival_enemy[i].x=rand();
                            survival_enemy[i].y=rand();
                            survival_enemy[i].hxp=survival_enemy[i].x;
                            survival_enemy[i].hyp=survival_enemy[i].y;
                            weapon[j].counter=10;
                            enemy_killed+=1;
                            break;
                        }
                    }
                    
                }

                //End Statement Condition
                if (enemy_killed==5 && flag_spawn_enemy_killed==false)
                {
                    flag_spawn=true;
                    flag_spawn_enemy_killed=true;
                }
                if (flag_spawn==true) //Spawn Stage 1
                {
                    spawn_enemy(survival_enemy,jumlah_enemy);
                    flag_spawn=false;
                }
                if(enemy_killed==10)
                {
                    flag_spawn_enemy_killed=false;
                    flag_spawn=true;
                }
            } //{} stage 1
  
            phase2:
            if (enemy_killed>=10 && enemy_killed<20)
            {
                //Putimage Enemy and enemy weapon
                for(int i=0;i<jumlah_enemy;i++)
                {
                    putimage(survival_enemy[i].x,survival_enemy[i].y,survival_enemy[i].enemy2,1);
                    putimage(survival_enemy[i].xp,survival_enemy[i].yp,survival_enemy[i].machinegun,1);
                }

                // X,Y Settings for Enemy + collision
                for(int i=0;i<jumlah_enemy;i++)
                {
                    // X,Y Changes
                    wander(survival_enemy[i].x,survival_enemy[i].y,survival_enemy[i].vx,survival_enemy[i].vy ,minX , maxX, minY, maxY, stepSizeX, Vmax);                
                    survival_enemy[i].yp +=5;

                    //Hitbox Senjata Enemy
                    survival_enemy[i].hx = survival_enemy[i].xp+10;
                    survival_enemy[i].hy = survival_enemy[i].yp;
                    survival_enemy[i].hw = 20;
                    survival_enemy[i].hl = 40;

                    //Hitbox enemy for X,Y
                    survival_enemy[i].hxp = survival_enemy[i].x;
                    survival_enemy[i].hyp = survival_enemy[i].y;


                    //X,Y Machine Gun
                    if (survival_enemy[i].yp >= 800)
                    {
                        survival_enemy[i].xp = survival_enemy[i].x;
                        survival_enemy[i].yp = survival_enemy[i].y;
                    }

                    //Musuh -> Player
                    if (Fcollision3C(hitbox_player,survival_enemy[i]))
                    {
                        darah-= 3;
                    }

                    //Player -> Musuh Hitbox
                    for (int j=0;j<sizeof(weapon)/sizeof(weapon[0]);j++)
                    {
                        if (FCPlayer(weapon[j],survival_enemy[i])) 
                        {
                            survival_enemy[i].x=rand();
                            survival_enemy[i].y=rand();
                            survival_enemy[i].hxp=survival_enemy[i].x;
                            survival_enemy[i].hyp=survival_enemy[i].y;
                            weapon[j].counter=10;
                            enemy_killed+=1;
                            break;
                        }
                    }
                    
                }

                //End Statement Condition
                if (enemy_killed==15 && flag_spawn_enemy_killed==false)
                {
                    flag_spawn=true;
                    flag_spawn_enemy_killed=true;
                }
                if (flag_spawn==true) //Spawn Stage 2
                {
                    spawn_enemy2(survival_enemy,jumlah_enemy);
                    flag_spawn=false;
                }

            } //{}Stage 2
  
            phase3:
            if (enemy_killed==20)
            {
                //Putimage Sol dae and Laserp
                putimage(xsoldae,ysoldae,enemy,1);
                if(laser[i] != NULL) if (i>=0 && i<=205) putimage(xsoldae+38,ysoldae+215,laser[i],1);
                // spawn_bg(space,counter1);

                // X,Y Settings for Enemy + collision
                // X,Y Changes
                xsoldae += vxsoldae;
                ysoldae += vysoldae;
                if (xsoldae >= 575 || xsoldae<0) vxsoldae *= -1;
                if (ysoldae >= 80 || ysoldae<0) vysoldae*=-1;
                

                //Player -> Sol Dae
                for (int i=0;i<sizeof(weapon)/sizeof(weapon[0]);i++)
                {
                    if (Fcollision3C(hs,weapon[i]))
                    {
                        cout<<"Hitpoint: "<<hitpoint<<endl;
                        if(weapon[i].weaponFlag==1) hitpoint-=10;
                        else if (weapon[i].weaponFlag==2) hitpoint -=3;
                        else if (weapon[i].weaponFlag==3) hitpoint -=0.01;
                        weapon[i].counter=10;
                        break;
                    }
                }
                
                //Sol Dae -> Player
                if (i>= 41 && i<= 186)
                {
                    hl[0]=xsoldae+78;
                    hl[1]=ysoldae+215;
                    hl[2]=108;
                    hl[3]=300;

                    if(Fcollision3B(hl,hitbox_player))
                    {
                    darah-=1;
                    }
                }
                else
                    {
                    hl[0] = 0;  hl[1] = 0;  hl[2] = 0;  hl[3] = 0;
                    }
                 
                //Hitbox sol dae update for X,Y
                hs[0] = xsoldae;
                hs[1] = ysoldae;
                hs[2] = 255;
                hs[3] = 225;

                //End Statement
                i++;
                if (i > 285) i=0;
                if (hitpoint<=0) 
                {
                    enemy_killed++;
                    flag_spawn_enemy_killed=0;    
                }
            }
  
            phase4:
            if (enemy_killed>20)
            {
                if (jumlah_enemy != 4) jumlah_enemy=4;
                
                //Putimage Enemy and enemy weapon
                if (random.size() != 0)
                {
                     for(int i=0;i<jumlah_enemy;i++)
                    {
                        if (random[i]==0 && random.size()!=0) 
                        {
                            putimage(survival_enemy[i].x,survival_enemy[i].y,survival_enemy[i].enemy1,1);
                            putimage(survival_enemy[i].xp,survival_enemy[i].yp,survival_enemy[i].machinegun,1);
                        }
                        else 
                        {
                            putimage(survival_enemy[i].x,survival_enemy[i].y,survival_enemy[i].enemy2,1);
                            putimage(survival_enemy[i].xp,survival_enemy[i].yp,survival_enemy[i].machinegun,1);
                        }
                    }
                }
                if (hitpoint>0) putimage(xsoldae,ysoldae,enemy,1);
                if(laser[i] != NULL) if (i>=0 && i<=205) putimage(xsoldae+38,ysoldae+215,laser[i],1);

               

                // X,Y Settings for Enemy + collision
                for(int i=0;i<jumlah_enemy;i++)
                {
                    // X,Y Changes
                    wander(survival_enemy[i].x,survival_enemy[i].y,survival_enemy[i].vx,survival_enemy[i].vy ,minX , maxX, minY, maxY, stepSizeX, Vmax);                
                    survival_enemy[i].yp +=5;

                    //Hitbox Senjata Enemy
                    survival_enemy[i].hx = survival_enemy[i].xp+10;
                    survival_enemy[i].hy = survival_enemy[i].yp;
                    survival_enemy[i].hw = 20;
                    survival_enemy[i].hl = 40;

                    //Hitbox enemy for X,Y
                    survival_enemy[i].hxp = survival_enemy[i].x;
                    survival_enemy[i].hyp = survival_enemy[i].y;


                    //X,Y Machine Gun
                    if (survival_enemy[i].yp >= 800)
                    {
                        survival_enemy[i].xp = survival_enemy[i].x;
                        survival_enemy[i].yp = survival_enemy[i].y;
                    }

                    //Musuh -> Player
                    if (Fcollision3C(hitbox_player,survival_enemy[i]))
                    {
                        darah-= 1;
                    }

                    //Player -> Musuh Hitbox
                    for (int j=0;j<sizeof(weapon)/sizeof(weapon[0]);j++)
                    {
                        if (FCPlayer(weapon[j],survival_enemy[i])) 
                        {
                            survival_enemy[i].x=rand();
                            survival_enemy[i].y=rand();
                            survival_enemy[i].hxp=survival_enemy[i].x;
                            survival_enemy[i].hyp=survival_enemy[i].y;
                            weapon[j].counter=10;
                            enemy_killed+=1;
                            break;
                        }
                    }
                    
                }
                xsoldae += vxsoldae;
                ysoldae += vysoldae;
                if (xsoldae >= 575 || xsoldae<0) vxsoldae *= -1;
                if (ysoldae >= 80 || ysoldae<0) vysoldae*=-1;
                //Player -> Sol Dae
                for (int i=0;i<sizeof(weapon)/sizeof(weapon[0]);i++)
                {
                    if (Fcollision3C(hs,weapon[i]))
                    {
                        cout<<"Hitpoint: "<<hitpoint<<endl;
                        if(weapon[i].weaponFlag==1) hitpoint-=10;
                        else if (weapon[i].weaponFlag==2) hitpoint -=3;
                        else if (weapon[i].weaponFlag==3) hitpoint -=0.01;
                        weapon[i].counter=10;
                        break;
                    }
                }
                
                //Sol Dae -> Player
                if (i>= 41 && i<= 186)
                {
                    hl[0]=xsoldae+78;
                    hl[1]=ysoldae+215;
                    hl[2]=108;
                    hl[3]=300;

                    if(Fcollision3B(hl,hitbox_player))
                    {
                    darah-=0.1;
                    }
                }
                else
                    {
                    hl[0] = 0;  hl[1] = 0;  hl[2] = 0;  hl[3] = 0;
                    }
                 
                //Hitbox sol dae update for X,Y
                hs[0] = xsoldae;
                hs[1] = ysoldae;
                hs[2] = 255;
                hs[3] = 225;

                //End Statement Sol Dae
                i++;
                if (i > 285) i=0;
                if (hitpoint<=0) enemy_killed++;


                //End Statement Condition
                if ((enemy_killed-20) %6 ==0)
                {
                    flag_spawn_enemy_killed++;
                }

                if (flag_spawn_enemy_killed%2==0) //Spawn Stage 4
                {
                    spawn_enemy4(survival_enemy,jumlah_enemy,random,xsoldae,ysoldae,hitpoint);
                    flag_spawn_enemy_killed++;
                }
            }
            
            //Outside all stage
            page = 1-page;
            if (darah<=0) return 0;
            delay(1);
        } //While loop {}
    }// Survival{}
    
    return 0;
}//Game {}

void Fshop()
{
    int fe=0;
    flag=1;
    page=0;
    
    while(1)
        {
            setactivepage(page);
            setvisualpage(1-page);
            if (GetAsyncKeyState(49)) flag=1;
            if (GetAsyncKeyState(50)) flag=2;
            if (GetAsyncKeyState(51)) flag=3;
            if (GetAsyncKeyState(13)) fe=1;

            float x=mousex(),y=mousey();

                if (flag==1)
                {
                    readimagefile("src/image/shop/1.jpg",0,0,800,600);
                    settextstyle(0,HORIZ_DIR,4);
                    outtextxy(340,393,"Beli");
                    if(x>340 && x<450 && y>393 && y<430)
                    {
                     cleardevice();
                     readimagefile("src/image/shop/1.jpg",0,0,800,600);
                     settextstyle(1,HORIZ_DIR,4);
                     outtextxy(340,393,"Beli");
                        if (currency>=10000 && ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            currency-=10000;
                            shop_senjata=1;
                            FsaveGame();
                            cout<<"Berhasil Membeli dan mengganti senjata"<<endl;
                        }
                    }
                    //rectangle(340,393,450,430);
                    delay(1);
                }
                
                else if (flag==2)
                {
                    readimagefile("src/image/shop/2.jpg",0,0,800,600);
                    settextstyle(0,HORIZ_DIR,4);
                    outtextxy(340,393,"Beli");
                    if(x>340 && x<450 && y>393 && y<430)
                    {
                     cleardevice();
                     readimagefile("src/image/shop/2.jpg",0,0,800,600);
                     settextstyle(1,HORIZ_DIR,4);
                     outtextxy(340,393,"Beli");
                        if (currency>=50000 && ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            currency-=50000;
                            shop_senjata=2;
                            FsaveGame();
                            cout<<"Berhasil Membeli dan mengganti senjata"<<endl;
                        }
                    }
                    //rectangle(340,393,450,430);
                    delay(1);
                }
                
                else if (flag==3)
                {
                    readimagefile("src/image/shop/3.jpg",0,0,800,600);
                    settextstyle(0,HORIZ_DIR,4);
                    outtextxy(340,393,"Beli");
                    if(x>340 && x<450 && y>393 && y<430)
                    {
                     cleardevice();
                     readimagefile("src/image/shop/3.jpg",0,0,800,600);
                     settextstyle(1,HORIZ_DIR,4);
                     outtextxy(340,393,"Beli");
                        if (currency>=200000 && ismouseclick(WM_LBUTTONDOWN))
                        {
                            clearmouseclick(WM_LBUTTONDOWN);
                            currency-=200000;
                            shop_senjata=3;
                            FsaveGame();
                            cout<<"Berhasil Membeli dan mengganti senjata"<<endl;
                        }
                    }
                    //rectangle(340,393,450,430);
                    delay(1);
                }

                //Tekan esc untuk keluar
                if (GetAsyncKeyState(27)) break;
                page = 1-page;
        }
}
int main()
{
    srand(time(0));
    int flag=0,key;
    CPesawat p;
    //char str[10000]="Terdapat sebuah planet yang telah dikuasai oleh para alien jahat yang ingin menguasai seluruh galaksi. Para alien tersebut telah melakukan serangan ke berbagai planet yang ada di sekitarnya, dan mereka berencana untuk menyerang planet yang berada di pusat galaksi. Untuk menghentikan para alien jahat ini, diperlukan kehadiran prajurit luar angkasa yang handal dan berani. Prajurit luar angkasa yang dipilih untuk misi ini adalah Kapten John. Ia telah memiliki pengalaman bertempur yang cukup banyak, dan telah melalui berbagai pelatihan dan simulasi pertempuran melawan alien. Kapten John bersama timnya diberi misi untuk mencegah para alien jahat ini menyerang planet pusat galaksi. Misi Kapten John dimulai dengan menyusup ke dalam kapal musuh dan menghancurkan pusat kendali kapal. Setelah berhasil menghancurkan pusat kendali, Kapten John dan timnya berhasil mendarat di planet yang dijadikan markas oleh para alien jahat.";
    initwindow(800,600,"Alien Space");
    
    FreadCurrency();
    //
    // Game(2);
    // return 0;
    //Fshop();
    //
    mainmenu:
        key=Fmainmenu();
        if (key==1) goto story;
        else if (key==2) goto tutorial;
        else if (key==3) goto shop;
        else if (key==4) goto saveGame;
    tutorial:
        Ftutorial();
        goto mainmenu;
    story:
        Fstory2();
    level:
       flag=Flevel();
       FLoading();
    game:
        Game(flag);
        fflush(stdin);
        setactivepage(1);
        setvisualpage(1);
        readimagefile("src/gover/GOver.jpg",0,0,800,600);
        PlaySound(TEXT("src/sfx/SFXGover.wav"),NULL,SND_ASYNC);
        delay(6000);
        flag=Freturn();
        if (flag==1) goto mainmenu;
        else return 0;
    shop:
        FLoading();
        Fshop();
        goto mainmenu;


    saveGame:
        FsaveGame();
        goto mainmenu;
    esc:
        return 0;
}