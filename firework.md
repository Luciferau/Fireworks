 #    搭建开发环境与配置素材

**由于编写代码需要显示图片,所以我们需要用到`<graphics.h>`**

下载地址：[https://easyx.cn/](https://easyx.cn/)

## 安装easyX

1.![image-20220204204759085](F:\markdowm 学习\firework_learning_new\picture\image-20220204204759085.png)

**单击下一步**

2.

![image-20220204204902018](F:\markdowm 学习\firework_learning_new\picture\image-20220204204902018.png)

**点击安装 ** ~~保险起见你可以都点~~

~~我这里已经安装好了 就不点了~~

3.

配置素材

素材在文尾已经打包好，放到fire目录里即可



![image-20220204205215259](F:\markdowm 学习\firework_learning_new\picture\image-20220204205215259.png)

4.

​	打开vs，我这里用的是vs2022，新建一个空项目。。

​	在解决方案管理器中，添加一个源文件

5.

我们先测试一下环境

~~~c++
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
int main()
{
initgraph(700,700);//初始化窗口 也就是设定我们的程序框大小
setcolor(RED);//设置绘图的颜色
circle(200,200,100);//圆心（200,200），半径100
rectangle(200,200,400,400);//绘制一个矩形
line(200,200,500,500);//画线
getch();
closegraph;//关闭绘图程序界面
}
~~~

# 开始开发

***

## 定义烟花、烟花弹的结构体



删掉之前的代码，写的空的main函数，写好烟花与烟花弹的结构体

~~~c++
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include<string>
#include <mmsystem.h>
#define NUM 13 //烟花弹的个数
#pragma comment ( lib, "Winmm.lib" )

// 烟花结构
struct Fire
{
	int r;					// 当前爆炸半径
	int max_r;				// 爆炸中心距离边缘最大半径
	int x, y;				// 爆炸中心在窗口的坐标
	int cent2LeftTopX, cent2LeftTopY;		// 爆炸中心相对图片左上角的坐标
	int width, height;		// 图片的宽高
	int pix[240][240];		// 储存图片像素点

	bool show;				// 是否绽放
	bool draw;				// 开始输出像素点
	DWORD t1, t2, dt;		// 绽放速度 dt为时间差
}fires[NUM];


// 烟花弹结构
struct Bullet
{
	int x, y;				// 烟花弹的当前坐标
	int topX, topY;				// 最高点坐标------将赋值给 FIRE 里面的 x, y
	int height;				// 烟花高度
	bool shoot;				// 是否可以发射

	DWORD t1, t2, dt;		// 发射速度
	IMAGE img[2];			// 储存烟花弹一亮一暗两张图片
    byte n : 1;
	//unsigned char n : 1;	// 图片下标 n++ 同种烟花有2个不同的颜色 需要1个位来进行操作 ++ 永远等于 0 或 1 C语言结构体 位段
}bullets[NUM];


int main(void)
{
    //数据初始化
    
	return 0;
}
~~~

### 个别类型讲解类型

#### bool

C语言并没有彻底从语法上支持“真”和“假”，只是用 0 和非 0 来代表。这点在 [C++](http://c.biancheng.net/cplus/) 中得到了改善，C++ 新增了 **bool 类型（布尔类型）**，它一般占用 1 个字节长度。bool 类型只有两个取值，true 和 false：true 表示“真”，false 表示“假”。

bool 是类型名字，也是 C++ 中的关键字，它的用法和 int、char、long 是一样的，请看下面的例子：

```c++
#include <iostream>
using namespace std;
int main(){
    int a, b;
    bool flag;  //定义布尔变量
    cin>>a>>b;
    flag = a > b;
    cout<<"flag = "<<flag<<endl;
    return 0
}
```

10 20
flag = 0

***但在 C++ 中使用 cout 输出 bool 变量的值时还是用数字 1 和 0 表示，而不是 true 或 false。[Java](http://c.biancheng.net/java/)、[PHP](http://c.biancheng.net/php/)、[JavaScript](http://c.biancheng.net/js/) 等也都支持bool类型，但输出结果为 true 或 false，~~我武断地认为这样更科学。~~***



你也可以使用 true 或 false 显式地对 bool 变量赋值，例如：

~~~c++
#include <iostream>
using namespace std;

int main(){
    bool flag = true;
    if(flag){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    flag = false;
    if(flag){
        cout<<"true"<<endl;
    }else{
        cout<<"false"<<endl;
    }

    return 0;
}
~~~

run result

true
false

`注意，true 和 false 是 C++ 中的关键字，true 表示“真”，false 表示“假”。`

#### DWORD 类型

让我们看一看DWORD类型的定义(WINDEF.H)

```c++
typedef unsigned long       DWORD;//      DWORD=unsigned long(完全等同)
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
```

我们可以看到DWORD的原型为unsigned long;

说明它是一种无符号long

#### IMAGE 类型

image在easyX.h中被定义为一个c++类；

其类中有多个成员，这里我将他们列举出来

```c++
// 定义图像对象
class IMAGE
{
public:
	int getwidth() const;	// 获取对象的宽度
	int getheight() const;	// 获取对象的高度

private:
	int width, height;		// 对象的宽高
	HBITMAP m_hBmp;
	HDC m_hMemDC;
	float m_data[6];
	COLORREF	m_LineColor;		// 当前线条颜色
	COLORREF	m_FillColor;		// 当前填充颜色
	COLORREF	m_TextColor;		// 当前文字颜色
	COLORREF	m_BkColor;			// 当前背景颜色
	DWORD*		m_pBuffer;			// 绘图区的内存

	LINESTYLE	m_LineStyle;		// 画线样式
	FILLSTYLE	m_FillStyle;		// 填充样式

	virtual void SetDefault();						// 设置为默认状态

public:
	IMAGE(int _width = 0, int _height = 0);			// 创建图像
	IMAGE(const IMAGE &img);						// 拷贝构造函数
	IMAGE& operator = (const IMAGE &img);			// 赋值运算符重载函数
	virtual ~IMAGE();
	virtual void Resize(int _width, int _height);	// 调整尺寸
};
```

#### byte类型

我先给你们列出byte类型的定义(rpcndr.h)

```c++
typedef unsigned char byte;
```

byte是一个无符号的char类型，但是一个char有个1字节，1个字节有8个位

如果我给出以下定义

`byte n :1;`

**如果我进行n++的操作，那么n不是等于0就是等于1**

因为我们只申请了一个位

位中是按照二进制进行储存的，0101010101010，我们可以把他用来当做`image img[2]`的下标

这样便提升了程序的性能





## 初始化

我们先初始化一个窗口,定义一个init函数

我们先进行函数声明，~~防止下面会报错，加在项目最前~~

```c++
void init()；//整个项目的初始化
void initFire(int i)；// 初始化指定的烟花和烟花弹
void loadFireImages()；//// 加载烟花和烟花弹的图片
    
```

#### 啥是工作区？？

一般控制台程序的工作区就是窗口，而SetWorkingImage函数可以设置工作区到窗口，进行对图片的操作



#### mciSendString()函数

`mciSendString("play fire/ring.mp3 repeat", 0, 0, 0);	//send(发送)	string（字符串)`

**mciSendSrting()函数只支持打开MP3音频文件，若需要打开wav音频文件可以使用PlaySound函数**

`mciSendString(L"open ./fire/bk1.mp3 alias music", 0, 0, 0);	//send(发送)	string（字符串)`

*当使用mciSendSrting（）函数时，一定要确定好文件的位置，文件夹名用/号隔开，向我这里的文件就在当前文件的根目录下，音乐的全名便是叫做bk1.MP3。bk1.MP3 alias music的意思是给bk1取一个叫做music的别名*

**mciSendString(L"play music", 0, 0, 0);**的意思是播放别名为music的音乐。后面三个参0，0，0则表示默认

//0,0,0 音乐播放器时：播放设备，快进设备 快退 暂停      

mciSendString(L"close music");//关闭音乐

***







###   实现初始化的三个函数

```c++
// 初始化指定的烟花和烟花弹
void initFire(int i)
{
	// 分别为：烟花中心到图片边缘的最远距离、烟花中心到图片左上角的距离 (x、y)  
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	/**** 初始化烟花 *****/
	fires[i].x = 0;				// 烟花中心坐标
	fires[i].y = 0;
	fires[i].width = 240;				// 图片宽
	fires[i].height = 240;				// 图片高
	fires[i].max_r = r[i];				// 最大半径
	fires[i].cent2LeftTopX = x[i];				// 中心距左上角距离x
	fires[i].cent2LeftTopY = y[i];				// 中心距左上角距离y
	fires[i].show = false;			// 是否绽放
	fires[i].dt = 5;				// 绽放时间间隔
	fires[i].t1 = timeGetTime();//获取系统时间（这个程序运行的时间）
	fires[i].r = 0;				// 从 0 开始绽放
	fires[i].draw = false;//是否画

	/**** 初始化烟花弹 *****/
	//timeGetTime 该时间为从系统开启算起所经过的时间,单位：毫秒
	bullets[i].t1 = timeGetTime();//获取该程序运行到此处所用的时间
	bullets[i].dt = rand() % 10;		// 发射速度时间间隔
	bullets[i].n = 0;				// 烟花弹闪烁图片下标
	bullets[i].shoot = false;			// 是否发射 不能一开始就发射 要先干点啥
}

```

```c++
// 加载图片
void loadFireImages()
{
	/**** 储存烟花的像素点颜色 ****/
	IMAGE fm, gm;
	loadimage(&fm, "fire/flower.jpg");

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm, i * 240, 0, 240, 240);

		SetWorkingImage(&gm);
		for (int a = 0; a < 240; a++)
			for (int b = 0; b < 240; b++)
				fires[i].pix[a][b] = getpixel(a, b);
	}

	/**** 加载烟花弹 ************/
	IMAGE sm;
	loadimage(&sm, "fire/shoot.jpg");

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&sm);
		int n = rand() % 5; //0..4

		getimage(&bullets[i].img[0], n * 20, 0, 20, 50);			// 暗
		getimage(&bullets[i].img[1], (n + 5) * 20, 0, 20, 50);		// 亮
	}

	//设置绘图设备为默认绘图窗口，就是当前游戏窗口
	SetWorkingImage();		// 设置回绘图窗口
}
```

setworkingimage裁剪图片



![image-20220206152537721](F:\markdowm 学习\firework_learning_new\picture\image-20220206152537721.png)



![image-20220206152452345](F:\markdowm 学习\firework_learning_new\picture\image-20220206152452345.png)

```c++
void init()
{
    //创建一个图形化窗口
	initgraph(1200, 800);
    
    // 播放背景音乐
	mciSendString("play fire/ring.mp3 repeat", 0, 0, 0);//如果这里报错可以改变字符集(改成多集字符集 （项目属性里面改）)，或者加一个L
    
    //初始化烟花
    for (int i = 0; i < NUM; i++) 
    {	// 初始化每一个烟花和烟花弹
		initFire(i);
	}
    loadFireImages();
    pMem = GetImageBuffer();		// 获取窗口显存指针
    
    
	// 打开音效并设置别名
	char cmd[128];
	for (int i = 0; i < 13; i++) 
    {
        //设置烟花爆照、发射时的声音 设置别名 不然只会放第一次
		sprintf_s(cmd, sizeof(cmd), "open fire/shoot.mp3 alias s%d", i);
		mciSendString(cmd, 0, 0, 0); // 打开13次

		sprintf_s(cmd, sizeof(cmd), "open fire/bomb.wav alias f%d", i);
		mciSendString(cmd, 0, 0, 0); // 打开13次
	}
    //倒入一个欢迎的图片

	loadimage(&head, "fire/head.png", 400, 300, true);
    
}
```







#### 拓展- 使用easyX将图片转换为灰度图

```c++
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>//播放音乐的头文件
#include <minwindef.h>
#include <graphics.h>//图像处理文件
#include <string.h>
#include <conio.h>
#include <easyx.h>//图像处理文件
#pragma comment (lib,"Winmm.lib")//播放音乐的库文件

void colorToGray(IMAGE*src)
{
	DWORD* pbuf = GetImageBuffer(src);
	int srcw = src->getwidth();
	int srch = src->getheight();

	for (size_t i = 0; i < srcw * srch; i++)
	{
		DWORD color = pbuf[i];
		BYTE r = (BYTE)color;
		BYTE g = (BYTE)(color >> 8);
		BYTE b = (BYTE)(color >> 16);
		BYTE a = (BYTE)(color >> 24);
		int avg = (r + b + g + a)/ 4;
		
		pbuf[i] =  RGB(avg,avg,avg);
	
		

	}
    putimage(0,0,&src,SRCINVERT/*可以不加*/);

}

int main()
{
		IMAGE image;
    	loadimage(&image, L"./1.jpg",800/4,450/4);
    	int iw = image.getwidth();//获取图片的宽
		int ih = image.getheight();//获取图片的高
    	colorToGray(&image);
    	
    
}	
    
```



#### 使用opencv将图片转化为灰度图

```c++
#include <opencv2\opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class QucikDemo 
{
    public:
    		void colorSpce_Demo(Mat &image);
}


void QucikDemo::colorSpce_Demo(Mat &iamge)
{
	Mat gray, hsv;
	cvtColor(iamge, hsv, COLOR_BGR2HSV);
	cvtColor(iamge, gray, COLOR_BGR2GRAY);
	namedWindow("HSV", WINDOW_FREERATIO);
	imshow("HSV",hsv);
	namedWindow("灰度", WINDOW_FREERATIO);
	imshow("灰度",gray);
	imwrite("F:\\WorkCpp\\opencvProject\\hsv.jpg",hsv);//保存图片
	imwrite("F:\\WorkCpp\\opencvProject\\gray.jpg", gray);
}

int main(int argc, char** argv)
{
	Mat src = imread("F:\\WorkCpp\\opencvProject\\1.jpg" ,/*IMREAD_GRAYSCALE/*灰度处理*/IMREAD_UNCHANGED/*显示透明通道*/);
    
    if (src.empty())
	{
		printf("图片倒入失败，请检查图像是否损坏以及图像路径是否错误\n");
		return -1;
	}
	namedWindow("原图", WINDOW_FREERATIO);

	imshow("原图", src);
     QucikDemo qd;
	qd.colorSpce_Demo(src);
    
    waitKey(0);//等待操作 相当于 system("pause"); 的作用
	destroyAllWindows();//关闭所有窗口
    
}


```

我这里使用了开源的opencv 有兴趣的可以加我QQ我发给你，遇到不懂的也可以加我QQ给你解决。有什么问题欢迎加我QQ一起解决

**我的QQ：3204877338**



#### MAT的讲解

```c++
// 定义图像对象
class IMAGE
{
public:
	int getwidth() const;	// 获取对象的宽度
	int getheight() const;	// 获取对象的高度

private:
	int width, height;		// 对象的宽高
	HBITMAP m_hBmp;
	HDC m_hMemDC;
	float m_data[6];
	COLORREF	m_LineColor;		// 当前线条颜色
	COLORREF	m_FillColor;		// 当前填充颜色
	COLORREF	m_TextColor;		// 当前文字颜色
	COLORREF	m_BkColor;			// 当前背景颜色
	DWORD*		m_pBuffer;			// 绘图区的内存

	LINESTYLE	m_LineStyle;		// 画线样式
	FILLSTYLE	m_FillStyle;		// 填充样式

	virtual void SetDefault();						// 设置为默认状态

public:
	IMAGE(int _width = 0, int _height = 0);			// 创建图像
	IMAGE(const IMAGE &img);						// 拷贝构造函数
	IMAGE& operator = (const IMAGE &img);			// 赋值运算符重载函数
	virtual ~IMAGE();
	virtual void Resize(int _width, int _height);	// 调整尺寸
};

```

**我们可以看到IMAGE也是一个c++的类 ，其相当于opencvMat**

Mat

```c++
class CV_EXPORTS Mat
{
public:
    /**
    These are various constructors that form a matrix. As noted in the AutomaticAllocation, often
    the default constructor is enough, and the proper matrix will be allocated by an OpenCV function.
    The constructed matrix can further be assigned to another matrix or matrix expression or can be
    allocated with Mat::create . In the former case, the old content is de-referenced.
     */
    Mat();

    /** @overload
    @param rows Number of rows in a 2D array.
    @param cols Number of columns in a 2D array.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    */
    Mat(int rows, int cols, int type);

    /** @overload
    @param size 2D array size: Size(cols, rows) . In the Size() constructor, the number of rows and the
    number of columns go in the reverse order.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
      */
    Mat(Size size, int type);

    /** @overload
    @param rows Number of rows in a 2D array.
    @param cols Number of columns in a 2D array.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param s An optional value to initialize each matrix element with. To set all the matrix elements to
    the particular value after the construction, use the assignment operator
    Mat::operator=(const Scalar& value) .
    */
    Mat(int rows, int cols, int type, const Scalar& s);

    /** @overload
    @param size 2D array size: Size(cols, rows) . In the Size() constructor, the number of rows and the
    number of columns go in the reverse order.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param s An optional value to initialize each matrix element with. To set all the matrix elements to
    the particular value after the construction, use the assignment operator
    Mat::operator=(const Scalar& value) .
      */
    Mat(Size size, int type, const Scalar& s);

    /** @overload
    @param ndims Array dimensionality.
    @param sizes Array of integers specifying an n-dimensional array shape.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    */
    Mat(int ndims, const int* sizes, int type);

    /** @overload
    @param sizes Array of integers specifying an n-dimensional array shape.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    */
    Mat(const std::vector<int>& sizes, int type);

    /** @overload
    @param ndims Array dimensionality.
    @param sizes Array of integers specifying an n-dimensional array shape.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param s An optional value to initialize each matrix element with. To set all the matrix elements to
    the particular value after the construction, use the assignment operator
    Mat::operator=(const Scalar& value) .
    */
    Mat(int ndims, const int* sizes, int type, const Scalar& s);

    /** @overload
    @param sizes Array of integers specifying an n-dimensional array shape.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param s An optional value to initialize each matrix element with. To set all the matrix elements to
    the particular value after the construction, use the assignment operator
    Mat::operator=(const Scalar& value) .
    */
    Mat(const std::vector<int>& sizes, int type, const Scalar& s);


    /** @overload
    @param m Array that (as a whole or partly) is assigned to the constructed matrix. No data is copied
    by these constructors. Instead, the header pointing to m data or its sub-array is constructed and
    associated with it. The reference counter, if any, is incremented. So, when you modify the matrix
    formed using such a constructor, you also modify the corresponding elements of m . If you want to
    have an independent copy of the sub-array, use Mat::clone() .
    */
    Mat(const Mat& m);

    /** @overload
    @param rows Number of rows in a 2D array.
    @param cols Number of columns in a 2D array.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param data Pointer to the user data. Matrix constructors that take data and step parameters do not
    allocate matrix data. Instead, they just initialize the matrix header that points to the specified
    data, which means that no data is copied. This operation is very efficient and can be used to
    process external data using OpenCV functions. The external data is not automatically deallocated, so
    you should take care of it.
    @param step Number of bytes each matrix row occupies. The value should include the padding bytes at
    the end of each row, if any. If the parameter is missing (set to AUTO_STEP ), no padding is assumed
    and the actual step is calculated as cols*elemSize(). See Mat::elemSize.
    */
    Mat(int rows, int cols, int type, void* data, size_t step=AUTO_STEP);

    /** @overload
    @param size 2D array size: Size(cols, rows) . In the Size() constructor, the number of rows and the
    number of columns go in the reverse order.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param data Pointer to the user data. Matrix constructors that take data and step parameters do not
    allocate matrix data. Instead, they just initialize the matrix header that points to the specified
    data, which means that no data is copied. This operation is very efficient and can be used to
    process external data using OpenCV functions. The external data is not automatically deallocated, so
    you should take care of it.
    @param step Number of bytes each matrix row occupies. The value should include the padding bytes at
    the end of each row, if any. If the parameter is missing (set to AUTO_STEP ), no padding is assumed
    and the actual step is calculated as cols*elemSize(). See Mat::elemSize.
    */
    Mat(Size size, int type, void* data, size_t step=AUTO_STEP);

    /** @overload
    @param ndims Array dimensionality.
    @param sizes Array of integers specifying an n-dimensional array shape.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param data Pointer to the user data. Matrix constructors that take data and step parameters do not
    allocate matrix data. Instead, they just initialize the matrix header that points to the specified
    data, which means that no data is copied. This operation is very efficient and can be used to
    process external data using OpenCV functions. The external data is not automatically deallocated, so
    you should take care of it.
    @param steps Array of ndims-1 steps in case of a multi-dimensional array (the last step is always
    set to the element size). If not specified, the matrix is assumed to be continuous.
    */
    Mat(int ndims, const int* sizes, int type, void* data, const size_t* steps=0);

    /** @overload
    @param sizes Array of integers specifying an n-dimensional array shape.
    @param type Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or
    CV_8UC(n), ..., CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
    @param data Pointer to the user data. Matrix constructors that take data and step parameters do not
    allocate matrix data. Instead, they just initialize the matrix header that points to the specified
    data, which means that no data is copied. This operation is very efficient and can be used to
    process external data using OpenCV functions. The external data is not automatically deallocated, so
    you should take care of it.
    @param steps Array of ndims-1 steps in case of a multi-dimensional array (the last step is always
    set to the element size). If not specified, the matrix is assumed to be continuous.
    */
    Mat(const std::vector<int>& sizes, int type, void* data, const size_t* steps=0);

    /** @overload
    @param m Array that (as a whole or partly) is assigned to the constructed matrix. No data is copied
    by these constructors. Instead, the header pointing to m data or its sub-array is constructed and
    associated with it. The reference counter, if any, is incremented. So, when you modify the matrix
    formed using such a constructor, you also modify the corresponding elements of m . If you want to
    have an independent copy of the sub-array, use Mat::clone() .
    @param rowRange Range of the m rows to take. As usual, the range start is inclusive and the range
    end is exclusive. Use Range::all() to take all the rows.
    @param colRange Range of the m columns to take. Use Range::all() to take all the columns.
    */
    Mat(const Mat& m, const Range& rowRange, const Range& colRange=Range::all());

    /** @overload
    @param m Array that (as a whole or partly) is assigned to the constructed matrix. No data is copied
    by these constructors. Instead, the header pointing to m data or its sub-array is constructed and
    associated with it. The reference counter, if any, is incremented. So, when you modify the matrix
    formed using such a constructor, you also modify the corresponding elements of m . If you want to
    have an independent copy of the sub-array, use Mat::clone() .
    @param roi Region of interest.
    */
    Mat(const Mat& m, const Rect& roi);

    /** @overload
    @param m Array that (as a whole or partly) is assigned to the constructed matrix. No data is copied
    by these constructors. Instead, the header pointing to m data or its sub-array is constructed and
    associated with it. The reference counter, if any, is incremented. So, when you modify the matrix
    formed using such a constructor, you also modify the corresponding elements of m . If you want to
    have an independent copy of the sub-array, use Mat::clone() .
    @param ranges Array of selected ranges of m along each dimensionality.
    */
    Mat(const Mat& m, const Range* ranges);

    /** @overload
    @param m Array that (as a whole or partly) is assigned to the constructed matrix. No data is copied
    by these constructors. Instead, the header pointing to m data or its sub-array is constructed and
    associated with it. The reference counter, if any, is incremented. So, when you modify the matrix
    formed using such a constructor, you also modify the corresponding elements of m . If you want to
    have an independent copy of the sub-array, use Mat::clone() .
    @param ranges Array of selected ranges of m along each dimensionality.
    */
    Mat(const Mat& m, const std::vector<Range>& ranges);

    /** @overload
    @param vec STL vector whose elements form the matrix. The matrix has a single column and the number
    of rows equal to the number of vector elements. Type of the matrix matches the type of vector
    elements. The constructor can handle arbitrary types, for which there is a properly declared
    DataType . This means that the vector elements must be primitive numbers or uni-type numerical
    tuples of numbers. Mixed-type structures are not supported. The corresponding constructor is
    explicit. Since STL vectors are not automatically converted to Mat instances, you should write
    Mat(vec) explicitly. Unless you copy the data into the matrix ( copyData=true ), no new elements
    will be added to the vector because it can potentially yield vector data reallocation, and, thus,
    the matrix data pointer will be invalid.
    @param copyData Flag to specify whether the underlying data of the STL vector should be copied
    to (true) or shared with (false) the newly constructed matrix. When the data is copied, the
    allocated buffer is managed using Mat reference counting mechanism. While the data is shared,
    the reference counter is NULL, and you should not deallocate the data until the matrix is not
    destructed.
    */
    template<typename _Tp> explicit Mat(const std::vector<_Tp>& vec, bool copyData=false);

    /** @overload
    */
    template<typename _Tp, typename = typename std::enable_if<std::is_arithmetic<_Tp>::value>::type>
    explicit Mat(const std::initializer_list<_Tp> list);

    /** @overload
    */
    template<typename _Tp> explicit Mat(const std::initializer_list<int> sizes, const std::initializer_list<_Tp> list);

    /** @overload
    */
    template<typename _Tp, size_t _Nm> explicit Mat(const std::array<_Tp, _Nm>& arr, bool copyData=false);

    /** @overload
    */
    template<typename _Tp, int n> explicit Mat(const Vec<_Tp, n>& vec, bool copyData=true);

    /** @overload
    */
    template<typename _Tp, int m, int n> explicit Mat(const Matx<_Tp, m, n>& mtx, bool copyData=true);

    /** @overload
    */
    template<typename _Tp> explicit Mat(const Point_<_Tp>& pt, bool copyData=true);

    /** @overload
    */
    template<typename _Tp> explicit Mat(const Point3_<_Tp>& pt, bool copyData=true);

    /** @overload
    */
    template<typename _Tp> explicit Mat(const MatCommaInitializer_<_Tp>& commaInitializer);

    //! download data from GpuMat
    explicit Mat(const cuda::GpuMat& m);

    //! destructor - calls release()
    ~Mat();

    /** @brief assignment operators

    These are available assignment operators. Since they all are very different, make sure to read the
    operator parameters description.
    @param m Assigned, right-hand-side matrix. Matrix assignment is an O(1) operation. This means that
    no data is copied but the data is shared and the reference counter, if any, is incremented. Before
    assigning new data, the old data is de-referenced via Mat::release .
     */
    Mat& operator = (const Mat& m);

    /** @overload
    @param expr Assigned matrix expression object. As opposite to the first form of the assignment
    operation, the second form can reuse already allocated matrix if it has the right size and type to
    fit the matrix expression result. It is automatically handled by the real function that the matrix
    expressions is expanded to. For example, C=A+B is expanded to add(A, B, C), and add takes care of
    automatic C reallocation.
    */
    Mat& operator = (const MatExpr& expr);

    //! retrieve UMat from Mat
    UMat getUMat(AccessFlag accessFlags, UMatUsageFlags usageFlags = USAGE_DEFAULT) const;

    /** @brief Creates a matrix header for the specified matrix row.

    The method makes a new header for the specified matrix row and returns it. This is an O(1)
    operation, regardless of the matrix size. The underlying data of the new matrix is shared with the
    original matrix. Here is the example of one of the classical basic matrix processing operations,
    axpy, used by LU and many other algorithms:
    @code
        inline void matrix_axpy(Mat& A, int i, int j, double alpha)
        {
            A.row(i) += A.row(j)*alpha;
        }
    @endcode
    @note In the current implementation, the following code does not work as expected:
    @code
        Mat A;
        ...
        A.row(i) = A.row(j); // will not work
    @endcode
    This happens because A.row(i) forms a temporary header that is further assigned to another header.
    Remember that each of these operations is O(1), that is, no data is copied. Thus, the above
    assignment is not true if you may have expected the j-th row to be copied to the i-th row. To
    achieve that, you should either turn this simple assignment into an expression or use the
    Mat::copyTo method:
    @code
        Mat A;
        ...
        // works, but looks a bit obscure.
        A.row(i) = A.row(j) + 0;
        // this is a bit longer, but the recommended method.
        A.row(j).copyTo(A.row(i));
    @endcode
    @param y A 0-based row index.
     */
    Mat row(int y) const;

    /** @brief Creates a matrix header for the specified matrix column.

    The method makes a new header for the specified matrix column and returns it. This is an O(1)
    operation, regardless of the matrix size. The underlying data of the new matrix is shared with the
    original matrix. See also the Mat::row description.
    @param x A 0-based column index.
     */
    Mat col(int x) const;

    /** @brief Creates a matrix header for the specified row span.

    The method makes a new header for the specified row span of the matrix. Similarly to Mat::row and
    Mat::col , this is an O(1) operation.
    @param startrow An inclusive 0-based start index of the row span.
    @param endrow An exclusive 0-based ending index of the row span.
     */
    Mat rowRange(int startrow, int endrow) const;

    /** @overload
    @param r Range structure containing both the start and the end indices.
    */
    Mat rowRange(const Range& r) const;

    /** @brief Creates a matrix header for the specified column span.

    The method makes a new header for the specified column span of the matrix. Similarly to Mat::row and
    Mat::col , this is an O(1) operation.
    @param startcol An inclusive 0-based start index of the column span.
    @param endcol An exclusive 0-based ending index of the column span.
     */
    Mat colRange(int startcol, int endcol) const;

    /** @overload
    @param r Range structure containing both the start and the end indices.
    */
    Mat colRange(const Range& r) const;

    /** @brief Extracts a diagonal from a matrix

    The method makes a new header for the specified matrix diagonal. The new matrix is represented as a
    single-column matrix. Similarly to Mat::row and Mat::col, this is an O(1) operation.
    @param d index of the diagonal, with the following values:
    - `d=0` is the main diagonal.
    - `d<0` is a diagonal from the lower half. For example, d=-1 means the diagonal is set
      immediately below the main one.
    - `d>0` is a diagonal from the upper half. For example, d=1 means the diagonal is set
      immediately above the main one.
    For example:
    @code
        Mat m = (Mat_<int>(3,3) <<
                    1,2,3,
                    4,5,6,
                    7,8,9);
        Mat d0 = m.diag(0);
        Mat d1 = m.diag(1);
        Mat d_1 = m.diag(-1);
    @endcode
    The resulting matrices are
    @code
     d0 =
       [1;
        5;
        9]
     d1 =
       [2;
        6]
     d_1 =
       [4;
        8]
    @endcode
     */
    Mat diag(int d=0) const;

    /** @brief creates a diagonal matrix

    The method creates a square diagonal matrix from specified main diagonal.
    @param d One-dimensional matrix that represents the main diagonal.
     */
    static Mat diag(const Mat& d);

    /** @brief Creates a full copy of the array and the underlying data.

    The method creates a full copy of the array. The original step[] is not taken into account. So, the
    array copy is a continuous array occupying total()*elemSize() bytes.
     */
    Mat clone() const CV_NODISCARD;

    /** @brief Copies the matrix to another one.

    The method copies the matrix data to another matrix. Before copying the data, the method invokes :
    @code
        m.create(this->size(), this->type());
    @endcode
    so that the destination matrix is reallocated if needed. While m.copyTo(m); works flawlessly, the
    function does not handle the case of a partial overlap between the source and the destination
    matrices.

    When the operation mask is specified, if the Mat::create call shown above reallocates the matrix,
    the newly allocated matrix is initialized with all zeros before copying the data.
    @param m Destination matrix. If it does not have a proper size or type before the operation, it is
    reallocated.
     */
    void copyTo( OutputArray m ) const;

    /** @overload
    @param m Destination matrix. If it does not have a proper size or type before the operation, it is
    reallocated.
    @param mask Operation mask of the same size as \*this. Its non-zero elements indicate which matrix
    elements need to be copied. The mask has to be of type CV_8U and can have 1 or multiple channels.
    */
    void copyTo( OutputArray m, InputArray mask ) const;

    /** @brief Converts an array to another data type with optional scaling.

    The method converts source pixel values to the target data type. saturate_cast\<\> is applied at
    the end to avoid possible overflows:

    \f[m(x,y) = saturate \_ cast<rType>( \alpha (*this)(x,y) +  \beta )\f]
    @param m output matrix; if it does not have a proper size or type before the operation, it is
    reallocated.
    @param rtype desired output matrix type or, rather, the depth since the number of channels are the
    same as the input has; if rtype is negative, the output matrix will have the same type as the input.
    @param alpha optional scale factor.
    @param beta optional delta added to the scaled values.
     */
    void convertTo( OutputArray m, int rtype, double alpha=1, double beta=0 ) const;

    /** @brief Provides a functional form of convertTo.

    This is an internally used method called by the @ref MatrixExpressions engine.
    @param m Destination array.
    @param type Desired destination array depth (or -1 if it should be the same as the source type).
     */
    void assignTo( Mat& m, int type=-1 ) const;

    /** @brief Sets all or some of the array elements to the specified value.
    @param s Assigned scalar converted to the actual array type.
    */
    Mat& operator = (const Scalar& s);

    /** @brief Sets all or some of the array elements to the specified value.

    This is an advanced variant of the Mat::operator=(const Scalar& s) operator.
    @param value Assigned scalar converted to the actual array type.
    @param mask Operation mask of the same size as \*this. Its non-zero elements indicate which matrix
    elements need to be copied. The mask has to be of type CV_8U and can have 1 or multiple channels
     */
    Mat& setTo(InputArray value, InputArray mask=noArray());

    /** @brief Changes the shape and/or the number of channels of a 2D matrix without copying the data.

    The method makes a new matrix header for \*this elements. The new matrix may have a different size
    and/or different number of channels. Any combination is possible if:
    -   No extra elements are included into the new matrix and no elements are excluded. Consequently,
        the product rows\*cols\*channels() must stay the same after the transformation.
    -   No data is copied. That is, this is an O(1) operation. Consequently, if you change the number of
        rows, or the operation changes the indices of elements row in some other way, the matrix must be
        continuous. See Mat::isContinuous .

    For example, if there is a set of 3D points stored as an STL vector, and you want to represent the
    points as a 3xN matrix, do the following:
    @code
        std::vector<Point3f> vec;
        ...
        Mat pointMat = Mat(vec). // convert vector to Mat, O(1) operation
                          reshape(1). // make Nx3 1-channel matrix out of Nx1 3-channel.
                                      // Also, an O(1) operation
                             t(); // finally, transpose the Nx3 matrix.
                                  // This involves copying all the elements
    @endcode
    @param cn New number of channels. If the parameter is 0, the number of channels remains the same.
    @param rows New number of rows. If the parameter is 0, the number of rows remains the same.
     */
    Mat reshape(int cn, int rows=0) const;

    /** @overload */
    Mat reshape(int cn, int newndims, const int* newsz) const;

    /** @overload */
    Mat reshape(int cn, const std::vector<int>& newshape) const;

    /** @brief Transposes a matrix.

    The method performs matrix transposition by means of matrix expressions. It does not perform the
    actual transposition but returns a temporary matrix transposition object that can be further used as
    a part of more complex matrix expressions or can be assigned to a matrix:
    @code
        Mat A1 = A + Mat::eye(A.size(), A.type())*lambda;
        Mat C = A1.t()*A1; // compute (A + lambda*I)^t * (A + lamda*I)
    @endcode
     */
    MatExpr t() const;

    /** @brief Inverses a matrix.

    The method performs a matrix inversion by means of matrix expressions. This means that a temporary
    matrix inversion object is returned by the method and can be used further as a part of more complex
    matrix expressions or can be assigned to a matrix.
    @param method Matrix inversion method. One of cv::DecompTypes
     */
    MatExpr inv(int method=DECOMP_LU) const;

    /** @brief Performs an element-wise multiplication or division of the two matrices.

    The method returns a temporary object encoding per-element array multiplication, with optional
    scale. Note that this is not a matrix multiplication that corresponds to a simpler "\*" operator.

    Example:
    @code
        Mat C = A.mul(5/B); // equivalent to divide(A, B, C, 5)
    @endcode
    @param m Another array of the same type and the same size as \*this, or a matrix expression.
    @param scale Optional scale factor.
     */
    MatExpr mul(InputArray m, double scale=1) const;

    /** @brief Computes a cross-product of two 3-element vectors.

    The method computes a cross-product of two 3-element vectors. The vectors must be 3-element
    floating-point vectors of the same shape and size. The result is another 3-element vector of the
    same shape and type as operands.
    @param m Another cross-product operand.
     */
    Mat cross(InputArray m) const;

    /** @brief Computes a dot-product of two vectors.

    The method computes a dot-product of two matrices. If the matrices are not single-column or
    single-row vectors, the top-to-bottom left-to-right scan ordering is used to treat them as 1D
    vectors. The vectors must have the same size and type. If the matrices have more than one channel,
    the dot products from all the channels are summed together.
    @param m another dot-product operand.
     */
    double dot(InputArray m) const;

    /** @brief Returns a zero array of the specified size and type.

    The method returns a Matlab-style zero array initializer. It can be used to quickly form a constant
    array as a function parameter, part of a matrix expression, or as a matrix initializer:
    @code
        Mat A;
        A = Mat::zeros(3, 3, CV_32F);
    @endcode
    In the example above, a new matrix is allocated only if A is not a 3x3 floating-point matrix.
    Otherwise, the existing matrix A is filled with zeros.
    @param rows Number of rows.
    @param cols Number of columns.
    @param type Created matrix type.
     */
    static MatExpr zeros(int rows, int cols, int type);

    /** @overload
    @param size Alternative to the matrix size specification Size(cols, rows) .
    @param type Created matrix type.
    */
    static MatExpr zeros(Size size, int type);

    /** @overload
    @param ndims Array dimensionality.
    @param sz Array of integers specifying the array shape.
    @param type Created matrix type.
    */
    static MatExpr zeros(int ndims, const int* sz, int type);

    /** @brief Returns an array of all 1's of the specified size and type.

    The method returns a Matlab-style 1's array initializer, similarly to Mat::zeros. Note that using
    this method you can initialize an array with an arbitrary value, using the following Matlab idiom:
    @code
        Mat A = Mat::ones(100, 100, CV_8U)*3; // make 100x100 matrix filled with 3.
    @endcode
    The above operation does not form a 100x100 matrix of 1's and then multiply it by 3. Instead, it
    just remembers the scale factor (3 in this case) and use it when actually invoking the matrix
    initializer.
    @note In case of multi-channels type, only the first channel will be initialized with 1's, the
    others will be set to 0's.
    @param rows Number of rows.
    @param cols Number of columns.
    @param type Created matrix type.
     */
    static MatExpr ones(int rows, int cols, int type);

    /** @overload
    @param size Alternative to the matrix size specification Size(cols, rows) .
    @param type Created matrix type.
    */
    static MatExpr ones(Size size, int type);

    /** @overload
    @param ndims Array dimensionality.
    @param sz Array of integers specifying the array shape.
    @param type Created matrix type.
    */
    static MatExpr ones(int ndims, const int* sz, int type);

    /** @brief Returns an identity matrix of the specified size and type.

    The method returns a Matlab-style identity matrix initializer, similarly to Mat::zeros. Similarly to
    Mat::ones, you can use a scale operation to create a scaled identity matrix efficiently:
    @code
        // make a 4x4 diagonal matrix with 0.1's on the diagonal.
        Mat A = Mat::eye(4, 4, CV_32F)*0.1;
    @endcode
    @note In case of multi-channels type, identity matrix will be initialized only for the first channel,
    the others will be set to 0's
    @param rows Number of rows.
    @param cols Number of columns.
    @param type Created matrix type.
     */
    static MatExpr eye(int rows, int cols, int type);

    /** @overload
    @param size Alternative matrix size specification as Size(cols, rows) .
    @param type Created matrix type.
    */
    static MatExpr eye(Size size, int type);

    /** @brief Allocates new array data if needed.

    This is one of the key Mat methods. Most new-style OpenCV functions and methods that produce arrays
    call this method for each output array. The method uses the following algorithm:

    -# If the current array shape and the type match the new ones, return immediately. Otherwise,
       de-reference the previous data by calling Mat::release.
    -# Initialize the new header.
    -# Allocate the new data of total()\*elemSize() bytes.
    -# Allocate the new, associated with the data, reference counter and set it to 1.

    Such a scheme makes the memory management robust and efficient at the same time and helps avoid
    extra typing for you. This means that usually there is no need to explicitly allocate output arrays.
    That is, instead of writing:
    @code
        Mat color;
        ...
        Mat gray(color.rows, color.cols, color.depth());
        cvtColor(color, gray, COLOR_BGR2GRAY);
    @endcode
    you can simply write:
    @code
        Mat color;
        ...
        Mat gray;
        cvtColor(color, gray, COLOR_BGR2GRAY);
    @endcode
    because cvtColor, as well as the most of OpenCV functions, calls Mat::create() for the output array
    internally.
    @param rows New number of rows.
    @param cols New number of columns.
    @param type New matrix type.
     */
    void create(int rows, int cols, int type);

    /** @overload
    @param size Alternative new matrix size specification: Size(cols, rows)
    @param type New matrix type.
    */
    void create(Size size, int type);

    /** @overload
    @param ndims New array dimensionality.
    @param sizes Array of integers specifying a new array shape.
    @param type New matrix type.
    */
    void create(int ndims, const int* sizes, int type);

    /** @overload
    @param sizes Array of integers specifying a new array shape.
    @param type New matrix type.
    */
    void create(const std::vector<int>& sizes, int type);

    /** @brief Increments the reference counter.

    The method increments the reference counter associated with the matrix data. If the matrix header
    points to an external data set (see Mat::Mat ), the reference counter is NULL, and the method has no
    effect in this case. Normally, to avoid memory leaks, the method should not be called explicitly. It
    is called implicitly by the matrix assignment operator. The reference counter increment is an atomic
    operation on the platforms that support it. Thus, it is safe to operate on the same matrices
    asynchronously in different threads.
     */
    void addref();

    /** @brief Decrements the reference counter and deallocates the matrix if needed.

    The method decrements the reference counter associated with the matrix data. When the reference
    counter reaches 0, the matrix data is deallocated and the data and the reference counter pointers
    are set to NULL's. If the matrix header points to an external data set (see Mat::Mat ), the
    reference counter is NULL, and the method has no effect in this case.

    This method can be called manually to force the matrix data deallocation. But since this method is
    automatically called in the destructor, or by any other method that changes the data pointer, it is
    usually not needed. The reference counter decrement and check for 0 is an atomic operation on the
    platforms that support it. Thus, it is safe to operate on the same matrices asynchronously in
    different threads.
     */
    void release();

    //! internal use function, consider to use 'release' method instead; deallocates the matrix data
    void deallocate();
    //! internal use function; properly re-allocates _size, _step arrays
    void copySize(const Mat& m);

    /** @brief Reserves space for the certain number of rows.

    The method reserves space for sz rows. If the matrix already has enough space to store sz rows,
    nothing happens. If the matrix is reallocated, the first Mat::rows rows are preserved. The method
    emulates the corresponding method of the STL vector class.
    @param sz Number of rows.
     */
    void reserve(size_t sz);

    /** @brief Reserves space for the certain number of bytes.

    The method reserves space for sz bytes. If the matrix already has enough space to store sz bytes,
    nothing happens. If matrix has to be reallocated its previous content could be lost.
    @param sz Number of bytes.
    */
    void reserveBuffer(size_t sz);

    /** @brief Changes the number of matrix rows.

    The methods change the number of matrix rows. If the matrix is reallocated, the first
    min(Mat::rows, sz) rows are preserved. The methods emulate the corresponding methods of the STL
    vector class.
    @param sz New number of rows.
     */
    void resize(size_t sz);

    /** @overload
    @param sz New number of rows.
    @param s Value assigned to the newly added elements.
     */
    void resize(size_t sz, const Scalar& s);

    //! internal function
    void push_back_(const void* elem);

    /** @brief Adds elements to the bottom of the matrix.

    The methods add one or more elements to the bottom of the matrix. They emulate the corresponding
    method of the STL vector class. When elem is Mat , its type and the number of columns must be the
    same as in the container matrix.
    @param elem Added element(s).
     */
    template<typename _Tp> void push_back(const _Tp& elem);

    /** @overload
    @param elem Added element(s).
    */
    template<typename _Tp> void push_back(const Mat_<_Tp>& elem);

    /** @overload
    @param elem Added element(s).
    */
    template<typename _Tp> void push_back(const std::vector<_Tp>& elem);

    /** @overload
    @param m Added line(s).
    */
    void push_back(const Mat& m);

    /** @brief Removes elements from the bottom of the matrix.

    The method removes one or more rows from the bottom of the matrix.
    @param nelems Number of removed rows. If it is greater than the total number of rows, an exception
    is thrown.
     */
    void pop_back(size_t nelems=1);

    /** @brief Locates the matrix header within a parent matrix.

    After you extracted a submatrix from a matrix using Mat::row, Mat::col, Mat::rowRange,
    Mat::colRange, and others, the resultant submatrix points just to the part of the original big
    matrix. However, each submatrix contains information (represented by datastart and dataend
    fields) that helps reconstruct the original matrix size and the position of the extracted
    submatrix within the original matrix. The method locateROI does exactly that.
    @param wholeSize Output parameter that contains the size of the whole matrix containing *this*
    as a part.
    @param ofs Output parameter that contains an offset of *this* inside the whole matrix.
     */
    void locateROI( Size& wholeSize, Point& ofs ) const;

    /** @brief Adjusts a submatrix size and position within the parent matrix.

    The method is complimentary to Mat::locateROI . The typical use of these functions is to determine
    the submatrix position within the parent matrix and then shift the position somehow. Typically, it
    can be required for filtering operations when pixels outside of the ROI should be taken into
    account. When all the method parameters are positive, the ROI needs to grow in all directions by the
    specified amount, for example:
    @code
        A.adjustROI(2, 2, 2, 2);
    @endcode
    In this example, the matrix size is increased by 4 elements in each direction. The matrix is shifted
    by 2 elements to the left and 2 elements up, which brings in all the necessary pixels for the
    filtering with the 5x5 kernel.

    adjustROI forces the adjusted ROI to be inside of the parent matrix that is boundaries of the
    adjusted ROI are constrained by boundaries of the parent matrix. For example, if the submatrix A is
    located in the first row of a parent matrix and you called A.adjustROI(2, 2, 2, 2) then A will not
    be increased in the upward direction.

    The function is used internally by the OpenCV filtering functions, like filter2D , morphological
    operations, and so on.
    @param dtop Shift of the top submatrix boundary upwards.
    @param dbottom Shift of the bottom submatrix boundary downwards.
    @param dleft Shift of the left submatrix boundary to the left.
    @param dright Shift of the right submatrix boundary to the right.
    @sa copyMakeBorder
     */
    Mat& adjustROI( int dtop, int dbottom, int dleft, int dright );

    /** @brief Extracts a rectangular submatrix.

    The operators make a new header for the specified sub-array of \*this . They are the most
    generalized forms of Mat::row, Mat::col, Mat::rowRange, and Mat::colRange . For example,
    `A(Range(0, 10), Range::all())` is equivalent to `A.rowRange(0, 10)`. Similarly to all of the above,
    the operators are O(1) operations, that is, no matrix data is copied.
    @param rowRange Start and end row of the extracted submatrix. The upper boundary is not included. To
    select all the rows, use Range::all().
    @param colRange Start and end column of the extracted submatrix. The upper boundary is not included.
    To select all the columns, use Range::all().
     */
    Mat operator()( Range rowRange, Range colRange ) const;

    /** @overload
    @param roi Extracted submatrix specified as a rectangle.
    */
    Mat operator()( const Rect& roi ) const;

    /** @overload
    @param ranges Array of selected ranges along each array dimension.
    */
    Mat operator()( const Range* ranges ) const;

    /** @overload
    @param ranges Array of selected ranges along each array dimension.
    */
    Mat operator()(const std::vector<Range>& ranges) const;

    template<typename _Tp> operator std::vector<_Tp>() const;
    template<typename _Tp, int n> operator Vec<_Tp, n>() const;
    template<typename _Tp, int m, int n> operator Matx<_Tp, m, n>() const;

    template<typename _Tp, std::size_t _Nm> operator std::array<_Tp, _Nm>() const;

    /** @brief Reports whether the matrix is continuous or not.

    The method returns true if the matrix elements are stored continuously without gaps at the end of
    each row. Otherwise, it returns false. Obviously, 1x1 or 1xN matrices are always continuous.
    Matrices created with Mat::create are always continuous. But if you extract a part of the matrix
    using Mat::col, Mat::diag, and so on, or constructed a matrix header for externally allocated data,
    such matrices may no longer have this property.

    The continuity flag is stored as a bit in the Mat::flags field and is computed automatically when
    you construct a matrix header. Thus, the continuity check is a very fast operation, though
    theoretically it could be done as follows:
    @code
        // alternative implementation of Mat::isContinuous()
        bool myCheckMatContinuity(const Mat& m)
        {
            //return (m.flags & Mat::CONTINUOUS_FLAG) != 0;
            return m.rows == 1 || m.step == m.cols*m.elemSize();
        }
    @endcode
    The method is used in quite a few of OpenCV functions. The point is that element-wise operations
    (such as arithmetic and logical operations, math functions, alpha blending, color space
    transformations, and others) do not depend on the image geometry. Thus, if all the input and output
    arrays are continuous, the functions can process them as very long single-row vectors. The example
    below illustrates how an alpha-blending function can be implemented:
    @code
        template<typename T>
        void alphaBlendRGBA(const Mat& src1, const Mat& src2, Mat& dst)
        {
            const float alpha_scale = (float)std::numeric_limits<T>::max(),
                        inv_scale = 1.f/alpha_scale;

            CV_Assert( src1.type() == src2.type() &&
                       src1.type() == CV_MAKETYPE(traits::Depth<T>::value, 4) &&
                       src1.size() == src2.size());
            Size size = src1.size();
            dst.create(size, src1.type());

            // here is the idiom: check the arrays for continuity and,
            // if this is the case,
            // treat the arrays as 1D vectors
            if( src1.isContinuous() && src2.isContinuous() && dst.isContinuous() )
            {
                size.width *= size.height;
                size.height = 1;
            }
            size.width *= 4;

            for( int i = 0; i < size.height; i++ )
            {
                // when the arrays are continuous,
                // the outer loop is executed only once
                const T* ptr1 = src1.ptr<T>(i);
                const T* ptr2 = src2.ptr<T>(i);
                T* dptr = dst.ptr<T>(i);

                for( int j = 0; j < size.width; j += 4 )
                {
                    float alpha = ptr1[j+3]*inv_scale, beta = ptr2[j+3]*inv_scale;
                    dptr[j] = saturate_cast<T>(ptr1[j]*alpha + ptr2[j]*beta);
                    dptr[j+1] = saturate_cast<T>(ptr1[j+1]*alpha + ptr2[j+1]*beta);
                    dptr[j+2] = saturate_cast<T>(ptr1[j+2]*alpha + ptr2[j+2]*beta);
                    dptr[j+3] = saturate_cast<T>((1 - (1-alpha)*(1-beta))*alpha_scale);
                }
            }
        }
    @endcode
    This approach, while being very simple, can boost the performance of a simple element-operation by
    10-20 percents, especially if the image is rather small and the operation is quite simple.

    Another OpenCV idiom in this function, a call of Mat::create for the destination array, that
    allocates the destination array unless it already has the proper size and type. And while the newly
    allocated arrays are always continuous, you still need to check the destination array because
    Mat::create does not always allocate a new matrix.
     */
    bool isContinuous() const;

    //! returns true if the matrix is a submatrix of another matrix
    bool isSubmatrix() const;

    /** @brief Returns the matrix element size in bytes.

    The method returns the matrix element size in bytes. For example, if the matrix type is CV_16SC3 ,
    the method returns 3\*sizeof(short) or 6.
     */
    size_t elemSize() const;

    /** @brief Returns the size of each matrix element channel in bytes.

    The method returns the matrix element channel size in bytes, that is, it ignores the number of
    channels. For example, if the matrix type is CV_16SC3 , the method returns sizeof(short) or 2.
     */
    size_t elemSize1() const;

    /** @brief Returns the type of a matrix element.

    The method returns a matrix element type. This is an identifier compatible with the CvMat type
    system, like CV_16SC3 or 16-bit signed 3-channel array, and so on.
     */
    int type() const;

    /** @brief Returns the depth of a matrix element.

    The method returns the identifier of the matrix element depth (the type of each individual channel).
    For example, for a 16-bit signed element array, the method returns CV_16S . A complete list of
    matrix types contains the following values:
    -   CV_8U - 8-bit unsigned integers ( 0..255 )
    -   CV_8S - 8-bit signed integers ( -128..127 )
    -   CV_16U - 16-bit unsigned integers ( 0..65535 )
    -   CV_16S - 16-bit signed integers ( -32768..32767 )
    -   CV_32S - 32-bit signed integers ( -2147483648..2147483647 )
    -   CV_32F - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )
    -   CV_64F - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )
     */
    int depth() const;

    /** @brief Returns the number of matrix channels.

    The method returns the number of matrix channels.
     */
    int channels() const;

    /** @brief Returns a normalized step.

    The method returns a matrix step divided by Mat::elemSize1() . It can be useful to quickly access an
    arbitrary matrix element.
     */
    size_t step1(int i=0) const;

    /** @brief Returns true if the array has no elements.

    The method returns true if Mat::total() is 0 or if Mat::data is NULL. Because of pop_back() and
    resize() methods `M.total() == 0` does not imply that `M.data == NULL`.
     */
    bool empty() const;

    /** @brief Returns the total number of array elements.

    The method returns the number of array elements (a number of pixels if the array represents an
    image).
     */
    size_t total() const;

    /** @brief Returns the total number of array elements.

     The method returns the number of elements within a certain sub-array slice with startDim <= dim < endDim
     */
    size_t total(int startDim, int endDim=INT_MAX) const;

    /**
     * @param elemChannels Number of channels or number of columns the matrix should have.
     *                     For a 2-D matrix, when the matrix has only 1 column, then it should have
     *                     elemChannels channels; When the matrix has only 1 channel,
     *                     then it should have elemChannels columns.
     *                     For a 3-D matrix, it should have only one channel. Furthermore,
     *                     if the number of planes is not one, then the number of rows
     *                     within every plane has to be 1; if the number of rows within
     *                     every plane is not 1, then the number of planes has to be 1.
     * @param depth The depth the matrix should have. Set it to -1 when any depth is fine.
     * @param requireContinuous Set it to true to require the matrix to be continuous
     * @return -1 if the requirement is not satisfied.
     *         Otherwise, it returns the number of elements in the matrix. Note
     *         that an element may have multiple channels.
     *
     * The following code demonstrates its usage for a 2-d matrix:
     * @snippet snippets/core_mat_checkVector.cpp example-2d
     *
     * The following code demonstrates its usage for a 3-d matrix:
     * @snippet snippets/core_mat_checkVector.cpp example-3d
     */
    int checkVector(int elemChannels, int depth=-1, bool requireContinuous=true) const;

    /** @brief Returns a pointer to the specified matrix row.

    The methods return `uchar*` or typed pointer to the specified matrix row. See the sample in
    Mat::isContinuous to know how to use these methods.
    @param i0 A 0-based row index.
     */
    uchar* ptr(int i0=0);
    /** @overload */
    const uchar* ptr(int i0=0) const;

    /** @overload
    @param row Index along the dimension 0
    @param col Index along the dimension 1
    */
    uchar* ptr(int row, int col);
    /** @overload
    @param row Index along the dimension 0
    @param col Index along the dimension 1
    */
    const uchar* ptr(int row, int col) const;

    /** @overload */
    uchar* ptr(int i0, int i1, int i2);
    /** @overload */
    const uchar* ptr(int i0, int i1, int i2) const;

    /** @overload */
    uchar* ptr(const int* idx);
    /** @overload */
    const uchar* ptr(const int* idx) const;
    /** @overload */
    template<int n> uchar* ptr(const Vec<int, n>& idx);
    /** @overload */
    template<int n> const uchar* ptr(const Vec<int, n>& idx) const;

    /** @overload */
    template<typename _Tp> _Tp* ptr(int i0=0);
    /** @overload */
    template<typename _Tp> const _Tp* ptr(int i0=0) const;
    /** @overload
    @param row Index along the dimension 0
    @param col Index along the dimension 1
    */
    template<typename _Tp> _Tp* ptr(int row, int col);
    /** @overload
    @param row Index along the dimension 0
    @param col Index along the dimension 1
    */
    template<typename _Tp> const _Tp* ptr(int row, int col) const;
    /** @overload */
    template<typename _Tp> _Tp* ptr(int i0, int i1, int i2);
    /** @overload */
    template<typename _Tp> const _Tp* ptr(int i0, int i1, int i2) const;
    /** @overload */
    template<typename _Tp> _Tp* ptr(const int* idx);
    /** @overload */
    template<typename _Tp> const _Tp* ptr(const int* idx) const;
    /** @overload */
    template<typename _Tp, int n> _Tp* ptr(const Vec<int, n>& idx);
    /** @overload */
    template<typename _Tp, int n> const _Tp* ptr(const Vec<int, n>& idx) const;

    /** @brief Returns a reference to the specified array element.

    The template methods return a reference to the specified array element. For the sake of higher
    performance, the index range checks are only performed in the Debug configuration.

    Note that the variants with a single index (i) can be used to access elements of single-row or
    single-column 2-dimensional arrays. That is, if, for example, A is a 1 x N floating-point matrix and
    B is an M x 1 integer matrix, you can simply write `A.at<float>(k+4)` and `B.at<int>(2*i+1)`
    instead of `A.at<float>(0,k+4)` and `B.at<int>(2*i+1,0)`, respectively.

    The example below initializes a Hilbert matrix:
    @code
        Mat H(100, 100, CV_64F);
        for(int i = 0; i < H.rows; i++)
            for(int j = 0; j < H.cols; j++)
                H.at<double>(i,j)=1./(i+j+1);
    @endcode

    Keep in mind that the size identifier used in the at operator cannot be chosen at random. It depends
    on the image from which you are trying to retrieve the data. The table below gives a better insight in this:
     - If matrix is of type `CV_8U` then use `Mat.at<uchar>(y,x)`.
     - If matrix is of type `CV_8S` then use `Mat.at<schar>(y,x)`.
     - If matrix is of type `CV_16U` then use `Mat.at<ushort>(y,x)`.
     - If matrix is of type `CV_16S` then use `Mat.at<short>(y,x)`.
     - If matrix is of type `CV_32S`  then use `Mat.at<int>(y,x)`.
     - If matrix is of type `CV_32F`  then use `Mat.at<float>(y,x)`.
     - If matrix is of type `CV_64F` then use `Mat.at<double>(y,x)`.

    @param i0 Index along the dimension 0
     */
    template<typename _Tp> _Tp& at(int i0=0);
    /** @overload
    @param i0 Index along the dimension 0
    */
    template<typename _Tp> const _Tp& at(int i0=0) const;
    /** @overload
    @param row Index along the dimension 0
    @param col Index along the dimension 1
    */
    template<typename _Tp> _Tp& at(int row, int col);
    /** @overload
    @param row Index along the dimension 0
    @param col Index along the dimension 1
    */
    template<typename _Tp> const _Tp& at(int row, int col) const;

    /** @overload
    @param i0 Index along the dimension 0
    @param i1 Index along the dimension 1
    @param i2 Index along the dimension 2
    */
    template<typename _Tp> _Tp& at(int i0, int i1, int i2);
    /** @overload
    @param i0 Index along the dimension 0
    @param i1 Index along the dimension 1
    @param i2 Index along the dimension 2
    */
    template<typename _Tp> const _Tp& at(int i0, int i1, int i2) const;

    /** @overload
    @param idx Array of Mat::dims indices.
    */
    template<typename _Tp> _Tp& at(const int* idx);
    /** @overload
    @param idx Array of Mat::dims indices.
    */
    template<typename _Tp> const _Tp& at(const int* idx) const;

    /** @overload */
    template<typename _Tp, int n> _Tp& at(const Vec<int, n>& idx);
    /** @overload */
    template<typename _Tp, int n> const _Tp& at(const Vec<int, n>& idx) const;

    /** @overload
    special versions for 2D arrays (especially convenient for referencing image pixels)
    @param pt Element position specified as Point(j,i) .
    */
    template<typename _Tp> _Tp& at(Point pt);
    /** @overload
    special versions for 2D arrays (especially convenient for referencing image pixels)
    @param pt Element position specified as Point(j,i) .
    */
    template<typename _Tp> const _Tp& at(Point pt) const;

    /** @brief Returns the matrix iterator and sets it to the first matrix element.

    The methods return the matrix read-only or read-write iterators. The use of matrix iterators is very
    similar to the use of bi-directional STL iterators. In the example below, the alpha blending
    function is rewritten using the matrix iterators:
    @code
        template<typename T>
        void alphaBlendRGBA(const Mat& src1, const Mat& src2, Mat& dst)
        {
            typedef Vec<T, 4> VT;

            const float alpha_scale = (float)std::numeric_limits<T>::max(),
                        inv_scale = 1.f/alpha_scale;

            CV_Assert( src1.type() == src2.type() &&
                       src1.type() == traits::Type<VT>::value &&
                       src1.size() == src2.size());
            Size size = src1.size();
            dst.create(size, src1.type());

            MatConstIterator_<VT> it1 = src1.begin<VT>(), it1_end = src1.end<VT>();
            MatConstIterator_<VT> it2 = src2.begin<VT>();
            MatIterator_<VT> dst_it = dst.begin<VT>();

            for( ; it1 != it1_end; ++it1, ++it2, ++dst_it )
            {
                VT pix1 = *it1, pix2 = *it2;
                float alpha = pix1[3]*inv_scale, beta = pix2[3]*inv_scale;
                *dst_it = VT(saturate_cast<T>(pix1[0]*alpha + pix2[0]*beta),
                             saturate_cast<T>(pix1[1]*alpha + pix2[1]*beta),
                             saturate_cast<T>(pix1[2]*alpha + pix2[2]*beta),
                             saturate_cast<T>((1 - (1-alpha)*(1-beta))*alpha_scale));
            }
        }
    @endcode
     */
    template<typename _Tp> MatIterator_<_Tp> begin();
    template<typename _Tp> MatConstIterator_<_Tp> begin() const;

    /** @brief Returns the matrix iterator and sets it to the after-last matrix element.

    The methods return the matrix read-only or read-write iterators, set to the point following the last
    matrix element.
     */
    template<typename _Tp> MatIterator_<_Tp> end();
    template<typename _Tp> MatConstIterator_<_Tp> end() const;

    /** @brief Runs the given functor over all matrix elements in parallel.

    The operation passed as argument has to be a function pointer, a function object or a lambda(C++11).

    Example 1. All of the operations below put 0xFF the first channel of all matrix elements:
    @code
        Mat image(1920, 1080, CV_8UC3);
        typedef cv::Point3_<uint8_t> Pixel;

        // first. raw pointer access.
        for (int r = 0; r < image.rows; ++r) {
            Pixel* ptr = image.ptr<Pixel>(r, 0);
            const Pixel* ptr_end = ptr + image.cols;
            for (; ptr != ptr_end; ++ptr) {
                ptr->x = 255;
            }
        }

        // Using MatIterator. (Simple but there are a Iterator's overhead)
        for (Pixel &p : cv::Mat_<Pixel>(image)) {
            p.x = 255;
        }

        // Parallel execution with function object.
        struct Operator {
            void operator ()(Pixel &pixel, const int * position) {
                pixel.x = 255;
            }
        };
        image.forEach<Pixel>(Operator());

        // Parallel execution using C++11 lambda.
        image.forEach<Pixel>([](Pixel &p, const int * position) -> void {
            p.x = 255;
        });
    @endcode
    Example 2. Using the pixel's position:
    @code
        // Creating 3D matrix (255 x 255 x 255) typed uint8_t
        // and initialize all elements by the value which equals elements position.
        // i.e. pixels (x,y,z) = (1,2,3) is (b,g,r) = (1,2,3).

        int sizes[] = { 255, 255, 255 };
        typedef cv::Point3_<uint8_t> Pixel;

        Mat_<Pixel> image = Mat::zeros(3, sizes, CV_8UC3);

        image.forEach<Pixel>([&](Pixel& pixel, const int position[]) -> void {
            pixel.x = position[0];
            pixel.y = position[1];
            pixel.z = position[2];
        });
    @endcode
     */
    template<typename _Tp, typename Functor> void forEach(const Functor& operation);
    /** @overload */
    template<typename _Tp, typename Functor> void forEach(const Functor& operation) const;

    Mat(Mat&& m);
    Mat& operator = (Mat&& m);

    enum { MAGIC_VAL  = 0x42FF0000, AUTO_STEP = 0, CONTINUOUS_FLAG = CV_MAT_CONT_FLAG, SUBMATRIX_FLAG = CV_SUBMAT_FLAG };
    enum { MAGIC_MASK = 0xFFFF0000, TYPE_MASK = 0x00000FFF, DEPTH_MASK = 7 };

    /*! includes several bit-fields:
         - the magic signature
         - continuity flag
         - depth
         - number of channels
     */
    int flags;
    //! the matrix dimensionality, >= 2
    int dims;
    //! the number of rows and columns or (-1, -1) when the matrix has more than 2 dimensions
    int rows, cols;
    //! pointer to the data
    uchar* data;

    //! helper fields used in locateROI and adjustROI
    const uchar* datastart;
    const uchar* dataend;
    const uchar* datalimit;

    //! custom allocator
    MatAllocator* allocator;
    //! and the standard allocator
    static MatAllocator* getStdAllocator();
    static MatAllocator* getDefaultAllocator();
    static void setDefaultAllocator(MatAllocator* allocator);

    //! internal use method: updates the continuity flag
    void updateContinuityFlag();

    //! interaction with UMat
    UMatData* u;

    MatSize size;
    MatStep step;

protected:
    template<typename _Tp, typename Functor> void forEach_impl(const Functor& operation);
};
```



 ***由于Mat中的成员太多，我这里就一一讲解***

只要记住Mat为opencv中的表图像的类

那么`openxc`中表示视频的是啥(⊙o⊙)？

它便是`VideoCapture video;`

我们可以对他进行如下操作

`bool ret = video.open("./video.mp4");`

我们定义了一个bool类型，表示 video是否可以被打开 或者 是否存在。

如果存在则返回true不存在则是false





## 初始化之后

那么初始化之后我们干什么呢？？
首先，我们写的是浪漫烟花，那必须有点开场白，不能一上来就放烟花，总得有个介绍什么的

考虑到烟花的浪漫性与**性

**我写了两种开场白**



### 倒计时版本

**此版本适合过年使用，跨年时候使用本特效效果上佳**

```c++
void daoJiShi() 
{
	IMAGE img[6];//定义几张图片 表示倒计时的数字
	char name[64];//每张图片的名字
	for (int i = 0; i < 6; i++) 
    {
        //生成命令
		sprintf(name, "fire/%d.png", i);
		loadimage(&img[i], name);//导入图片
	}

	for (int i = 5; i >= 0; i--) 
    {
        //双缓冲机制
		BeginBatchDraw();//开始绘制
        
		cleardevice();//清除屏幕 相当于system（“cls”）
        //贴图
		putimage((1200 - img[i].getwidth()) / 2, (800 - img[i].getheight()) / 2, &img[i]);
        //结束本次绘图
		EndBatchDraw();
		Sleep(1000);//帧等待
	}
	cleardevice();//清除总屏幕 开始绘制烟花
}
```



### 滚动字幕版本

***

1.0

```c++
	for (int i = 0; i < 50; i++)
	{
		int x = 600 + int(180 * sin(PI * 2 * i / 60));
		int y = 200 + int(180 * cos(PI * 2 * i / 60));
		cleardevice();
		settextstyle(i, 0, "楷体");
		outtextxy(x-80, y, "浪漫表白日");
		outtextxy(x-10, y+100, "献给挚爱某某某");
		Sleep(25);
	}
```



2.0



![image-20220206145632282](F:\markdowm 学习\firework_learning_new\picture\image-20220206145632282.png)



```c++
#define PI 3.1415926
#include <math.h>
//#include ...

void SaySomething()
{
 //模拟字幕运动
    int R = 180;
    int offX = 600;//圆心偏移量
    int offY = 200;//圆心偏移量
    
    for(int a = 90;a >= -210;a-= 6)
    {
        
        int x = offX + R * cos(a / 180.0*PI);
        int y = offY + R * sin(a/180.0 *PI);
        cleardevice();
		settextstyle(（90 - a）/ 300.0* 50, 0, "楷体");
        
		outtextxy(x-80, y, "浪漫表白日");
		outtextxy(x-10, y+100, "献给挚爱***);
		Sleep(25);
        
        //circle(x,y,10);
       // Sleep(1000);//帧等待
        Sleep(20);
}
 	cleardevice();//清除屏幕 准备第二轮字幕
    settextstyle(40, 0, "楷体");
	outtextxy(400, 200, "I LOVE YOU ");
	outtextxy(400, 250, "往后余生是你");
	outtextxy(400, 300, "风雪是你");
	outtextxy(400, 350, "平淡是你");
	outtextxy(400, 400, "清贫是你");
	outtextxy(400, 450, "荣华是你");
	outtextxy(400, 500, "目光所致也是你");
     getchar();
                  cleardevice();//开始绘制烟花
}
```





## 开始放烟花弹-点火

**我们先放一下改好的main函数**

定义一些变量

```c++
	DWORD t1;	// 烟花计时
	DWORD ht1;  // 播放花样计时

```



```c++
int main(void) {
	init();//初始化

    saysomething();//开幕式 字幕 
	 t1 = timeGetTime();	// 烟花计时
	ht1 = timeGetTime();  // 播放花样计时


	BeginBatchDraw();//开始绘制
    //双缓冲机制 让程序更加高效

	// kbhit()判断有没有按键输入
	while (!_kbhit())
	{
		// 帧等待
		Sleep(10);
		clearImage();
		FlushBatchDraw();	// 显示前面的所有绘图操作
 
	}

	return 0;
}
```



**在放烟花之前，我们先写这样一个函数**

我们放烟花，最后总要让烟花消失吧，不然整个屏幕都是烟花的像素，看起来就非常的丑陋

我们还要定义这样一个变量

```c++
DWORD* pMem;// 指向绘图设备的显示缓冲区。
```



```c++
//擦出像素点
void clearImage() {
	for (int i = 0; i < 2000; i++)
	{
		int px1 = rand() % 1200; // 0  to 1199
		int py1 = rand() % 800;  // 0 to 799

		pMem[py1 * 1200 + px1] = BLACK;//将像素点赋值为背景色即为擦除
		pMem[py1 * 1200 + px1 + 1] = BLACK;	// 对显存赋值擦出像素点		
	}
}
```

 

### 选择烟花弹





```c++

void chose(DWORD t1) //t1位为上一次点烟花弹的时间 
{
	DWORD t2 = timeGetTime();
 
	if (t2 - t1 > 100) // 100ms点一次
	{
		int n = rand() % 30; //取模的数字越大，烟花发射频率越慢，因为 <13的概率就越低

		if (n < 13 && bullets[n].shoot == false && fires[n].show == false) //烟花弹不能发射 且 烟花不能show
            
		{
			/**** 重置烟花弹，预备发射 再次初始化数据 *****/
			bullets[n].x = rand() % 1200;
			bullets[n].y = rand() % 100 + 600; // 600-699
			bullets[n].topX = bullets[n].x;
			bullets[n].topY = rand() % 400; // 0 - 399
			bullets[n].height = bullets[n].y - bullets[n].topY;
			bullets[n].shoot = true;//可以发射 

			// 绘制烟花的初始状态（即：在起始位置绘制烟花）
			putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT/* 加这个获取更好的效果* /);

			/**** 播放每个烟花弹的声音 *****/
			char cmd[50];
			sprintf_s(cmd, "play s%d", n);//生成命令
			mciSendString(cmd, 0, 0, 0);//播放发射的音乐
		}
		t1 = t2;//重置时间
	}
}
```



### 测试烟花弹

```c++
void putimage(
int dstX,int dstY,IMAGE*pSrcImg,DWORD dwRop = SRCCOPY
);
```



```c++
void testFire() {
	int n = 5;

	bullets[n].x = 600;
	bullets[n].y = 600;
	bullets[n].topX = 600;
	bullets[n].topY = 200;

	// 绘制烟花的初始状态（即：在起始位置绘制烟花）
	putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);

	while (bullets[n].y > bullets[n].topY) {
		// 擦除
		putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);
		bullets[n].y -= 5;
		// 绘制
		putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);
		Sleep(50);
	}

	 
	 
}
```





![image-20220206153056161](F:\markdowm 学习\firework_learning_new\picture\image-20220206153056161.png)





**XOR模式就是对内存中每个像素的每一位的原值和新值做异或运算**



![image-20220206153640306](F:\markdowm 学习\firework_learning_new\picture\image-20220206153640306.png)



**特点**：

1. 对于0，和任何数x异或，结果都等于x.可实现透明式复制，之拷贝自己有效的数据，空白数据对背景没有影响

2. 对于任何数，和自己异或，结果都是0，可以实现原地擦除

   

## 开始放烟花弹-起飞

```c++

// 烟花弹升空
void shoot() {
	for (int i = 0; i < 13; i++) 
    {
		bullets[i].t2 = timeGetTime();

		if (bullets[i].t2 - bullets[i].t1 > bullets[i].dt && bullets[i].shoot == true) 
        {
			// 擦除
			putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

			// 更新烟花弹的位置和图片状态
			if (bullets[i].y > bullets[i].topY)
            {
				bullets[i].n++;
				bullets[i].y -= 5;
			}

			// 在新位置上，重新绘制
			putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

			/**** 上升到高度的 3 / 4，减速 *****/
			// 即距离最高点还有1/4的时候，减速
			if ((bullets[i].y - bullets[i].topY) * 4 < bullets[i].height)
				bullets[i].dt = rand() % 4 + 10; // 10..13

			/**** 上升到最大高度 *****/
			if (bullets[i].y <= bullets[i].topY) {
				// 擦除烟花弹
				putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

				// 准备渲染“烟花”
				fires[i].x = bullets[i].topX + 10;		// 在烟花弹中间爆炸
				fires[i].y = bullets[i].topY;			// 在最高点绽放
				fires[i].show = true;					// 开始绽放
				bullets[i].shoot = false;				// 停止发射

				 // 关闭点烟花的音效，并播放爆炸的音效, 并重新打开点烟花的音效
				char c1[64], c2[64];
				sprintf_s(c1, "close s%d", i);//生成关闭命令
				sprintf_s(c2, "play f%d", i);
				mciSendString(c1, 0, 0, 0);
				mciSendString(c2, 0, 0, 0);

				sprintf_s(c1, sizeof(c1), "open fire/shoot.mp3 alias s%d", i);
				mciSendString(c1, 0, 0, 0);
			}

			// 更新烟花弹的时间
			bullets[i].t1 = bullets[i].t2;
		}
	}
}
```



## 绽放烟花



```c++
// 绽放烟花
void showFire() {
	// 烟花个阶段绽放时间间隔，制作变速绽放效果
	// 半径越大，绽放越慢
	 
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	for (int i = 0; i < NUM; i++) {
		fires[i].t2 = timeGetTime();

		// 增加爆炸半径，绽放烟花，增加时间间隔做变速效果
		if (fires[i].t2 - fires[i].t1 > fires[i].dt
			&& fires[i].show == true) {
			// 更新烟花半径
			if (fires[i].r < fires[i].max_r) {
				fires[i].r++;
				fires[i].dt = drt[fires[i].r / 10];
				fires[i].draw = true;
			}

			// 销毁烟花，并重新初始化该序号的飞弹和烟花
			if (fires[i].r >= fires[i].max_r) {
				fires[i].draw = false;
				initFire(i);

				// 关闭爆炸音效，并重新打开爆炸音效
				char cmd[64];
				sprintf_s(cmd, "close f%d", i);
				mciSendString(cmd, 0, 0, 0);

				sprintf_s(cmd, sizeof(cmd), "open fire/bomb.wav alias f%d", i);
				mciSendString(cmd, 0, 0, 0);
			}

			// 更新烟花的时间
			fires[i].t1 = fires[i].t2;
		}

		// 绘制指定的烟花
		drawFire(i);
	}
}
```



###  绘制指定的烟花

```c++
void drawFire(int i) {
	if (!fires[i].draw) {
		return;
	}

	// 弧度 PI 3.14  2PI 6.28  360度
	for (double a = 0; a <= 6.28; a += 0.01)  //0-2PI 弧度
	{
		//三角函数
		int x1 = (int)(fires[i].cent2LeftTopX + fires[i].r * cos(a));	// 相对于图片左上角的坐标
		int y1 = (int)(fires[i].cent2LeftTopY - fires[i].r * sin(a));   // 方向和easyx的Y坐标相反

		if (x1 > 0 && x1 < fires[i].width && y1 > 0 && y1 < fires[i].height)	// 只输出图片内的像素点
		{
			int b = fires[i].pix[x1][y1] & 0xff;  //得到三原色的最低字节(B)
			int g = (fires[i].pix[x1][y1] >> 8) & 0xff; //第2个字节
			int r = (fires[i].pix[x1][y1] >> 16);

			// 烟花像素点在窗口上的坐标
			int xx = (int)(fires[i].x + fires[i].r * cos(a));
			int yy = (int)(fires[i].y - fires[i].r * sin(a));

			// 较暗的像素点不输出、防止越界
			//二维数组  当成 一位数组使用的案例 
			//颜色值接近黑色的不输出。
			// 看电影  5排第6个座位： 5*30+6
			if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
				pMem[yy * 1200 + xx] = BGR(fires[i].pix[x1][y1]);	// 显存操作绘制烟花
		}
	}
	fires[i].draw = false;
}

```



#### 数学知识



烟花的任意一点，相当于烟花中心的位置（R x cosA ，R x sinA）



![image-20220206154908409](F:\markdowm 学习\firework_learning_new\picture\image-20220206154908409.png)





烟花的任意一点，相对于图片的左上角位置:(cent2LeftTopX+Rxcos,cent2LeftTopY - RxsinA)

![image-20220206155136985](F:\markdowm 学习\firework_learning_new\picture\image-20220206155136985.png)







## 特效

绘制一个心形

```c++
void heartFire(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	static bool flag = false;
	static DWORD startTime = 0;

	if (flag && st2 - startTime > 3500) {
		putimage(430, 250, &head);
		flag = false;
	}

	if (st2 - st1 > 20000)		// 20秒
	{
		flag = true;
		startTime = timeGetTime();
		// 先擦除正在发送的烟花弹
		for (int i = 0; i < 13; i++) {
			if (bullets[i].shoot)
				putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);
		}


		// 心形坐标
		int x[13] = { 600, 750, 910, 1000, 950, 750, 600, 450, 250, 150, 250, 410, 600 };
		int y[13] = { 650, 530, 400, 220, 50, 40, 200, 40, 50, 220, 400, 530, 650 };
		for (int i = 0; i < NUM; i++)
		{
			bullets[i].x = x[i];
			bullets[i].y = y[i] + 750;  //每个烟花弹的发射距离都是750，确保同时爆炸
			bullets[i].topX = x[i];
			bullets[i].topY = y[i];


			bullets[i].height = bullets[i].y - bullets[i].topY;
			bullets[i].shoot = true;
			bullets[i].dt = 7;
			// 显示烟花弹
			putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

			/**** 设置烟花参数 ***/
			fires[i].x = bullets[i].x + 10;
			fires[i].y = bullets[i].topY;
			fires[i].show = false;
			fires[i].r = 0;


		}
		st1 = st2;
	}
}
```

![image-20220206155647084](F:\markdowm 学习\firework_learning_new\picture\image-20220206155647084.png)

## 实现main函数

~~~c++
int main(void) {
	init();

 
    //此处添加开幕式
	DWORD t1 = timeGetTime();	// 筛选烟花计时
	DWORD ht1 = timeGetTime();  // 播放花样计时

	BeginBatchDraw();
 
	 while (!_kbhit())
	{
		// 帧等待
		Sleep(10);

		clearImage();

		chose(t1); //点火
		shoot(); //升空
		showFire();
		heartFire(ht1);

		FlushBatchDraw();	// 显示前面的所有绘图操作
 
	}

	return 0;
}
~~~





# 全部代码



```c++
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include<string>
#include <mmsystem.h>
#pragma comment ( lib, "Winmm.lib" )


#define PI 3.14
#define NUM 13

DWORD* pMem;

IMAGE head;

 
struct Fire
{
	int r;					 
	int max_r;				 
	int x, y;				 
	int cent2LeftTopX, cent2LeftTopY;		 
	int width, height;		  
	int pix[240][240];		 
	bool show;				 
	bool draw;				 
	DWORD t1, t2, dt;		 
}fires[NUM];


struct Bullet
{
	int x, y;				
	int topX, topY;			
	int height;				
	bool shoot;		
    DWORD t1, t2, dt;
	IMAGE img[2];			 
	unsigned char n : 1;	 
}bullets[NUM];




// 初始化指定的烟花和烟花弹
void initFire(int i)
{
	// 分别为：烟花中心到图片边缘的最远距离、烟花中心到图片左上角的距离 (x、y) 两个分量
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	/**** 初始化烟花 *****/
	fires[i].x = 0;				// 烟花中心坐标
	fires[i].y = 0;
	fires[i].width = 240;				// 图片宽
	fires[i].height = 240;				// 图片高
	fires[i].max_r = r[i];				// 最大半径
	fires[i].cent2LeftTopX = x[i];				// 中心距左上角距离
	fires[i].cent2LeftTopY = y[i];
	fires[i].show = false;			// 是否绽放
	fires[i].dt = 5;				// 绽放时间间隔
	fires[i].t1 = timeGetTime();
	fires[i].r = 0;				// 从 0 开始绽放
	fires[i].draw = false;

	/**** 初始化烟花弹 *****/
	//timeGetTime 该时间为从系统开启算起所经过的时间,单位：毫秒
	bullets[i].t1 = timeGetTime();
	bullets[i].dt = rand() % 10;		// 发射速度时间间隔
	bullets[i].n = 0;				// 烟花弹闪烁图片下标
	bullets[i].shoot = false;			// 是否发射
}

// 加载图片
void loadFireImages()
{
	/**** 储存烟花的像素点颜色 ****/
	IMAGE fm, gm;
	loadimage(&fm, "fire/flower.jpg");

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm, i * 240, 0, 240, 240);

		SetWorkingImage(&gm);
		for (int a = 0; a < 240; a++)
			for (int b = 0; b < 240; b++)
				fires[i].pix[a][b] = getpixel(a, b);
	}

	/**** 加载烟花弹 ************/
	IMAGE sm;
	loadimage(&sm, "fire/shoot.jpg");

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&sm);
		int n = rand() % 5; //0..4

		getimage(&bullets[i].img[0], n * 20, 0, 20, 50);			// 暗
		getimage(&bullets[i].img[1], (n + 5) * 20, 0, 20, 50);		// 亮
	}

	//设置绘图设备为默认绘图窗口，就是当前游戏窗口
	SetWorkingImage();		// 设置回绘图窗口
}

void drawFire(int i) {
	if (!fires[i].draw) {
		return;
	}

	// 弧度 PI 3.14  2PI 6.28  360度
	for (double a = 0; a <= 6.28; a += 0.01)  //0-2PI 弧度
	{
		//三角函数
		int x1 = (int)(fires[i].cent2LeftTopX + fires[i].r * cos(a));	// 相对于图片左上角的坐标
		int y1 = (int)(fires[i].cent2LeftTopY - fires[i].r * sin(a));   // 方向和easyx的Y坐标相反

		if (x1 > 0 && x1 < fires[i].width && y1 > 0 && y1 < fires[i].height)	// 只输出图片内的像素点
		{
			int b = fires[i].pix[x1][y1] & 0xff;  //得到三原色的最低字节(B)
			int g = (fires[i].pix[x1][y1] >> 8) & 0xff; //第2个字节
			int r = (fires[i].pix[x1][y1] >> 16);

			// 烟花像素点在窗口上的坐标
			int xx = (int)(fires[i].x + fires[i].r * cos(a));
			int yy = (int)(fires[i].y - fires[i].r * sin(a));

			// 较暗的像素点不输出、防止越界
			//二维数组  当成 一位数组使用的案例 
			//颜色值接近黑色的不输出。
			// 看电影  5排第6个座位： 5*30+6
			if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
				pMem[yy * 1200 + xx] = BGR(fires[i].pix[x1][y1]);	// 显存操作绘制烟花
		}
	}
	fires[i].draw = false;
}


// C++的引用
void chose(DWORD t1) //t1位为上一次点烟花弹的时间
{
	DWORD t2 = timeGetTime();

	if (t2 - t1 > 100) // 100ms点一次
	{
		int n = rand() % 30; //取摸的数字越大，烟花发射频率越慢，因为<13的概率就越低

		if (n < 13 && bullets[n].shoot == false && fires[n].show == false)
		{
			/**** 重置烟花弹，预备发射 *****/
			bullets[n].x = rand() % 1200;
			bullets[n].y = rand() % 100 + 600; // 600-699
			bullets[n].topX = bullets[n].x;
			bullets[n].topY = rand() % 400; // 0.399
			bullets[n].height = bullets[n].y - bullets[n].topY;
			bullets[n].shoot = true;

			// 绘制烟花的初始状态（即：在起始位置绘制烟花）
			putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);

			/**** 播放每个烟花弹的声音 *****/
			char cmd[50];
			sprintf_s(cmd, "play s%d", n);
			mciSendString(cmd, 0, 0, 0);
		}
		t1 = t2;
	}
}


// 项目初始化
void init() {
	// 创建窗口
	initgraph(1200, 800);

	// 播放背景音乐
	mciSendString("play fire/ring.mp3 repeat", 0, 0, 0);

	for (int i = 0; i < NUM; i++) {	// 初始化烟花和烟花弹
		initFire(i);
	}

	loadFireImages();

	// 这个函数用于获取绘图设备的显示缓冲区指针。
	pMem = GetImageBuffer();		// 获取窗口显存指针


	// 打开音效并设置别名
	char cmd[128];
	for (int i = 0; i < 13; i++) {
		sprintf_s(cmd, sizeof(cmd), "open fire/shoot.mp3 alias s%d", i);
		mciSendString(cmd, 0, 0, 0); // 打开13次

		sprintf_s(cmd, sizeof(cmd), "open fire/bomb.wav alias f%d", i);
		mciSendString(cmd, 0, 0, 0); // 打开13次
	}

	loadimage(&head, "fire/head.png", 400, 300, true);
}

void clearImage() {
	for (int i = 0; i < 2000; i++)
	{
		int px1 = rand() % 1200; // 0..1199
		int py1 = rand() % 800;  // 0.799

		pMem[py1 * 1200 + px1] = BLACK;
		pMem[py1 * 1200 + px1 + 1] = BLACK;	// 对显存赋值擦出像素点		
	}
}


// 烟花弹升空
void shoot() {
	for (int i = 0; i < 13; i++) {
		bullets[i].t2 = timeGetTime();

		if (bullets[i].t2 - bullets[i].t1 > bullets[i].dt && bullets[i].shoot == true) {
			// 擦除
			putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

			// 更新烟花弹的位置和图片状态
			if (bullets[i].y > bullets[i].topY) {
				bullets[i].n++;
				bullets[i].y -= 5;
			}

			// 在新位置上，重新绘制
			putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

			/**** 上升到高度的 3 / 4，减速 *****/
			// 即距离最高点还有1/4的时候，减速
			if ((bullets[i].y - bullets[i].topY) * 4 < bullets[i].height)
				bullets[i].dt = rand() % 4 + 10; // 10..13

			/**** 上升到最大高度 *****/
			if (bullets[i].y <= bullets[i].topY) {
				// 擦除烟花弹
				putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

				// 准备渲染“烟花”
				fires[i].x = bullets[i].topX + 10;		// 在烟花弹中间爆炸
				fires[i].y = bullets[i].topY;			// 在最高点绽放
				fires[i].show = true;					// 开始绽放
				bullets[i].shoot = false;				// 停止发射

				 // 关闭点烟花的音效，并播放爆炸的音效, 并重新打开点烟花的音效
				char c1[64], c2[64];
				sprintf_s(c1, "close s%d", i);
				sprintf_s(c2, "play f%d", i);
				mciSendString(c1, 0, 0, 0);
				mciSendString(c2, 0, 0, 0);

				sprintf_s(c1, sizeof(c1), "open fire/shoot.mp3 alias s%d", i);
				mciSendString(c1, 0, 0, 0);
			}

			// 更新烟花弹的时间
			bullets[i].t1 = bullets[i].t2;
		}
	}
}



void showFire() {
	// 烟花个阶段绽放时间间隔，制作变速绽放效果
	// 为什么数组大小定义为16？
	// 目前烟花的最大半径是155，准备以半径/10可刻度，不同的半径，绽放速度不同
	// 半径越大，绽放越慢
	//              10 20 30 40 50 
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	for (int i = 0; i < NUM; i++) {
		fires[i].t2 = timeGetTime();

		// 增加爆炸半径，绽放烟花，增加时间间隔做变速效果
		if (fires[i].t2 - fires[i].t1 > fires[i].dt
			&& fires[i].show == true) {
			// 更新烟花半径
			if (fires[i].r < fires[i].max_r) {
				fires[i].r++;
				fires[i].dt = drt[fires[i].r / 10];
				fires[i].draw = true;
			}

			// 销毁烟花，并重新初始化该序号的飞弹和烟花
			if (fires[i].r >= fires[i].max_r) {
				fires[i].draw = false;
				initFire(i);

				// 关闭爆炸音效，并重新打开爆炸音效
				char cmd[64];
				sprintf_s(cmd, "close f%d", i);
				mciSendString(cmd, 0, 0, 0);

				sprintf_s(cmd, sizeof(cmd), "open fire/bomb.wav alias f%d", i);
				mciSendString(cmd, 0, 0, 0);
			}

			// 更新烟花的时间
			fires[i].t1 = fires[i].t2;
		}

		// 绘制指定的烟花
		drawFire(i);
	}
}


void heartFire(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	static bool flag = false;
	static DWORD startTime = 0;

	if (flag && st2 - startTime > 3500) {
		putimage(430, 250, &head);
		flag = false;
	}

	if (st2 - st1 > 20000)		// 20秒
	{
		flag = true;
		startTime = timeGetTime();
		// 先擦除正在发送的烟花弹
		for (int i = 0; i < 13; i++) {
			if (bullets[i].shoot)
				putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);
		}


		// 心形坐标
		int x[13] = { 600, 750, 910, 1000, 950, 750, 600, 450, 250, 150, 250, 410, 600 };
		int y[13] = { 650, 530, 400, 220, 50, 40, 200, 40, 50, 220, 400, 530, 650 };
		for (int i = 0; i < NUM; i++)
		{
			bullets[i].x = x[i];
			bullets[i].y = y[i] + 750;  //每个烟花弹的发射距离都是750，确保同时爆炸
			bullets[i].topX = x[i];
			bullets[i].topY = y[i];


			bullets[i].height = bullets[i].y - bullets[i].topY;
			bullets[i].shoot = true;
			bullets[i].dt = 7;
			// 显示烟花弹
			putimage(bullets[i].x, bullets[i].y, &bullets[i].img[bullets[i].n], SRCINVERT);

			/**** 设置烟花参数 ***/
			fires[i].x = bullets[i].x + 10;
			fires[i].y = bullets[i].topY;
			fires[i].show = false;
			fires[i].r = 0;


		}
		st1 = st2;
	}
}


void daoJiShi() {
	IMAGE img[6];
	char name[64];
	for (int i = 0; i < 6; i++) {
		sprintf(name, "fire/%d.png", i);
		loadimage(&img[i], name);
	}

	for (int i = 5; i >= 0; i--) {
		BeginBatchDraw();
		cleardevice();
		putimage((1200 - img[i].getwidth()) / 2, (800 - img[i].getheight()) / 2, &img[i]);
		EndBatchDraw();
		Sleep(1000);
	}
	cleardevice();
}

int main(void) {
	init();

	daoJiShi();

	DWORD t1 = timeGetTime();	// 筛选烟花计时
	DWORD ht1 = timeGetTime();  // 播放花样计时

	BeginBatchDraw();

	// kbhit()判断有没有按键输入
	while(1)//while (!_kbhit())
	{
		// 帧等待
		Sleep(10);

		clearImage();

		chose(t1); //点火
		shoot(); //升空
		showFire();
		heartFire(ht1);

		FlushBatchDraw();	// 显示前面的所有绘图操作

		 
	}

	return 0;
}
```



一些测试函数

```c++

void testFire() {
	int n = 5;

	bullets[n].x = 600;
	bullets[n].y = 600;
	bullets[n].topX = 600;
	bullets[n].topY = 200;

	// 绘制烟花的初始状态（即：在起始位置绘制烟花）
	putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);

	while (bullets[n].y > bullets[n].topY) {
		// 擦除
		putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);
		bullets[n].y -= 5;
		// 绘制
		putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);
		Sleep(50);
	}

	// 先擦除烟花弹
	putimage(bullets[n].x, bullets[n].y, &bullets[n].img[bullets[n].n], SRCINVERT);

	fires[n].show = true;
	fires[n].x = bullets[n].x + 10;
	fires[n].y = bullets[n].y;
	while (fires[n].r <= fires[n].max_r) {
		fires[n].draw = true;
		drawFire(n);
		fires[n].r++;
		Sleep(10);
	}
}
```



 # 我的另一个版本



由于代码过多，原理几乎一样，我这里就只给出源代码，你们需要素材的替换即可



```c++
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
```





```c++
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>		
#pragma comment ( lib, "Winmm.lib" )

/***** 宏定义区 ******/

#define NUM		13			// 烟花种类数量宏定义
#define PI      3.1415926548

/***** 结构定义区 **********/

// 烟花结构
struct FIRE
{
	int r;					// 当前爆炸半径
	int max_r;				// 爆炸中心距离边缘最大半径
	int x, y;				// 爆炸中心在窗口的坐标
	int cen_x, cen_y;		// 爆炸中心相对图片左上角的坐标
	int width, height;		// 图片的宽高
	int xy[240][240];		// 储存图片像素点

	bool show;				// 是否绽放
	bool draw;				// 开始输出像素点
	DWORD t1, t2, dt;		// 绽放速度
}Fire[NUM];

// 烟花弹结构
struct JET
{
	int x, y;				// 喷射点坐标
	int hx, hy;				// 最高点坐标------将赋值给 FIRE 里面的 x, y
	int height;				// 烟花高度
	bool shoot;				// 是否可以发射

	DWORD t1, t2, dt;		// 发射速度
	IMAGE img[2];			// 储存花弹一亮一暗图片
	byte n : 1;				// 图片下标
}Jet[NUM];


/**** 函数申明区 ****/

void welcome();
void Init(int);		// 初始化烟花
void Load();		// 加载烟花图片
void Shoot();		// 发射烟花
void Chose(DWORD&);		// 筛选烟花
void Style(DWORD&);		// 发射样式
void Show(DWORD*);		// 绽放烟花


// 主函数
void main()
{
	initgraph(1200, 800);
	srand(time(0));

	// 播放背景音乐
	mciSendString("open ./fire/小幸运.mp3 alias bk", 0, 0, 0);
	mciSendString("play bk repeat", 0, 0, 0);

	welcome();

	DWORD t1 = timeGetTime();			// 筛选烟花计时
	DWORD st1 = timeGetTime();			// 播放花样计时
	DWORD* pMem = GetImageBuffer();		// 获取窗口显存指针

	for (int i = 0; i < NUM; i++)		// 初始化烟花
	{
		Init(i);
	}
	Load();								// 将烟花图片信息加载进相应结构中
	BeginBatchDraw();					// 开始批量绘图

	while (!kbhit())
	{
		Sleep(10);

		// 随机选择 4000 个像素点擦除
		for (int clr = 0; clr < 1000; clr++)
		{
			for (int j = 0; j < 2; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 800;

				if (py1 < 799)				// 防止越界
					pMem[py1 * 1200 + px1] = pMem[py1 * 1200 + px1 + 1] = BLACK;	// 对显存赋值擦出像素点
			}
		}
		Chose(t1);			// 筛选烟花
		Shoot();			// 发射烟花
		Show(pMem);			// 绽放烟花
		Style(st1);			// 花样发射
		FlushBatchDraw();	// 显示前面的所有绘图操作
	}
}


void welcome()
{
	//setfillstyle(0);
	setcolor(YELLOW);
	
	for (int i = 0; i < 50; i++)
	{
		int x = 600 + int(180 * sin(PI * 2 * i / 60));
		int y = 200 + int(180 * cos(PI * 2 * i / 60));
		cleardevice();
		settextstyle(i, 0, "楷体");
		outtextxy(x-80, y, "浪漫表白日");
		outtextxy(x-10, y+100, "献给挚爱某某某");
		Sleep(25);
	}

	getchar();
	cleardevice();
	settextstyle(25, 0, "楷体");
	outtextxy(400, 200, "原来你是我最想留住的幸运");
	outtextxy(400, 250, "原来我们和爱情曾经靠得那么近");
	outtextxy(400, 300, "那为我对抗世界的决定");
	outtextxy(400, 350, "那陪我淋的雨");
	outtextxy(400, 400, "一幕幕都是你");
	outtextxy(400, 450, "一尘不染的真心。");
	outtextxy(600, 500, "----《小幸运》");

	
	getchar();
}

// 初始化烟花参数
void Init(int i)
{
	// 分别为：烟花中心到图片边缘的最远距离、烟花中心到图片左上角的距离 (x、y) 两个分量
	int r[13] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[13] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[13] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	/**** 初始化烟花 *****/

	Fire[i].x = 0;				// 烟花中心坐标
	Fire[i].y = 0;
	Fire[i].width = 240;				// 图片宽
	Fire[i].height = 240;				// 图片高
	Fire[i].max_r = r[i];				// 最大半径
	Fire[i].cen_x = x[i];				// 中心距左上角距离
	Fire[i].cen_y = y[i];
	Fire[i].show = false;			// 是否绽放
	Fire[i].dt = 5;				// 绽放时间间隔
	Fire[i].t1 = timeGetTime();
	Fire[i].r = 0;				// 从 0 开始绽放

	/**** 初始化烟花弹 *****/

	Jet[i].x = -240;				// 烟花弹左上角坐标
	Jet[i].y = -240;
	Jet[i].hx = -240;				// 烟花弹发射最高点坐标
	Jet[i].hy = -240;
	Jet[i].height = 0;				// 发射高度
	Jet[i].t1 = timeGetTime();
	Jet[i].dt = rand() % 10;		// 发射速度时间间隔
	Jet[i].n = 0;				// 烟花弹闪烁图片下标
	Jet[i].shoot = false;			// 是否发射
}


// 加载图片
void Load()
{
	/**** 储存烟花的像素点颜色 ****/
	IMAGE fm, gm;
	loadimage(&fm, "./fire/flower.jpg", 3120, 240);

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&fm);
		getimage(&gm, i * 240, 0, 240, 240);
		SetWorkingImage(&gm);

		for (int a = 0; a < 240; a++)
		for (int b = 0; b < 240; b++)
			Fire[i].xy[a][b] = getpixel(a, b);
	}

	/**** 加载烟花弹 ************/
	IMAGE sm;
	loadimage(&sm, "./fire/shoot.jpg", 200, 50);

	for (int i = 0; i < 13; i++)
	{
		SetWorkingImage(&sm);
		int n = rand() % 5;

		getimage(&Jet[i].img[0], n * 20, 0, 20, 50);			// 暗
		getimage(&Jet[i].img[1], (n + 5) * 20, 0, 20, 50);		// 亮
	}


	SetWorkingImage();		// 设置回绘图窗口
}


// 在一定范围内筛选可发射的烟花，并初始化发射参数，输出烟花弹到屏幕，播放声音
void Chose(DWORD& t1)
{
	DWORD t2 = timeGetTime();

	if (t2 - t1 > 100)
	{
		int n = rand() % 20;

		if (n < 13 && Jet[n].shoot == false && Fire[n].show == false)
		{
			/**** 重置烟花弹，预备发射 *****/
			Jet[n].x = rand() % 1200;
			Jet[n].y = rand() % 100 + 600;
			Jet[n].hx = Jet[n].x;
			Jet[n].hy = rand() % 400;
			Jet[n].height = Jet[n].y - Jet[n].hy;
			Jet[n].shoot = true;
			putimage(Jet[n].x, Jet[n].y, &Jet[n].img[Jet[n].n], SRCINVERT);

			/**** 播放每个烟花弹的声音 *****/
			/*char c1[50], c2[30], c3[30];
			sprintf(c1, "open ./fire/shoot.mp3 alias s%d", n);
			sprintf(c2, "play s%d", n);
			sprintf(c3, "close n%d", n);

			mciSendString(c3, 0, 0, 0);
			mciSendString(c1, 0, 0, 0);
			mciSendString(c2, 0, 0, 0);*/
		}
		t1 = t2;
	}
}


//扫描烟花弹并发射
void Shoot()
{
	for (int i = 0; i < 13; i++)
	{
		Jet[i].t2 = timeGetTime();

		if (Jet[i].t2 - Jet[i].t1 > Jet[i].dt && Jet[i].shoot == true)
		{
			/**** 烟花弹的上升 *****/
			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);

			if (Jet[i].y > Jet[i].hy)
			{
				Jet[i].n++;
				Jet[i].y -= 5;
			}

			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);

			/**** 上升到高度的 3 / 4，减速 *****/
			if ((Jet[i].y - Jet[i].hy) * 4 < Jet[i].height)
				Jet[i].dt = rand() % 4 + 10;

			/**** 上升到最大高度 *****/
			if (Jet[i].y <= Jet[i].hy)
			{
				// 播放爆炸声
				/*char c1[50], c2[30], c3[30];
				sprintf(c1, "open ./fire/bomb.wav alias n%d", i);
				sprintf(c2, "play n%d", i);
				sprintf(c3, "close s%d", i);

				mciSendString(c3, 0, 0, 0);
				mciSendString(c1, 0, 0, 0);
				mciSendString(c2, 0, 0, 0);*/

				putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);	// 擦掉烟花弹
				Fire[i].x = Jet[i].hx + 10;											// 在烟花弹中间爆炸
				Fire[i].y = Jet[i].hy;												// 在最高点绽放
				Fire[i].show = true;					// 开始绽放
				Jet[i].shoot = false;					// 停止发射

			}
			Jet[i].t1 = Jet[i].t2;
		}
	}
}



//显示花样
void Style(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	if (st2 - st1 >20000)		// 一首歌的时间
	{
		// 心形坐标
		int x[13] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int y[13] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };
		for (int i = 0; i < NUM; i++)
		{
			//cleardevice();
			/**** 规律分布烟花弹 ***/
			Jet[i].x = x[i] * 10;
			Jet[i].y = (y[i] + 75) * 10;
			Jet[i].hx = Jet[i].x;
			Jet[i].hy = y[i] * 10;
			Jet[i].height = Jet[i].y - Jet[i].hy;
			Jet[i].shoot = true;
			Jet[i].dt = 7;
			putimage(Jet[i].x, Jet[i].y, &Jet[i].img[Jet[i].n], SRCINVERT);	// 显示烟花弹

			/**** 设置烟花参数 ***/
			Fire[i].x = Jet[i].x + 10;
			Fire[i].y = Jet[i].hy;
			Fire[i].show = false;
			Fire[i].r = 0;

			/**** 播放发射声音 ***/
			/*char c1[50], c2[30], c3[30];
			sprintf(c1, "open ./fire/shoot.mp3 alias s%d", i);
			sprintf(c2, "play s%d", i);
			sprintf(c3, "close n%d", i);

			mciSendString(c3, 0, 0, 0);
			mciSendString(c1, 0, 0, 0);
			mciSendString(c2, 0, 0, 0);*/
		}
		st1 = st2;
	}
}


// 绽放烟花
void Show(DWORD* pMem)
{
	// 烟花个阶段绽放时间间隔，制作变速绽放效果
	int drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 55 };

	for (int i = 0; i < NUM; i++)
	{
		Fire[i].t2 = timeGetTime();

		// 增加爆炸半径，绽放烟花，增加时间间隔做变速效果
		if (Fire[i].t2 - Fire[i].t1 > Fire[i].dt && Fire[i].show == true)
		{
			if (Fire[i].r < Fire[i].max_r)
			{
				Fire[i].r++;
				Fire[i].dt = drt[Fire[i].r / 10];
				Fire[i].draw = true;
			}

			if (Fire[i].r >= Fire[i].max_r - 1)
			{
				Fire[i].draw = false;
				Init(i);
			}
			Fire[i].t1 = Fire[i].t2;
		}

		// 如果该号炮花可爆炸，根据当前爆炸半径画烟花，颜色值接近黑色的不输出。
		if (Fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)  //0-2PI 弧度
			{
				//三角函数
				int x1 = (int)(Fire[i].cen_x + Fire[i].r * cos(a));				// 相对于图片左上角的坐标
				int y1 = (int)(Fire[i].cen_y - Fire[i].r * sin(a));

				if (x1 > 0 && x1 < Fire[i].width && y1 > 0 && y1 < Fire[i].height)	// 只输出图片内的像素点
				{
					int b = Fire[i].xy[x1][y1] & 0xff;
					int g = (Fire[i].xy[x1][y1] >> 8) & 0xff;
					int r = (Fire[i].xy[x1][y1] >> 16);

					// 烟花像素点在窗口上的坐标
					int xx = (int)(Fire[i].x + Fire[i].r * cos(a));
					int yy = (int)(Fire[i].y - Fire[i].r * sin(a));

					// 较暗的像素点不输出、防止越界
					//二维数组  当成 一位数组使用的案例 
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800)
						pMem[yy * 1200 + xx] = BGR(Fire[i].xy[x1][y1]);	// 显存操作绘制烟花
				}
			}
			Fire[i].draw = false;
		}
	}
}
```



# 项目地址 

加我QQ：1481458358

有任何问题都可以问我，欢迎讨论学习。



声明：以上图文来源与网络，若有侵权请联系删除。

我的博客



[C++编写浪漫烟花 - 心怡，欣怡。 - 博客园 (cnblogs.com)](https://www.cnblogs.com/lxy5201314/p/15371136.html)

