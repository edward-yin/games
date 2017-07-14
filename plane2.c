#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


int p_x,p_y;//position of the plane
int b_x,b_y;//position of the bullet
int e_x,e_y;//enemy
int height,width;//scale
int score,miss;
int m,n;

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
    height = 20;
    width = 30;
    p_x = width/2;
    p_y = height-3;
    b_x = p_x;
    b_y = -2;
    e_x = p_x;
    e_y = 0;
    score = 0;
    miss = 0;
}

void show()
{
    HideCursor();
	gotoxy(0,0);
    //system("cls");
    int i,j;
    for (i=0;i<height;i++)
    {
        for (j=0;j<=width;j++)
        {
            if ((i == p_y)&&(j == p_x))
            { 
                //printf("*");//plane
                		
				printf("*");
				//j = j+2;
			}
			else if ((i == p_y+1)&&(j == p_x-1))
			{
				printf("***");
				j = j+2;
			}
            else if ((i == e_y)&&(j == e_x))
                printf("@");//enemy
            else if ((i == b_y)&&(j == b_x))
                printf("|");//bullet
            else if (j == width)
				printf("||");
            else 
                printf(" ");
        }
        printf("\n");
    }
    printf("SCORE %d\n",score);
    printf("MISS %d\n",miss);
}


void updateWithoutInput()  //update without input
{
    if (b_y>-1)
        b_y--;
        
        
    if ((b_y == e_y)&&(b_x == e_x))//shoot down enemy
    {
        score++;
        e_y = -1;
        e_x = rand()%width;
        b_y = -2;
    }
    
    if (e_y > height)//enemy out of scale
    {
        //new enemy
        e_y = -1;
        e_x = rand()%width;
        miss++;
    }   
        
    static int v = 0;
    if (v < 15)
        v++;
    if (v == 15)
    {
        e_y++;
        v = 0;
    }
}

void updateWithInput()
{
    char input;
    if (kbhit())
    {
        input = getch();
        if ((input == 'a')&&(p_x > 0))   
			p_x--;  // move left
		if ((input == 'd')&&(p_x < width-1))
			p_x++;  // move right
		if ((input == 'w')&&(p_y > 0))
			p_y--;  // move up
		if ((input == 's')&&(p_y < height-1))
			p_y++;  // move down
		if (input == ' ')  // shoot
		{
			b_y = p_y-1;  // the initial position is over the plane
			b_x = p_x;
		}
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
