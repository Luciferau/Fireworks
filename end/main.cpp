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
    1.�ѳ��������Ԫ�����������ͱ�ʾ
    //�����������洰�ڵ����꣬ͼƬ������
    �����̻��Ĵ�С240*240
    2.��ʼ��
*/


#define NUM 13


//�̻�
struct Fire
{
    int x, y;//�̻��ڴ������汬ը������
    int r;//�̻���ը�ĵ�ǰ�뾶
    int max_r;//�̻���ը���뾶
    int cen_x, cen_y;//ͼƬ����ϵ�е�����λ��
    int xy[240][240];//240*240���������飬ͼƬ�����ص㱣��������
    bool show;//�̻��Ƿ�ʼ��ը ��ʾ�ɲ����Ա�ը
    bool draw;//��ʼ���� ��ʾ�Ƿ�ը
    DWORD t1, t2, dt;//��λʱ�� ֡�� ��ը���ٶ�
    //unsigned long = DWORD 4�ֽ�

}fire[NUM];


struct Jet
{
    int x, y;  //�̻��������� ��ǰ������  
    int hx, hy;//�̻�����ߵ�����
    bool shoot;//��һ������������̻���������
    //�̻�����״̬ �Ƿ����״̬ true false
    unsigned long t1, t2, dt;      //�ٶ� dt = t2 - t2
    IMAGE img[2];//����ͼƬ һ��һ�� img[0]��ʾ��ɫ img[1]��ɫ
    //ģ��һ��һ����Ч��
    byte n : 1;//typedef unsigned char byte;
    //C���Խṹ�� λ��  һ��λ 1/8�ֽ� ����n++��01010010100��Ҫô���� Ҫô��һ
    //img[n++]//һ��һ��
}jet[NUM];


void load()
{
    mciSendString( "open ./bk2.mp3 alias music", 0, 0, 0);
    mciSendString( "play music", 0, 0, 0);
    srand(time(NULL));
    IMAGE bigimg;//һ����ͼƬ���ؽ���
    loadimage(&bigimg,  "./shoot.jpg", 200, 50);
    //��shoot.jpg������bigimg
    SetWorkingImage(&bigimg);//ʮ���̻�����ͼƬ
    for (int i = 0; i < NUM; i++)
    {
        int n =  rand() % 5;
        getimage(&jet[i].img[0],n*20,0,20,50);//�����ǰ���5�ŵ�����һ��ͼƬ���浽����
        getimage(&jet[i].img[1],(n + 5)*20,0,20,50);
    }
    SetWorkingImage(NULL);//�ѹ�������ص�����

    IMAGE flower, stepimg;
 
    loadimage(&flower,  "./flower.jpg", 3120, 240);//3120 240���߶ȣ� 13��
    //������ Ĭ�Ϲ������Ǵ���
    //flower.jpg���ͼƬ����13���̻�

    //getimage(&stepimg,);
    for (int i = 0; i < NUM; i++)
    {
        SetWorkingImage(&flower);//��flowerͼƬ�ϣ���ͼƬ

        getimage(&stepimg, i * 240, 0, 240, 240);//�ü���һ���̻� ��ȡ
        SetWorkingImage(&stepimg);//СͼƬ������
        for (int a = 0; a < 240; a++)
        {
            for (int b = 0; b < 240; b++)
            {
                fire[i].xy[a][b] = getpixel(a, b);//��ȡСͼƬ�ϵ�ÿһ�����أ������xy����


            }
        }
    }

    SetWorkingImage(NULL);//�������ص�����
    //return 0;

}



//��ʼ��
void init(int i)
{
    //��ʼ���̻���������
    jet[i].x = 0;
    jet[i].y = 0;
    jet[i].hx = 0;
    jet[i].hy = 0;
    jet[i].t1 = GetTickCount();
    jet[i].t2 = 0;
    jet[i].dt = rand()%10 + 1;//��λʱ�� 1ms - 10ms
    jet[i].n = 0;
    jet[i].shoot = false;
    
    fire[i].x = rand() % 1200;
    fire[i].y = rand() % 800;
    fire[i].r = 0;
    fire[i].max_r = 120;//ͼƬ�Ŀ��240 240  
    fire[i].cen_x = 120;
    fire[i].cen_y = 120;
    //fire[i].xy[240][240]; 
    fire[i].show = false; //***********
    fire[i].draw = false;
    fire[i].t1 = GetTickCount();//��ȡϵͳ��ʱ��
    //fire[i].t2;
    fire[i].dt = 5;//��ը�ļ�� 5����
    fire[i].xy[240][240];
 
}



//����ĵĵط�
void firedraw(DWORD* pmem)//�Դ�ָ��
{
    //�߼�
    for (int i = 0; i < NUM; i++)
    {
        fire[i].t2 = GetTickCount();//GetTickCount:��ȡϵͳ��ʱ��
        //��detat = t2 - t1��
        if (fire[i].t2 - fire[i].t1 >= fire[i].dt && fire[i].show == true)
        {
            //r���ܳ���max_r
            if (fire[i].r < fire[i].max_r)
            {
                fire[i].r++;//�뾶���ϱ��
                fire[i].draw = true;//���Ի���
            }
            //��һ���� ��ը����
            if (fire[i].r >= fire[i].max_r - 1)
            {
                fire[i].draw = false;
                init(i);//��ը�������ڴ��ʼ�����ȴ���һ�α�ը
            }
            //����ʱ�� ������Զt2-t1��Ϊ5��ֻ��һ��Ϊ5��
            fire[i].t1 = fire[i].t2;
        }
        //����ǿ��Ի��Ƶ�״̬
        if (fire[i].draw = true)
        {
            // ���Ʋ�����ͼ ����������ص�
                // ���ص� ������ɫ����ɫ��32λ�����ݣ�
                // 00000000 00000000 00000000 00000000
                // a͸����  red      green    blue
            for (double a = 0; a <= 6.28; a += 0.01)
            {
                //x1 y1 ͼƬ����ϵ������
                int x1 = fire[i].cen_x + fire[i].r * cos(a);
                int y1 = fire[i].cen_y - fire[i].r * sin(a);
                //�������ϵ ����ѧ��һ��
                //�԰뾶r�õ�Բ���ϵ�ÿһ��x��y
                if (x1 > 0 && x1 < 240 && y1 > 0 && y1 < 240)
                {
                    //�ֿ�32λ����  ��ɫ 00000000 00000000 00000000

                    //�㲻�ܳ���ͼƬ�ĸ÷�Χ����
                    int b = fire[i].xy[x1][y1] & 0xff;//blue
                    int g = (fire[i].xy[x1][y1] >> 8) & 0xff;//green
                    int r = (fire[i].xy[x1][y1] >> 16);//red
                    // ����ת�� СͼƬ->������
                    int xx = fire[i].x + fire[i].r * cos(a);
                    int yy = fire[i].y - fire[i].r * sin(a);
                    //xx yy ��������ϵ������

                    if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
                    {
                        //����������ɫ̫��ڣ� �Ͳ����
                        pmem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
                        // �����ص�  ͼƬ =�� ����
                    }
                }
            }

            //628��Բ���ϵĵ�
            fire[i].draw = false;
        }


    }

}





//ѡ�� ���� һ��ʱ����
void choise(DWORD tt1)

{
    DWORD tt2 = GetTickCount();
    if (tt2 - tt1 > 100)//��֤ʱ����
    {
        int i = rand() % NUM;

        if ( jet[i].shoot == false && fire[i].show == false)//δ����״̬ ����
        {
            //�������¹滮һ��
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
        settextstyle(i, 0,"����");
        outtextxy(x - 80, y, "xuzhiqian");
        outtextxy(x - 10, y + 100, "�����ƽ������");
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
                jet[i].n++;//һ��һ��
                jet[i].y -= 5;//����Ч��
            }
            
            putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
            if (jet[i].y <= jet[i].hy)//�Ѿ�������ߵĸ߶�
            {
                putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n],SRCINVERT);
                //���������괫�ݸ��̻� 
               
                fire[i].x = jet[i].hx;
                fire[i].y = jet[i].hy;
                fire[i].show = true;
                //����ʹ�����
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
    DWORD* pmem = GetImageBuffer();//��ȡ�Դ�ָ��
      
    load();
     
 
    for (int i = 0; i < NUM; i++)
    {
        init(i);
    }
    saysomenthing();
    BeginBatchDraw();
    
    while (1)
    {
        Sleep(10);//����ʱ��
        for (int c = 0;c < 1000;c++)
        {
            for (int r = 0; r < 2; r++)//��֤ÿ�β�����ǧ�����ص�
            {
                //�������ǧ�����ڵĵ�
                int px1 = rand() % 1200;
                int py1 = rand() % 800;
                if (py1 < 799)//��ֹԽ��
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