#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include<windows.h> 

int p_x,p_y;
int b_x,b_y;//position of the ball
int v_x,v_y;
int buttom,right;
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
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);//hide cursor
}

void startup()
{
	buttom = 25;
	right = 50;
	p_x = rand()%right;
	p_y = buttom-1;
	b_x = p_x + 1;
	b_y = buttom - 2;
	v_x = (rand()%3)+1;
	v_y = -1;
	score = 0;
	 
}

void show()
{
    HideCursor();
	gotoxy(0,0);
    //system("cls");
    int i,j;
    for (i=0;i<buttom;i++)
    {
        for (j=0;j<=right;j++)
        {
        	if ((i == b_y)&&(j == b_x))
        	{
        		printf("o");
        		//j = j+2;
        	}
        		
        	else if ((i == p_y)&&(j == p_x))
        		printf("*");
        	else if ((i == p_y)&&(j == p_x+1))
        		printf("*");
			else if ((i == p_y)&&(j == p_x+2))
        		printf("*");
			else if ((i == p_y)&&(j == p_x+3))
        		printf("*");
			else if (j == right)
				printf("|");	
        	else 
        		printf(" ");
        }
        printf("\n");
    }
    printf("SCORE %d\n",score);
    
}

void updateWithoutInput()  //update without input
{
	static int v = 0;
    if (v < 10)
        v++;
    if (v == 10)
    {
        b_x = b_x+v_x;
        b_y = b_y+v_y;
        v = 0;
    }
	
	if ((b_x +v_x) <= 0)
	{
		b_x = 0;
		v_x = -v_x;
	}
		
	if ((b_x + v_x)>=right-1)
	{
		b_x = right-1;
		v_x = -v_x;
	}
		
	if ((b_y + v_y)<= 0)
	{
		b_y = 0;
		v_y = -v_y;
	}
		
	if (((b_y +v_y) >= p_y-1)&&((p_x <= b_x)&&(b_x <= p_x+3)))
	{
		b_y = p_y-1;
		v_y = -v_y;
		score = score + 1;
	}
		
		
	//out 
	if ((b_y > p_y)&&((p_x > b_x)||(b_x > p_x+3)))
	{
		b_x = p_x + 1;
		b_y = buttom - 2;
		v_x = (rand()%3)+1;
		v_y = -1;
	}
	
}

void updateWithInput()
{
	char input;
    if (kbhit())
    {
        input = getch();
        if ((input == 'a')&&(p_x > 0))   
			p_x--;  //move left
		if ((input == 'd')&&(p_x < right-4))
			p_x++; //move right
	}
}


int main()
{
	startup();  //initialize
	while (1) //start in loop
	{
		show();  //show the interface
		updateWithoutInput(); 
		updateWithInput();  
		//Sleep(100);
   	}
}
