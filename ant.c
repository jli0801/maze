#include <stdio.h>
#include <string.h>
#include "ant.h"
#define MAX_SIZEA 500 
//all methods 
int xCoor;
int yCoor;

int numRow;
int numCol;

int itchR; // 0 for no itch and anything above 0 represents the number of steps 
int itchL;
int itchF; //forwards
int itchB; //backwards
int energy; 

int steps; //how many cells/elements did we cover 

static int coordinates[MAX_SIZEA][MAX_SIZEA];

int mazeMain[MAX_SIZEA][MAX_SIZEA];
int top = 0;
//update the coordinates in the ant.c file
//everytime we move, send the coordinates back 
void setEnergy(int en)
{
	energy = en;
}

int getEnergy()
{
	return energy;
}

int compareCoor(int exitX, int exitY)
{
	//1 is not equal
	//0 is equal 
	if(getX() != exitX && getY() != exitY)
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

void mazeSetup(int **m)
{
	int i = 0;
	int j = 0;
	for( i = 0; i < numRow; i++)
	{
		for (j = 0; j < numCol; j++)
		{
			mazeMain[i][j] = m[i][j];
		}
	}
}

void setCoord(int x, int y)
{
	xCoor = x;
	yCoor = y;
}

void setMaxRow(int row)
{
	numRow = row;
}

void setMaxCol(int col)
{
	numCol = col;
}

int getX()
{
	return xCoor;	
}
int getY()
{
	return yCoor;
}

void mvf()
{
	if((xCoor+1) < numRow) //highest you could go the row or the column 
	{
		xCoor++;
		steps++;
		setEnergy(getEnergy() - 3);
	}
}
void mvb()
{
	if(xCoor != 0) //lowest you could go is (0,0)
	{
		xCoor--;
		steps++;
		setEnergy(getEnergy() - 3);
	}
}
void mvl()
{
	if(yCoor != 0)
	{
		yCoor--;
		steps++;
		setEnergy(getEnergy() - 3);
	}
}
void mwr()
{
	if((yCoor+1) < numCol)
	{
		yCoor++;
		steps++;
		setEnergy(getEnergy() - 3);
	}
}
//for the c__ methods you need to look at the maze and the location of the ant
void cwl() 
{
	int leftCounter = -1;
	int left = 1;
	while(mazeMain[getX()][getY()-left] == 0)
	{
		left++;
		leftCounter++;
	}	
	if(leftCounter == -1)
	{
		itchL = 0; 
	}
	else
	{
		itchL = left;
	}
	setEnergy(getEnergy() - 1);
}
void cwr()
{
	int rightCounter = -1;
	int right = 1;
	while(mazeMain[getX()][getY()+right] == 0) //0 means open 
	{
		right++;
		rightCounter++;
	}
	if(rightCounter == -1)
	{
		//means the next one is a wall 
		itchR = 0;
	}
	else
	{
		itchR = right;
	}

	setEnergy(getEnergy() - 1);
}
void cwf()
{
		int forwardCounter = -1;
			int forward = 1;
			while(mazeMain[getX()+forward][getY()] == 0) //0 means open 
			{
				forward++;
				forwardCounter++;
			}
			if(forwardCounter == -1)
			{
				//means the next one is a wall 
				itchF = 0;
			}
			else
			{
				itchF = forward;
			}
	setEnergy(getEnergy() - 1);
}
void cwb()
{
	int backCounter = -1;
	int back = 1;
	while(mazeMain[getX()-back][getY()] == 0) //0 means open 
	{
		back++;
		backCounter++;
	}
	if(backCounter == -1)
	{
		//means the next one is a wall 
	itchB = 0;
	}
	else
	{
		itchB = back;
	}
	setEnergy(getEnergy() - 1);
}
//push pop clear peek are from the stacks.h file

int isemptyA () {

   if (top == 0)
      return 1;
   else
      return 0;
}
   
int isfullA () {

   if (top == MAX_SIZEA)
      return 1;
   else
      return 0;
}

int peekA () {
  if (!(isempty()))
  {
	return coordinates[top - 1];
}
  else 
  {
  	printf ("Stack is empty\n");
  }
  	setEnergy(getEnergy() - 2);
}

int popA () {
   int data[2][1] = {{getX()}, {getY()}};

   if (isempty() != 1) //its one now B/C it still needs to pop one out 
   {
     
      top = top--;   
      return data;
   } 
   else
	{
      printf("Error: Stack is empty\n");
  	}
      
    setEnergy(getEnergy() - 4);
}

void pushA () {
	int data[2][1] = {getX(), getY()}; //current location 
   if (isfull() == 0)
   {
   		top++; //add on more ontop
		coordinates[top][0] = data[1][0];
		coordinates[top][1] = data[1][1];
   }
    else 
    {
    	printf("Error: Stack is full\n");
	}
	setEnergy(getEnergy() - 4);

void clearA () {
	top = 0;
	
	setEnergy(getEnergy() - 2);
}
//end of stack methods 

void bjpi() //xposition
{
	//jump x position along the direction
	//for until ant hits a wall aka maze [x] == 1
	if(itchL > 0)
	{
		int left = itchL;
		for (left = itchL; left < 0; left--)
		{
			mvl();
			setEnergy(getEnergy() - 5);
		}
	}
	else if(itchR > 0)
	{
		int right = itchR;
		for (right = itchR; right < 0; right--)
		{
			mvr();
			setEnergy(getEnergy() - 5);
		}	
	}
	else if(itchF > 0)
	{
		int forward = itchF;
		for (forward = itchF; forward < 0; forward--)
		{
			mvf();
			setEnergy(getEnergy() - 5);
		}
	}
	else if(itchB > 0)
	{
		int back = itchB;
		for (back = itchB; back < 0; back--)
		{
			mvb();
			setEnergy(getEnergy() - 5);
		}
	
	}
	jpitx();
}

void jpitx() //stops the iteching of the ant 
{	
		itchL = 0; //reset 
		itchR = 0; //reset
		itchF = 0; //reset	
		itchB = 0; //reset 
}
void cjpi() //moves one position
{
	if(itchL > 0)
	{
		mvl();
	}
	else if(itchR > 0)
	{
		mvr();
	}
	else if(itchF > 0 )
	{
		mvf();
	}
	else if(itchB > 0)
	{
		mvb();
	}
	jpitx();
	setEnergy(getEnergy() - 3);
}
void rpNt(int n, int t) //n amount of times 
{
	//for the push pop peek clear, call stacks.h
	//t is the next whatever actions 
	char nextActions[MAX_SIZEA][MAX_SIZEA];
	int j = 0;
	for(j = 0; j < t; j++)
	{
		//nextActions[j] = pop();
		strcpy(nextActions[j], pop());
	}
	int i = 0;
	int k = 0;
	for(i = 0; i < n; i++)
	{
		//identify the action 
		for (k = 0; k < t; k++)
		{
			if(strcmp(nextActions[k], "mvf") == 0)
			{
				mvf();
			}
			else if (strcmp(nextActions[k], "mvb") == 0)
			{
				mvb();
			}
			else if (strcmp(nextActions[k], "mvl") == 0)
			{
				mvl();
			}
			else if (strcmp(nextActions[k], "mwr") == 0)
			{
				mwr();	
			}
			else if (strcmp(nextActions[k], "cwl") == 0)
			{
				cwl();			
			}
			else if (strcmp(nextActions[k], "cwr") == 0)
			{
				cwr();
			}
			else if (strcmp(nextActions[k], "cwf") == 0)
			{
				cwf();
			}
			else if (strcmp(nextActions[k], "cwb") == 0)
			{
				cwb();
			}
			else if (strcmp(nextActions[k], "push") == 0)
			{
				pushA();
			}
			else if (strcmp(nextActions[k], "pop") == 0)
			{
				//refers to the pop in this c file 
				popA();
			}
			else if (strcmp(nextActions[k], "peek") == 0)
			{
				peekA();
			}
			else if (strcmp(nextActions[k], "clear") == 0)
			{
				clearA();
			}
			else if (strcmp(nextActions[k], "bjpi") == 0)
			{
				bjpi();
			}
			else if (strcmp(nextActions[k], "cjpi") == 0)
			{
				cjpi();
			}
		}
	}
}
}
	
