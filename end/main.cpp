#include <stdio.h>
#include <graphics.h>
#include <Windows.h>
#include <math.h>
#include <time.h>
#include<stdlib.h>
#include <mmsystem.h>
#define PI      3.1415926548
#pragma comment(lib,"winmm.lib")
/*
    1.把程序里面的元素用数据类型表示
    //两个坐标桌面窗口的坐标，图片的坐标
    单个烟花的大小240*240
    2.初始化
*/


#define NUM 13


//烟花
struct Fire
{
    int x, y;//烟花在窗口里面爆炸的坐标
    int r;//烟花爆炸的当前半径
    int max_r;//烟花爆炸最大半径
    int cen_x, cen_y;//图片坐标系中的中心位置
    int xy[240][240];//240*240的像素数组，图片的像素点保存在这里
    bool show;//烟花是否开始爆炸 表示可不可以爆炸
    bool draw;//开始绘制 表示是否爆炸
    DWORD t1, t2, dt;//单位时间 帧数 爆炸的速度
    //unsigned long = DWORD 4字节

}fire[NUM];


struct Jet
{
    int x, y;  //烟花弹的坐标 当前的坐标  
    int hx, hy;//烟花弹最高的坐标
    bool shoot;//用一个数组来存放烟花弹的数据
    //烟花弹的状态 是否发射的状态 true false
    unsigned long t1, t2, dt;      //速度 dt = t2 - t2
    IMAGE img[2];//两张图片 一明一亮 img[0]表示暗色 img[1]亮色
    //模拟一闪一闪的效果
    byte n : 1;//typedef unsigned char byte;
    //C语言结构体 位段  一个位 1/8字节 假设n++（01010010100）要么是零 要么是一
    //img[n++]//一闪一闪
}jet[NUM];


void load()
{
    mciSendString( "open ./bk2.mp3 alias music", 0, 0, 0);
    mciSendString( "play music", 0, 0, 0);
    srand(time(NULL));
    IMAGE bigimg;//一整张图片加载进来
    loadimage(&bigimg,  "./shoot.jpg", 200, 50);
    //把shoot.jpg保存在bigimg
    SetWorkingImage(&bigimg);//十个烟花弹的图片
    for (int i = 0; i < NUM; i++)
    {
        int n =  rand() % 5;
        getimage(&jet[i].img[0],n*20,0,20,50);//随机将前面的5张的任意一张图片保存到。。
        getimage(&jet[i].img[1],(n + 5)*20,0,20,50);
    }
    SetWorkingImage(NULL);//把工作区域回到窗口

    IMAGE flower, stepimg;
 
    loadimage(&flower,  "./flower.jpg", 3120, 240);//3120 240（高度） 13张
    //工作区 默认工作区是窗口
    //flower.jpg这个图片中有13朵烟花

    //getimage(&stepimg,);
    for (int i = 0; i < NUM; i++)
    {
        SetWorkingImage(&flower);//在flower图片上，裁图片

        getimage(&stepimg, i * 240, 0, 240, 240);//裁剪第一朵烟花 获取
        SetWorkingImage(&stepimg);//小图片搞事情
        for (int a = 0; a < 240; a++)
        {
            for (int b = 0; b < 240; b++)
            {
                fire[i].xy[a][b] = getpixel(a, b);//获取小图片上的每一个像素，存放在xy数组


            }
        }
    }

    SetWorkingImage(NULL);//工作区回到窗口
    //return 0;

}



//初始化
void init(int i)
{
    //初始化烟花弹的数据
    jet[i].x = 0;
    jet[i].y = 0;
    jet[i].hx = 0;
    jet[i].hy = 0;
    jet[i].t1 = GetTickCount();
    jet[i].t2 = 0;
    jet[i].dt = rand()%10 + 1;//单位时间 1ms - 10ms
    jet[i].n = 0;
    jet[i].shoot = false;
    
    fire[i].x = rand() % 1200;
    fire[i].y = rand() % 800;
    fire[i].r = 0;
    fire[i].max_r = 120;//图片的宽度240 240  
    fire[i].cen_x = 120;
    fire[i].cen_y = 120;
    //fire[i].xy[240][240]; 
    fire[i].show = false; //***********
    fire[i].draw = false;
    fire[i].t1 = GetTickCount();//获取系统的时间
    //fire[i].t2;
    fire[i].dt = 5;//爆炸的间隔 5毫秒
    fire[i].xy[240][240];
 
}



//最核心的地方
void firedraw(DWORD* pmem)//显存指针
{
    //逻辑
    for (int i = 0; i < NUM; i++)
    {
        fire[i].t2 = GetTickCount();//GetTickCount:获取系统的时间
        //“detat = t2 - t1”
        if (fire[i].t2 - fire[i].t1 >= fire[i].dt && fire[i].show == true)
        {
            //r不能超过max_r
            if (fire[i].r < fire[i].max_r)
            {
                fire[i].r++;//半径不断变大
                fire[i].draw = true;//可以绘制
            }
            //万一超过 爆炸结束
            if (fire[i].r >= fire[i].max_r - 1)
            {
                fire[i].draw = false;
                init(i);//爆炸结束给内存初始化，等待下一次爆炸
            }
            //重置时间 否则永远t2-t1不为5（只有一次为5）
            fire[i].t1 = fire[i].t2;
        }
        //如果是可以绘制的状态
        if (fire[i].draw = true)
        {
            // 绘制不是贴图 而是输出像素点
                // 像素点 就是颜色（颜色：32位的数据）
                // 00000000 00000000 00000000 00000000
                // a透明度  red      green    blue
            for (double a = 0; a <= 6.28; a += 0.01)
            {
                //x1 y1 图片坐标系的坐标
                int x1 = fire[i].cen_x + fire[i].r * cos(a);
                int y1 = fire[i].cen_y - fire[i].r * sin(a);
                //编程坐标系 与数学不一样
                //以半径r得到圆弧上的每一个x和y
                if (x1 > 0 && x1 < 240 && y1 > 0 && y1 < 240)
                {
                    //分开32位数据  颜色 00000000 00000000 00000000

                    //点不能超出图片的该范围以外
                    int b = fire[i].xy[x1][y1] & 0xff;//blue
                    int g = (fire[i].xy[x1][y1] >> 8) & 0xff;//green
                    int r = (fire[i].xy[x1][y1] >> 16);//red
                    // 像素转移 小图片->工作区
                    int xx = fire[i].x + fire[i].r * cos(a);
                    int yy = fire[i].y - fire[i].r * sin(a);
                    //xx yy 窗口坐标系的坐标

                    if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
                    {
                        //如果这个点颜色太深（黑） 就不输出
                        pmem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
                        // 移像素点  图片 =》 窗口
                    }
                }
            }

            //628个圆弧上的点
            fire[i].draw = false;
        }


    }

}





//选择 出现 一点时间间隔
void choise(DWORD tt1)

{
    DWORD tt2 = GetTickCount();
    if (tt2 - tt1 > 100)//保证时间间隔
    {
        int i = rand() % NUM;

        if ( jet[i].shoot == false && fire[i].show == false)//未发射状态 空闲
        {
            //数据重新规划一下
            jet[i].x = rand()% (1200 - 20);
            jet[i].y = rand()% (100 + 600);
            jet[i].hx = jet[i].x;
            jet[i].hy = rand()% 400;
            jet[i].shoot = true;
            putimage(jet[i].x, jet[i].y,&jet[i].img[jet[i].n], SRCINVERT);


        }
        tt1 = tt2;
    }
}
 
int saysomenthing()
{
    setcolor(YELLOW);

    for (int i = 0; i < 50; i++)
    {
        int x = 600 + int(180 * sin(PI * 2 * i / 60));
        int y = 200 + int(180 * cos(PI * 2 * i / 60));
        cleardevice();
        settextstyle(i, 0,"楷体");
        outtextxy(x - 80, y, "xuzhiqian");
        outtextxy(x - 10, y + 100, "世界和平！！！");
        Sleep(50);
    }
    getchar();
    return 0;
}

void shoot()
{
    for (int i = 0;i < NUM;i++)
    {
        jet[i].t2 = GetTickCount();
        if (jet[i].t2 - jet[i].t1 > jet[i].dt && jet[i].shoot == true)

        {
            putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n],SRCINVERT);//n++
            if (jet[i].y > jet[i].hy)
            {
                jet[i].n++;//一闪一闪
                jet[i].y -= 5;//上升效果
            }
            
            putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
            if (jet[i].y <= jet[i].hy)//已经到达最高的高度
            {
                putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n],SRCINVERT);
                //把它的坐标传递个烟花 
               
                fire[i].x = jet[i].hx;
                fire[i].y = jet[i].hy;
                fire[i].show = true;
                //它的使命完成
                jet[i].shoot = false;
            }
            jet[i].t1 = jet[i].t2;
        }
    }
}



int main()
{
    initgraph(1200, 800);
   
    DWORD tt1 = GetTickCount();
    DWORD* pmem = GetImageBuffer();//获取显存指针
      
    load();
     
 
    for (int i = 0; i < NUM; i++)
    {
        init(i);
    }
    saysomenthing();
    BeginBatchDraw();
    
    while (1)
    {
        Sleep(10);//擦除时间
        for (int c = 0;c < 1000;c++)
        {
            for (int r = 0; r < 2; r++)//保证每次擦除两千的像素点
            {
                //随机找两千个窗口的点
                int px1 = rand() % 1200;
                int py1 = rand() % 800;
                if (py1 < 799)//防止越界
                {
                    pmem[py1 * 1200 + px1] = pmem[py1*1200 + px1 + 1] = BLACK;
                }
            }
        }

        choise(tt1);
        shoot();
        firedraw(pmem);
        FlushBatchDraw();
    }

     getchar();
    return 0;
}