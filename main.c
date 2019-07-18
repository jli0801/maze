#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stacks.h"
#include "ant.h"

//stack is for movements 
//there is another stack within ANT for his coordinates 

#define max 100
#define max_energy 1500
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*typedef struct ant
{
	int xCoor;
	int yCoor;
	int energy;
	int itch;
	int coveredMaze;
	void(*setEnergy)(ant *self, int newEnergy);
	void(*setXCoor)(ant *self, int xCoor);
	void(*setYCoord)(ant *self, int yCoor);
	void(*setCoveredMaze)(ant *self, int coveredMaze); //can be used as a statistics FOR THE ANT 
}antM;*/

int symbolCheck(char symb)
{
	if(symb == '-' || symb == '|')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void removeChar(char* source, char* removeC)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(strcmp(i, removeC) != 0)
    {
    	i++;
	}
  }
  *i = 0;
}

int nextSpace(char* string)
{
	int c = 0;
	int space = -1;
	//when we find the first space we're gonna skip it
	//i only want the index of the second space
	for( c = 0; c < strlen(string) ; c++)
	{
		if(string[c] == ' ')
		{
			space = c;
		}
	}	
	return space;
}

int  getSubString(char *target, char *source,int from, int to)
{
	int length = 0;
	int i = 0,j = 0;
	
	//get length
	while(source[i++]!='\0')
		length++;
	
	if(from<0 || from>length){
		printf("Invalid \'from\' index\n");
		return 1;
	}
	if(to>length){
		printf("Invalid \'to\' index\n");
		return 1;
	}	
	
	for(i=from,j=0;i<=to;i++,j++){
		target[j]=source[i];
	}
	
	//assign NULL at the end of string
	target[j]='\0'; 
	
	return 0;	
}

int main(int argc, char *argv[]) {
	FILE *f; 
	
	char c, lines[max][max];
	int maze[max][max];
	//rows then the columns 
	int startX, startY, exitX, exitY, NR_COL, NR_ROW = 0;
	//get the number of rows and cols before creating maze  
	
	int iX =0;
	int jY = 0;//for creating the maze

	if ((f = fopen ("maze.txt", "r")) == NULL) 
	{
       printf ("File %s cannot be opened\n", "maze.txt");
       return 1;
       //ends program with a one!
	}
	
	//read the first character of the file'
	c = fgetc (f);
	//EOF = END OF FILE
	//keeps reading character before the file ends
	
	
	//hard code the first four lines ot get entrance, exit, row, col
	int lineNum = 0; 
	while (c != EOF) 
	{	
	    while (c == '\n') //indicates new line 
		{ //logic or 
	        c = fgetc(f);
	    }
		
		while(!(lineNum ==5))
		{
			fgets(lines[lineNum], max, f);
			lineNum++;
		}
		//the first four lines are in lines[][]
		//str.erase(remove(str.begin(), str.end(), ' '), str.end());
		//str.erase(remove(str.begin(), str.end(), '='), str.end());
		char tempXstart[3]; //will be converted into an integer later 
		char tempYstart[3]; 
		
		char tempXexit[3];
		char tempYexit[3];
		int i = 0;
		for(i = 0; i < 2; i++) //0 and 1 
		{
		//	lines[i].erase(remove(lines[i].begin(), lines[i].end(), ' '), lines[i].end());
		//	lines[i].erase(remove(lines[i].begin(), lines[i].end(), '='), lines[i].end());
		removeChar(lines[i], " ");
		removeChar(lines[i], "=");
			//start0,12 exit9,5
		//from the last char to the comma - x
		//from the commma to the end ((sizeof(lines.[lineNum]))) - y 
			if(strstr(lines[i], "/start/") != NULL)
			{
				int indexComma = strchr(lines[i], ',') - lines[i];
				//the next number is the x 
				getSubString(tempXstart, lines[i], lines[i] + strlen("start"),sizeof(lines[i]) - indexComma);
				//strncpy(tempXstart, lines[i] + strlen("start"), sizeof(lines[i]) - indexComma);
				//comma to the last number is the y 
				getSubString(tempYstart, lines[i], indexComma,sizeof(lines[i]));
				//strncpy(tempYstart, sizeof(lines[i]) - indexComma, sizeof(lines[i]));
				
				startX = atoi(tempXstart);
				startY = atoi(tempYstart);
			}
			else if (strstr(lines[i], "/exit/") != NULL)
			{
				//the next number is x 
				//last number is y 
				int indexComma = strchr(lines[i], ',') - lines[i];
				//the next number is the x 
				//strncpy(tempXexit, lines[i] + strlen("start"), sizeof(lines[i]) - indexComma);
				getSubString(tempXexit, lines[i], lines[i] + strlen("start"),sizeof(lines[i]) - indexComma);
				//comma to the last number is the y 
				//strncpy(tempYexit, sizeof(lines[i]) - indexComma, sizeof(lines[i]));
				getSubString(tempYexit, lines[i],indexComma,sizeof(lines[i]));
				
				exitX = atoi(tempXexit);
				exitY = atoi(tempYexit);
			}
		}
		//number of columns and rows 
		char tempCol[3]; //3 for a three digit number 
		char tempRow[3]; //in char from the array and then converted to NR_COL and NR_Row 
		for(i = 2; i < 4; i++)
		{
		//	lines[i].erase(remove(lines[i].begin(), lines[i].end(), ' '), lines[i].end());
		//	lines[i].erase(remove(lines[i].begin(), lines[i].end(), '='), lines[i].end());
		removeChar(lines[i], " ");
		removeChar(lines[i], "=");
			if(strstr(lines[i], "/NR_COLUMNS/") != NULL) 
			{
			//starting point -> lines[i][strlen("NR_COLUMNS")]
			//end point -> lines[i][strlen(lines[i])]
			//strncpy(dest, src + beginIndex, endIndex - beginIndex);
			//strncpy(tempCol, lines[i] + strlen("NR_COLUMNS"), sizeof(lines[i]) - strlen("NR_COLUMNS"));
			getSubString(tempCol, lines[i], lines[i] + strlen("NR_COLUMNS"),sizeof(lines[i]) - strlen("NR_COLUMNS"));
			NR_COL = atoi(tempCol); //into an integer 
			}
			else if (strstr(lines[i], "/NR_ROW/") != NULL)
			{
			//strncpy(tempRow, lines[i] + strlen("NR_ROW"), sizeof(lines[i]) - strlen("Nr_ROWS"));
			getSubString(tempRow, lines[i], lines[i] + strlen("NR_ROWS"),sizeof(lines[i]) - strlen("NR_ROWS"));
			NR_ROW = atoi(tempRow); //into an integer 
			}
		}
		setMaxRow(NR_ROW);
		setMaxCol(NR_COL);
		//for column and row: from the last char to the end (sizeof(lines.[lineNum]))
		
		//every single character 
		c = fgetc(f);
	    //for maze 
	    
	//   	int maze[NR_ROW][NR_COL];
		for (iX = 0; iX < NR_ROW; iX++)
		{
			for (jY = 0; jY < NR_COL; jY++)
			{
				if(c == ' ')
			    {
			    	maze[iX][jY] = 0;
				}
				if(symbolCheck(c) == 1) //blocked by wall 
				{
					maze[iX][jY] = 1;
				}
				else
				{
					maze[iX][jY] = 0;
				}
			}
		}
	    
		//keep in mind the columns and rows for incrementing iX and jY
	}
	fclose(f);
	//"local" maze 
	//int mazeInit[NR_ROW][NR_COL]; //empty 
	
	//intelligence
	char v, actions[max];
	int index = 0;
	FILE *f_brain;
	if ((f_brain = fopen ("brain.txt", "r")) == NULL) 
	{
       printf ("File %s cannot be opened\n", "brain.txt");
       return 1;
       //ends program with a one!
	}
	
	v = fgetc(f_brain);
	while(v != EOF)
	{
		while (v == ' ' || v == '/n')
		{
			v = fgetc(f_brain);
		}
		if((v >= 'a' && v <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			while((v >= 'a' && v <= 'z') || (c >= 'A' && c <= 'Z'))
			{
				actions[index++] = v;
				v = fgetc(f_brain);
			}
		}
		actions[index] = '\0';
		index = 0;
		push(actions);
	}
	fclose(f_brain);
	//POP EVERY STRING INTO HIS STACK so he knows what to do 
	
	//actual game play(?)
	setEnergy(max_energy);
	setMaxRow(NR_ROW);
	setMaxCol(NR_COL);
	setCoor(startX, startY);
	
	//1 is not equal and 0 is equal 
	while (getEnergy() > 0 && (compareCoor(exitX, exitY) == 1) && (isempty() == 0))
	{
		//the stack is done 
		//we want to pop and make the ant do whatever the action is 
		char actionAnt[max];
		
		strncpy(actionAnt[max], peek(), sizeof(pop()));
		//char actionAnt[max] = pop();
		//analyze the action and call appropriate method 
		
		//we need to analyze the maze 
		mazeSetup(maze);
		if (strcmp(actionAnt, "cwl") == 0)
		{
		cwl();
		}
		else if (strcmp(actionAnt, "cwr") == 0)
		{
			//check y+1
			cwr();
			
		}
		else if (strcmp(actionAnt, "cwf") == 0)
		{
			//check x+1
		cwf();
		}
		else if (strcmp(actionAnt, "cwb") == 0)
		{
			//check x-1
		cwb();
		}
		else if(strcmp(actionAnt, "mvf") == 0)
		{
			mvf();
		}
		else if (strcmp(actionAnt, "mvb") == 0)
		{
			mvb();
		}
		else if (strcmp(actionAnt, "mvl") == 0)
		{
			mvl();
		}
		else if (strcmp(actionAnt, "mwr") == 0)
		{
			mwr();	
		}
		else if (strcmp(actionAnt, "push") == 0)
		{
			pushA();
		}
		else if (strcmp(actionAnt, "pop") == 0)
		{
			//refers to the pop in this c file 
			popA();
		}
		else if (strcmp(actionAnt, "peek") == 0)
		{
			peekA();
		}
		else if (strcmp(actionAnt, "clear") == 0)
		{
			clearA();
		}
		else if (strcmp(actionAnt, "bjpi") == 0)
		{
			bjpi();
		}
		else if (strcmp(actionAnt, "cjpi") == 0)
		{
			cjpi();
		}
		else if (strstr(actionAnt, "RN ") != NULL)
		{
			//RN n t 
			//actionAnt + strlen("RN ") 
			int nextBlank = nextSpace(actionAnt);
			int nPass = -1;
			int tPass = -1;
			char actionN[max];
			//strncpy(actionN, actionAnt + strlen("RN "), 
			getSubString(actionN, actionAnt, actionAnt + strlen("RN "),sizeof(actionAnt) - nextBlank);
			//where N ends + 1 for space 
			// to the end 
			char timesT[max];
			getSubString(timesT, actionAnt, nextBlank , sizeof(actionAnt));
			
			nPass = atoi(actionN);
			tPass = atoi(timesT);
		}
	}	
	FILE *f_write = fopen("results.txt", "ab+");
	if(f_write)
	{
		printf("The current energy is %d", getEnergy());
		printf("The ant is currently at %d, %d.", getX(), getY());
		if(compareCoor(exitX, exitY) == 1)
		{
			//ant found the exit 
			printf("He found his way out!");
			return 1;
		}
		if(getEnergy() <= 0 )
		{
			//they died 
			printf("He lost his energy!");
			//maybe print his location 
			return 1;
		}
		if (isEmpty() == 1)
		{
			//no more moves 
			printf("He ran out of moves!");
			return 1;
		}
	}
	
	
	
	return 0;
}
