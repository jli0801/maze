#define MAX_SIZEA 500 
void setCoord(int x, int y); //should be from the scanner and should be the entrance

void mazeSetup(int **m);

void setEnergy(int);
int getEnergy(void);

void setMaxRow(int);
void setMaxCol(int); //sets the boundaries 

int compareCoor(int exitX, int exitY);

int getX(void);
int getY(void);

void mvf(); //update the coordinates in the ant.c file
void mvb();
void mvl();
void mwr();


//for the stack of his coordinates 
int isemptyA (void);
int isfullA (void);
int peekA (void); 
int popA (void);
void pushA ();
void clearA (void);


//checking to left, right, forwards, back and using the 'itch'
void cwl();
void cwr();
void cwf();
void cwb();
//push pop clear peek are all in the stacks.h file

void bjpi();
void cjpi();
void jpitx();
//the char is supposed to be an array but you can't pass arrays 
//when using this function set the action to a static char array 
void rpNt(int x, int y, int t, char action); //n - actions  t- times 
//so for the stack we don't know if the next one will be rpNt 
 
