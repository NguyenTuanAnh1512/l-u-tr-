#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define consoleWidth 25
#define consoleHeight 25

using namespace std;

int inputKey()
{
	if (_kbhit())
	{
		int key = _getch();

		if (key == 224)	// special key
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	

	
}

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;                  
	HANDLE	hConsoleOut;
	COORD	Home = {0,0};
	DWORD	dummy;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

	FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}


void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

enum TrangThai {UP, DOWN, LEFT, RIGHT};


struct ToaDo
{
	int x,y;
};


struct HoaQua
{
	ToaDo td;
};



struct KieuSnake
{
	ToaDo dot[40];
	int n;
	TrangThai tt;
};


void DieuKhien_DiChuyen (KieuSnake &snake)
{
	//truyen trang thai cho dot cu
	for (int i = snake.n - 1; i > 0; i--)
		snake.dot[i] = snake.dot[i-1];
		
	if (kbhit())   //phat hien co phim nhan vao
	{
		int key = _getch();
		if(key == 75)
			snake.tt = LEFT;
		else if(key == 77)
			snake.tt = RIGHT;
		else if(key == 72)
			snake.tt = UP;
		else if(key == 80)
			snake.tt = DOWN;
	}
	
	if(snake.tt == UP)
		snake.dot[0].y--;
	else if(snake.tt ==DOWN)
		snake.dot[0].y++;
	else if(snake.tt ==LEFT)
		snake.dot[0].x--;
	else if(snake.tt ==RIGHT)
		snake.dot[0].x++;	
}


void HienThi (KieuSnake snake , HoaQua hq)
{
	clrscr();
	
	for(int i=0 ; i<consoleHeight ; i++)
	{
		gotoXY (consoleWidth , i);
		putchar(178);
	}
	
	gotoXY (hq.td.x , hq.td.y);
	cout<<"O";
	
	for(int i=0; i < snake.n; i++)
	{
		gotoXY (snake.dot[i].x, snake.dot[i].y);
		cout<<"*";
	}
}


void KhoiTao (KieuSnake &snake , HoaQua &hq)
{
	snake.n = 3;
	snake.dot[0].x = 2;
	snake.dot[0].y = 0;
	snake.dot[0].x = 1;
	snake.dot[0].y = 0;
	snake.dot[0].x = 0;
	snake.dot[0].y = 0;
	snake.tt = RIGHT;
	
	
	hq.td.x = 10;
	hq.td.y = 10;
}


void XuLy (KieuSnake &snake , HoaQua &hq)
{
	if ( snake.dot[0].x == hq.td.x && snake.dot[0].y == hq.td.y)
	{
		//an duoc hoa qua
		for (int i = snake.n;i>0;i--)
			snake.dot[i] = snake.dot[i-1];
			
		snake.n++;
		
		if(snake.tt == UP)
			snake.dot[0].y--;
		else if(snake.tt ==DOWN)
			snake.dot[0].y++;
		else if(snake.tt ==LEFT)
			snake.dot[0].x--;
		else if(snake.tt ==RIGHT)
			snake.dot[0].x++;	
			
			
		hq.td.x = rand() % consoleWidth;
		hq.td.y = rand() % consoleHeight;
	}
	
	
}


int main()
{
	srand(time(NULL));
	KieuSnake snake;
	HoaQua hq;
	KhoiTao (snake , hq);
	
	while(1)
	{
		//hien thi
		HienThi (snake , hq);
		//dieu kien
		DieuKhien_DiChuyen (snake);
		//xu li game
		XuLy (snake , hq);
		//game over
		
		
		Sleep(80);
	}
	return 0;
}
