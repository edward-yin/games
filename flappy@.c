#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int bottom,left; //scale
int b_x,b_y;//bird position
int bar1_x,bar1_ytop,bar1_ydown;//
int bar2_x,bar2_ytop,bar2_ydown;
int score;
void gotoxy(int x,int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

void HideCursor()//hide cursor 
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup() //initialize
{
	bottom = 30;
	left = 60;
	b_x = left/3;
	b_y = bottom/3;
	bar1_x = 0;
	bar1_ytop = 10;
	bar1_ydown = 16;
	bar2_x = bar1_x + 30;
	bar2_ytop = 16;
	bar2_ydown = 22;		
	score = 0;
}

void show()
{
	HideCursor();
	gotoxy(0,0);
	//system("cls");
	int i,j;
	
	for (i=0;i<bottom;i++)
	{
		for (j=0;j<left;j++)
		{
			if ((i == b_y)&&(j == b_x))
				printf("@");
			else if ((j == bar1_x)&&((i<=bar1_ytop)||(i>=bar1_ydown)))
				printf("*");
			else if ((j == bar2_x)&&((i<=bar2_ytop)||(i>=bar2_ydown)))
				printf("*");
			else 
				printf(" ");
		}
		printf("|\n");
	}

	for (j=0;j<left;j++)
	{
		printf("_");
	}
	printf("|\nscroe: %d\n",score);
}

void updateWithoutInput()
{
	b_y++;
	bar1_x--;
	bar2_x--; 
	Sleep(100);
	
	if ((b_x == bar1_x)||(b_x == bar2_x))
	{
		if (((b_y>bar1_ytop)&&(b_y<bar1_ydown))||((b_y>bar2_ytop)&&(b_y<bar2_ydown)))
		{
			score++;
		}
		else 
		{
			printf("GAME OVER");
			system("pause");
			exit(0);
			
		}
	}
	
	if (bar1_x<=0)
	{
		bar1_x = left;
		int temp = rand()%(int)(bottom*0.8);
		bar1_ydown = temp + bottom/10;
		bar1_ytop = temp - bottom/10;
	}
	if (bar2_x<=0)
	{
		bar2_x = left;
		int temp = rand()%(int)(bottom*0.8);
		bar2_ydown = temp + bottom/10;
		bar2_ytop = temp - bottom/10;
	}
	
	 
}

void updateWithInput()
{
	char input;
	if (kbhit())
	{
		input = getch();
		if (input == ' ')
		{
			b_y = b_y - 4;
		}
	}
}


int main()
{
	startup();  // initialize	
	while (1)  
	{
		show();  
		updateWithoutInput(); 
		updateWithInput();    
	}
}
