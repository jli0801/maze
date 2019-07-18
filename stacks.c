#include <stdio.h>
#include "stacks.h"
#define MAX_SIZE 200 
static char stack [MAX_SIZE][MAX_SIZE]; //first is number of strings
//second is the length of strings 
int top = 0;     //MAKE THE END OF THE ARRAY TO BE THE TOP 
//GLOBAL BOI 

//TOP IS OUR TRACKERS FOR THE STACK 

//integer stack
int isempty () {

   if (stack[top] == "" || stack[top] == NULL || top == 0)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if (top == MAX_SIZE)
      return 1;
   else
      return 0;
}

char peek () 
{
  if (!(isempty()))
   return *stack[top - 1];
  else 
  	printf ("Stack is empty\n");
}

char pop () {
char data[MAX_SIZE];
   if (isempty() != 1) //its one now B/C it still needs to pop one out 
   {
      
      strncpy(data, stack[top-1], sizeof(stack[top-1]));
      top = top - 1;   
      return *data;
    
   } 
   else
      printf("Error: Stack is empty\n");
}

void push(char data) {

   if (isfull() == 0)
   {
   		top++; //add on more ontop
		
		strncpy(stack[top], data, sizeof(data));
   }
    else 
    {
    	printf("Error: Stack is full\n");
	}
}

void clear () {
	top = 0;
}
