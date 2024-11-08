// Бібліотеки
#include <iostream>
#include<conio.h>
#include <winbgim.h>
#include<math.h>

// Клавіші
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ROTX 100
#define ROTY 119
#define ROTZ 97
#define MAGNIFICATION 120
#define REDUCTION 122

using namespace std;

struct Dot3d // Структура, яка представляє точки в пам'яті ПК
{
	double x, y, z;
};
	Dot3d Plane[32];//Масив точок
	int Rebro = 30;// Довжина ребра
	int Rebra [48][2] = //Масив, який об'єднує певні точки між собою
	{
		{0,1},{1,2},{2,3},{3,0},{2,4},{1,5},{0,6},{3,7},{4,5},{6,5},{6,7},{7,4},
		{4,8},{5,9},{8,10},{10,11},{11,12},{12,13},{13,14},{14,15},{8,9},{13,10},
		{8,14},{9,15},{9,16},{16,17},{17,18},{18,19},{19,16},{19,15},{7,20},
		{6,21},{14,23},{15,22},{20,23},{21,22},{24,25},{25,31},{31,30},{30,24},
		{24,29},{29,28},{28,25},{25,26},{26,27},{27,24},{23,22},{20,21}
	};
	
int Krok = 10;
int Size = 1;
int Mx, My;

int AngleX = 0;
int AngleY = 0;
int AngleZ = 0;

void InitPlane(int x1, int y1, int z1, int m);
void PaintPlane(Dot3d * c);

void OffsetPlaneHorizontal(int);
void OffsetPlaneVertical(int);
void rotationX(int);
void rotationZ(int);
void rotationY(int);
void ResizePlus(int);
void ResizeMinus(int);

int main(int argc, char** argv) 
{	
    char menu;
    //Відкриття графічного вікна
    initwindow(1600, 1000);
    //Початкове розміщення об'єкту
    Mx = getmaxx()/2;;
    My = getmaxy()/2;;
    
	//Меню
	setcolor (14);
	outtextxy (80,20,"ГЕОМЕТРИЧНЕ ПЕРЕТВОРЕННЯ ЛIТАКА");
	setcolor (3);
	outtextxy (40,60,"Виберiть один iз наступних пунктiв меню:");
	setcolor (10);
	outtextxy (40,90,"1 - Демонстрацiя фiгури");
	setcolor (9);
	outtextxy (40,110,"2 - Довiдка");
	setcolor (1);
	outtextxy (40,130,"3 - Про автора");
	setcolor (4);
	outtextxy (40,150,"4 - Вихід");
	
	//Пункти меню 
	while (true)
	{	
		menu = getch();
		
		switch (menu)
		{
			case '1':
			{
				cleardevice( );
				InitPlane (Mx / 100, My / 100, 0 , Rebro);
				PaintPlane (Plane);
				
				while (true)
				{
					char action; // Дія
					action = getch();
		
					switch (action)
					{
						case ESC:
						{
							return 0;
							break;	
						}	
						case LEFT:
						{
							OffsetPlaneHorizontal(-Krok);
							break;	
						}	
						case RIGHT:
						{
							OffsetPlaneHorizontal(Krok);
							break;	
						}	
						case UP:
						{
							OffsetPlaneVertical(-Krok);
							break;	
						}	
						case DOWN:
						{
							OffsetPlaneVertical(Krok);
							break;	
						}	
						case ROTX:
						{
							rotationX(5);
							break;	
						}
						case ROTY:
						{
							rotationY(5);
							break;	
						}	
						case ROTZ:
						{
							rotationZ(5);
							break;	
						}	
						case MAGNIFICATION:
						{
							ResizePlus(Size);
							break;	
						}	
						case REDUCTION:
						{
							ResizeMinus(Size);
							break;	
						}
					}
				}
			}
			
			case '2':
			{
				cleardevice( );
				setcolor (3);
				outtextxy (88,0,"Довідка:");
				setcolor (10);
				outtextxy (80,20,"Керування:");
				setcolor (11);
				outtextxy (10,50,"Стрілки - переміщення фігури;");
				outtextxy (10,80,"z - зменшення фігури;");
				outtextxy (10,100,"x - збільшення фігури;");
				outtextxy (10,130,"a - обертання фігури по осі Z;");
				outtextxy (10,150,"w - обертання фігури по осі Y;");
				outtextxy (10,170,"d - обертання фігури по осі X;");
				setcolor (4);
				outtextxy (10,200,"ESC - вихід з програми;");
				setcolor (8);
				outtextxy (10,230,"Для коректної роботи в програмі мову потрібно змінити на англійську.");
				getch ();
				return 0;
				break;
			}
			case '3':
			{
				cleardevice( );
				setcolor (1); 
				outtextxy (165,20,"Програму створив");
				outtextxy (150,50,"студент групи КН-23");
				outtextxy (120,80,"Росоха Максим Валентинович");
				getch ();
				return 0;
				break;
			}
			case '4':
			{
				return 0;
				break;
			}	
		}
	}
    return 0;
}
//Масив з координатими точок		
void InitPlane(int x1, int y1, int z1, int m)
{
	Plane[0].x = x1;							Plane[0].y = y1;							Plane[0].z = z1;
	Plane[1].x = Plane[0].x;					Plane[1].y = Plane[0].y - m;				Plane[1].z = Plane[0].z;
	Plane[2].x = Plane[0].x;					Plane[2].y = Plane[0].y - m;				Plane[2].z = Plane[0].z - m;
	Plane[3].x = Plane[0].x;					Plane[3].y = Plane[0].y;					Plane[3].z = Plane[0].z - m;
	Plane[4].x = Plane[0].x + 3 * m;			Plane[4].y = Plane[0].y - 2 * m;			Plane[4].z = Plane[0].z - m;
	Plane[5].x = Plane[0].x + 3 * m;			Plane[5].y = Plane[0].y - 2 * m;			Plane[5].z = Plane[0].z;
	Plane[6].x = Plane[0].x + 3 * m;			Plane[6].y = Plane[0].y + m;				Plane[6].z = Plane[0].z;
	Plane[7].x = Plane[0].x + 3 * m;			Plane[7].y = Plane[0].y + m;				Plane[7].z = Plane[0].z - m;
	Plane[8].x = Plane[0].x + 6 * m;			Plane[8].y = Plane[0].y - 2 * m;			Plane[8].z = Plane[0].z - m;
	Plane[9].x = Plane[0].x + 6 * m;			Plane[9].y = Plane[0].y - 2 * m;			Plane[9].z = Plane[0].z;
	Plane[10].x = Plane[0].x + 8 * m;			Plane[10].y = Plane[0].y - 2 * m;			Plane[10].z = Plane[0].z - 5 * m;
	
	Plane[11].x = Plane[0].x + 14 * m;			Plane[11].y = Plane[0].y - 2 * m;			Plane[11].z = Plane[0].z - 12 * m;
	Plane[12].x = Plane[0].x + 15 * m;			Plane[12].y = Plane[0].y - 2 * m;			Plane[12].z = Plane[0].z - 12 * m;
	Plane[13].x = Plane[0].x + 12 * m;			Plane[13].y = Plane[0].y - 2 * m;			Plane[13].z = Plane[0].z - 5 * m;
	Plane[14].x = Plane[0].x + 11 * m;			Plane[14].y = Plane[0].y - 2 * m;			Plane[14].z = Plane[0].z - m;
	Plane[15].x = Plane[0].x + 11 * m;			Plane[15].y = Plane[0].y - 2 * m;			Plane[15].z = Plane[0].z;
	Plane[16].x = Plane[0].x + 8 * m;			Plane[16].y = Plane[0].y - 2 * m;			Plane[16].z = Plane[0].z + 4 * m;
	Plane[17].x = Plane[0].x + 14 * m;			Plane[17].y = Plane[0].y - 2 * m; 			Plane[17].z = Plane[0].z + 11 * m;
	Plane[18].x = Plane[0].x + 15 * m;			Plane[18].y = Plane[0].y - 2 * m;			Plane[18].z = Plane[0].z + 11 * m;
	Plane[19].x = Plane[0].x + 12 * m;			Plane[19].y = Plane[0].y - 2 * m;			Plane[19].z = Plane[0].z + 4 * m;
	Plane[20].x = Plane[0].x + 11 * m;			Plane[20].y = Plane[0].y + m;				Plane[20].z = Plane[0].z - m;
	Plane[21].x = Plane[0].x + 11 * m;			Plane[21].y = Plane[0].y + m;				Plane[21].z = Plane[0].z;
	Plane[22].x = Plane[0].x + 22 * m;			Plane[22].y = Plane[0].y - 2 * m;			Plane[22].z = Plane[0].z;
	
	Plane[23].x = Plane[0].x + 22 * m;			Plane[23].y = Plane[0].y - 2 * m;			Plane[23].z = Plane[0].z - m;
	Plane[24].x = Plane[0].x + 19 * m;			Plane[24].y = Plane[0].y - 2 * m;			Plane[24].z = Plane[0].z - m/2;
	Plane[25].x = Plane[0].x + 22 * m;			Plane[25].y = Plane[0].y - 2 * m;			Plane[25].z = Plane[0].z - m/2;
	Plane[26].x = Plane[0].x + 24 * m;			Plane[26].y = Plane[0].y - 2 * m;			Plane[26].z = Plane[0].z + m;
	Plane[27].x = Plane[0].x + 22 * m;			Plane[27].y = Plane[0].y - 2 * m;			Plane[27].z = Plane[0].z + m;
	Plane[28].x = Plane[0].x + 24 * m;			Plane[28].y = Plane[0].y - 2 * m;			Plane[28].z = Plane[0].z - 2 * m;
	Plane[29].x = Plane[0].x + 22 * m;			Plane[29].y = Plane[0].y - 2 * m;			Plane[29].z = Plane[0].z - 2 * m;
	Plane[30].x = Plane[0].x + 22 * m;			Plane[30].y = Plane[0].y - 6 * m;			Plane[30].z = Plane[0].z - m/2;
	Plane[31].x = Plane[0].x + 24 * m;			Plane[31].y = Plane[0].y - 6 * m;			Plane[31].z = Plane[0].z - m/2;
}

void PaintPlane(Dot3d * c)
{
	int yt1, yt2, xt1, xt2, zt1, zt2;

	double anX = (AngleX % 360 / 360.0) * 3.14 * 2;
	double anY = (AngleY % 360 / 360.0) * 3.14 * 2;
	double anZ = (AngleZ % 360 / 360.0) * 3.14 * 2;
	
	// Малювання фігури
	for (int i = 0; i < 48; i++)
	{

		xt1 =  (c[Rebra[i][0]].x);
		yt1 =  (c[Rebra[i][0]].y) * cos(anX) + c[Rebra[i][0]].z * sin(anX);
		zt1 = -(c[Rebra[i][0]].y) * sin(anX) + c[Rebra[i][0]].z * cos(anX);
		
		xt2 =  (c[Rebra[i][1]].x);
		yt2 =  (c[Rebra[i][1]].y) * cos(anX) + c[Rebra[i][1]].z * sin(anX);
		zt2 = -(c[Rebra[i][1]].y) * sin(anX) + c[Rebra[i][1]].z * cos(anX);
		
		xt1 =  xt1 * cos(anY) + zt1 * sin(anY);
		yt1 =  yt1;
		zt1 = -xt1 * sin(anY) + zt1 * cos(anY);
		
		xt2 =  xt2 * cos(anY) + zt2 * sin(anY);
		yt2 =  yt2;
		zt2 = -xt2 * sin(anY) + zt2 * cos(anY);
		
		xt1 =  xt1 * cos(anZ) - yt1 * sin(anZ);
		yt1 = -xt1 * sin(anZ) + yt1 * cos(anZ);
		zt1 =  zt1;
		
		xt2 =  xt2 * cos(anZ) - yt2 * sin(anZ);
		yt2 = -xt2 * sin(anZ) + yt2 * cos(anZ);
		zt2 =  zt2;
		
		// Колір фігури (синій)
		setcolor(1);
		// Малювання ліній
		line (xt1 + Mx, yt1 + My, xt2 + Mx, yt2 + My);
	}	
}

// Переміщення фігури по горизонталі
void OffsetPlaneHorizontal(int m)
{
	for(int i = 0; i < 32; i++)
	{
		Plane[i].x = Plane[i].x + m;
		cleardevice();
		PaintPlane(Plane);
	}
}

// Переміщення фігури по вертикалі
void OffsetPlaneVertical(int m)
{
	for(int i = 0; i < 32; i++)
	{
		Plane[i].y = Plane[i].y + m;
		cleardevice();
		PaintPlane(Plane);
	}
}

// Обертання фігури по осі X
void rotationX(int m)
{
	AngleX += m;
	cleardevice();
	InitPlane(Plane[0].x, Plane[0].y, Plane[0].z, Rebro);
	PaintPlane(Plane);
}

// Обертання фігури по осі Y
void rotationY(int m)
{
	AngleY += m;
	cleardevice();
	InitPlane(Plane[0].x, Plane[0].y, Plane[0].z, Rebro);
	PaintPlane(Plane);
}

// Обертання фігури по осі Z
void rotationZ(int m)
{
	AngleZ += m;
	cleardevice();
	InitPlane(Plane[0].x, Plane[0].y, Plane[0].z, Rebro);
	PaintPlane(Plane);
}

// Збільшення фігури
void ResizePlus(int m)
{
	Rebro += m;
	cleardevice();
	InitPlane(Plane[0].x, Plane[0].y, Plane[0].z, Rebro);
	PaintPlane(Plane);
}

// Зменшення фігури
void ResizeMinus(int m)
{
	Rebro -= m;
	cleardevice();
	InitPlane(Plane[0].x, Plane[0].y, Plane[0].z, Rebro);
	PaintPlane(Plane);
}
