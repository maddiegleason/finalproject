// Authors: Madeline Gleason and Taylor Rongaus
// Date: December 13, 2015
// final.c is the game "Frogger"

/* Game Notes: 
- you have 3 lives, and lose a life from: 
	- moving outside game scene
	- jumping in to water
	- jumping to an already occupied home
	- running out of time
- frog moves with arrow keys
- get 10 points when moving a step forward, 500 points when reaching an empty home 
- timer counts down, faster every level (vehicles, frogs, logs move faster)
- 5 lanes of vehicles, 3 lanes with logs, 2 with turtles
- each lane moves at randomly chosen speed
- when an available home gets occupied, a frog appears at the starting point and you control frog from the starting point
- when all five homes are occupied timer restarts and you level up 
- if you lose all 3 lives you die and return to start of level 1
*/ 

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "gfx4.h"
#define XSIZE 650
#define YSIZE 650
#define XSCALE 50 
#define YSCALE 50
#define GRID 13

void waitFor (unsigned int secs);
char *num2str(int n);
void drawBackground();
void drawLilyPads();
void printInfo(int *lives, int *score);
void drawTruck(int *dxtruck1, int *dxtruck2, int *dxtruck3, int *frog_xpos, int *frog_ypos, int *collision, int *dxfrog, int *dyfrog, int *lives); 
void drawCar(int *dxcar1, int *dxcar2, int *frog_xpos, int *frog_ypos, int *collision, int *dxfrog, int *dyfrog, int *lives);
void drawLog(int *dxlog1, int *dxlog2, int *dxlog3, int *frog_xpos, int *frog_ypos, int *dxfrog, int *dyfrog, int *ride, int *win, int *collision, int *lives);
void drawFrog(int *dxfrog, int *dyfrog, int *ride, int *dxlog1, int *frog_xpos, int *frog_ypos, int *win, int *collision, int *lives);
void drawTurtle(int *dxturtle, int *dxturtle1);
void resetFrog(int *frog_xpos, int *frog_ypos, int *collision, int *dxfrog, int *dyfrog);
void drawX(int x, int y);
void checkWin(int *frog_xpos, int *frog_ypos, int *win);

int main()
{
	char c;
	char w;
	int deltat = 50000;
	int dxfrog = 0; 		// initialize frog hop coordinates
	int dyfrog = 0;	
	int dxtruck1 = 0; 
	int dxtruck2 = 0;
	int dxtruck3 = 0;
	int dxcar1 = 0; 
	int dxcar2 = 0;
	int dxlog1 = 0; 
	int dxlog2 = 0;
	int dxlog3 = 0;
	int dxturtle = 0, dxturtle1= 0;
	int frog_xpos = 8;
	int frog_ypos = 13;
	int collision = 0;
	int ride = 0;
	int lives = 3;
	int win = 0;
	int score = 0;

	// Open Window
	gfx_open(XSIZE, YSIZE, "Frogger");
	gfx_clear();
	gfx_color(255,255,255);
	gfx_changefont("12x24");
	gfx_text(XSIZE/2-25,YSIZE/2-20,"FROGGER");
	gfx_changefont("6x9");	gfx_text(XSIZE/2-25,YSIZE/2-5,"click to start");
	gfx_changefont("8x13");	gfx_text(XSIZE/2-30,YSIZE/2+50,"INSTRUCTIONS:");
	gfx_changefont("6x9");	gfx_text(XSIZE/2-18,YSIZE/2+65,"don't die lol");
	gfx_text(XSIZE/2-40,YSIZE/2+75,"you have three lives");
	gfx_text(XSIZE/2-22,YSIZE/2+85,"press q to quit");

	while (1){
	if(gfx_event_waiting()){		w = gfx_wait();		if (w == 'q') return;	}
	
	while (w == 1) {
		switch(c) {
			case 'R': // up arrow
				if (dyfrog > -12) {				// criteria establihsed based on starting point of frog
					dyfrog--;
					frog_ypos+=-1;
					score += 10;
		//			printf("frog y position: %d\n", frog_ypos);
				}
				drawFrog(&dxfrog,&dyfrog,&ride,&dxlog1,&frog_xpos,&frog_ypos,&win,&collision,&lives);
				c = '+';
				break;
			case 'Q': // left arrow
				if (dxfrog > -7) {
					dxfrog--;
					frog_xpos+=-1;
		//			printf("frog x position: %d\n", frog_xpos);
				}
				drawFrog(&dxfrog,&dyfrog,&ride,&dxlog1,&frog_xpos,&frog_ypos,&win,&collision,&lives);
				c = '+';
				break;
			case 'T': // down arrow
				if (dyfrog < 0) {
					dyfrog++;
					frog_ypos+=1;
		//			printf("frog y position: %d\n", frog_ypos);
				}
				drawFrog(&dxfrog,&dyfrog,&ride,&dxlog1,&frog_xpos,&frog_ypos,&win,&collision,&lives);
				c = '+';
				break;
			case 'S': // right arrow
				if (dxfrog<5) {
					dxfrog++;
					frog_xpos+=1;
		//			printf("frog x position: %d\n", frog_xpos);
				}
				drawFrog(&dxfrog,&dyfrog,&ride,&dxlog1,&frog_xpos,&frog_ypos,&win,&collision,&lives);
				c = '+';
				break;
			}
				
			gfx_clear();
			drawBackground();
			drawLilyPads();
			printInfo(&lives, &score);
			drawTruck(&dxtruck1, &dxtruck2, &dxtruck3, &frog_xpos, &frog_ypos, &collision, &dxfrog, &dyfrog, &lives);
			drawCar(&dxcar1, &dxcar2, &frog_xpos, &frog_ypos, &collision, &dxfrog, &dyfrog, &lives);
			drawLog(&dxlog1,&dxlog2,&dxlog3,&frog_xpos, &frog_ypos, &dxfrog, &dyfrog, &ride, &win, &collision, &lives);
			drawTurtle(&dxturtle, &dxturtle1);
			drawFrog(&dxfrog,&dyfrog,&ride,&dxlog1,&frog_xpos,&frog_ypos,&win,&collision,&lives);

			gfx_flush();
			usleep(deltat);
			
			// check to see if out of lives
			// instead of returning a "You Lose" window maybe return back to original home page? 
			if (lives == 0) {
				w = '+';
				gfx_clear();
				gfx_color(255,255,255);
				gfx_text(XSIZE/2-20,YSIZE/2-20,"YOU LOSE");	
				gfx_changefont("6x9");
				gfx_text(XSIZE/2-22,YSIZE/2-10,"press 'q' to quit");
				if(gfx_event_waiting()){					w = gfx_wait();					if ((w == 'q')) return;
				}
			}
			if (win == 1) {
				w = '+';
				gfx_clear();
				gfx_color(255,255,255);
				gfx_text(XSIZE/2-20,YSIZE/2-20,"YOU WIN");	
				gfx_changefont("6x9");
				gfx_text(XSIZE/2-25,YSIZE/2-10,"press 'q' to quit");
				if(gfx_event_waiting()){					w = gfx_wait();					if (w == 'q') return;				}
			}
	
			if(gfx_event_waiting()){
			c = gfx_wait();
				if (c=='q'){
					return 0;			// quit program if user enters q
				}
			}
		}
	}	
}

void waitFor(unsigned int secs) 
{
	unsigned int retTime;	
	retTime = time(0) + secs;		// get finishing time
	while (time(0) < retTime); 		// loop until it arrives
}

char *num2str(int n) 
{
  static char a[10], *p = a;
  snprintf(p, 10, "%d", n);
  return p;
}

void drawBackground()
{	
	// Set Grass 1
	gfx_color(74, 212, 46);	
	gfx_fill_rectangle(0,YSIZE-2*YSCALE,XSIZE,2*YSCALE);
	// Set Road
	gfx_color(158, 162, 158);
	gfx_fill_rectangle(0,YSIZE-7*YSCALE,XSIZE,5*YSCALE);
	// Set Grass 2
	gfx_color(74, 212, 46);
	gfx_fill_rectangle(0,YSIZE-9*YSCALE,XSIZE,2*YSCALE);
	// Set Water
	gfx_color(80, 159, 238);
	gfx_fill_rectangle(0,YSIZE-12*YSCALE,XSIZE,3*YSCALE);
	// Set Grass 3
	gfx_color(74, 212, 46);
	gfx_fill_rectangle(0,0,XSIZE,YSCALE);
	// Set Grid
	int i, j;
	gfx_color(108, 105, 105);
	for (i = 0; i <=XSIZE; i=i+XSCALE){
		gfx_line(i, 0, i, YSIZE);
	}
	for (j= 0; j<=YSIZE; j=j+YSCALE){
		gfx_line(0, j, XSIZE, j);
	}
}

void drawLilyPads()
{
	gfx_color(243, 164, 246);
	double k;
	for (k = 2.5; k <=10.5; k = k+2){
		gfx_fill_arc((k*XSCALE-20),(.5*YSCALE-20),40,40,0,360);
	}
}

void printInfo(int *lives, int *score){
	gfx_color(255,255,255);
	gfx_changefont("12x24");
	
	char *numscore;
	numscore = num2str(*score);
	gfx_text(5,YSIZE-5,"Score:");
	gfx_text(85,YSIZE-5,numscore);
	
	char *numlives;
	numlives = num2str(*lives);
	gfx_text(5,YSIZE-30,"Lives:");
	gfx_text(80,YSIZE-30,numlives);
}

void drawTruck(int *dxtruck1, int *dxtruck2, int *dxtruck3, int *frog_xpos, int *frog_ypos, int *collision, int *dxfrog, int *dyfrog, int *lives) 
{
	// TRUCK1 GOING RIGHT
	// Truck Body 
	gfx_color(255,255,255);
	gfx_fill_rectangle(XSCALE+0.5**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	// Truck top 
	gfx_color(210, 27, 27);
	gfx_fill_rectangle(1.5*XSCALE+XSCALE+0.5**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(.5*XSCALE),(.6*YSCALE));
	// Truck Middle 
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(1.5*XSCALE+XSCALE+0.5**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));
	// Truck Window
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(1.85*XSCALE+XSCALE+0.5**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));
	
	// TRUCK2 GOING LEFT
	// Truck Body 
	gfx_color(255,255,255);
	gfx_fill_rectangle(XSIZE-1.5*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	// Truck top 
	gfx_color(210, 27, 27);
	gfx_fill_rectangle(XSIZE-2.0*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(.5*XSCALE),(.6*YSCALE));
	// Truck Middle 
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(XSIZE-1.65*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	// Truck Window
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(XSIZE-2.0*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));	
	
	// TRUCK3 GOING RIGHT
	gfx_color(255,255,255);
	gfx_fill_rectangle(4*XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	// Truck top 
	gfx_color(210, 27, 27);
	gfx_fill_rectangle(4.5*XSCALE+XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(.5*XSCALE),(.6*YSCALE));
	// Truck Middle 
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(4.5*XSCALE+XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));
	// Truck Window
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(4.85*XSCALE+XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));
	
	// Increment truck positions
	(*dxtruck1)++;
	if (0.5**dxtruck1 > 13) {
		*dxtruck1 = -10;
	}
	(*dxtruck2)++;
	if (0.5**dxtruck2 > 13) {
		*dxtruck2 = -10;
	}
	(*dxtruck3)++;
	if (0.5**dxtruck3 > 13) {
		*dxtruck3 = -20;
	}
	
	// Check for collisions
	if (((*frog_xpos == 0.5**dxtruck1+1)||(*frog_xpos == 0.5**dxtruck1+2)||(*frog_xpos == 0.5**dxtruck1+3)) && (*frog_ypos == 11)) {
		*collision = 1;
		*lives = *lives - 1;
		drawX(*frog_xpos, *frog_ypos-1);
		resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);
	}
	// note: having troubles w/ accurately detecting these two collisions:
	if (((*frog_xpos == 0.5**dxtruck2+4)||(*frog_xpos == 0.5**dxtruck2+2)||(*frog_xpos == 0.5**dxtruck2+3)) && (*frog_ypos == 9)) {
		*collision = 1;
		*lives = *lives -1;
		drawX(*frog_xpos, *frog_ypos-1);
		resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);
	}
	if (((*frog_xpos == 0.5**dxtruck3+4)||(*frog_xpos == 0.5**dxtruck3+5)||(*frog_xpos == 0.5**dxtruck3+6)) && (*frog_ypos == 7)) {
		*collision = 1;
		*lives = *lives -1;
		drawX(*frog_xpos, *frog_ypos-1);
		resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);
	}

}

void drawCar(int *dxcar1, int *dxcar2, int *frog_xpos, int *frog_ypos, int *collision, int *dxfrog, int *dyfrog, int *lives)
{

	// CAR GOING RIGHT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(4*XSCALE+0.25**dxcar1*XSCALE,YSIZE-(3.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(3.9*XSCALE+XSCALE+0.25**dxcar1*XSCALE,YSIZE-(3.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(3.9*XSCALE+XSCALE+0.25**dxcar1*XSCALE,YSIZE-(3.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(3.3*XSCALE+XSCALE+0.25**dxcar1*XSCALE,YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(3.6*XSCALE+XSCALE+0.25**dxcar1*XSCALE,YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// CAR GOING LEFT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(XSIZE-(4*XSCALE)-0.5**dxcar2*XSCALE,YSIZE-(5.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(XSIZE-(4*XSCALE)-0.5**dxcar2*XSCALE,YSIZE-(5.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(XSIZE-(4*XSCALE)-0.5**dxcar2*XSCALE,YSIZE-(5.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(XSIZE-(3.4*XSCALE)-0.5**dxcar2*XSCALE,YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(XSIZE-(3.7*XSCALE)-0.5**dxcar2*XSCALE,YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// Increment car positions
	(*dxcar1)++;
	if (0.25**dxcar1 > 13) {
		*dxcar1 = -20;
	}
	(*dxcar2)++;
	if (0.5**dxcar2 > 13) {
		*dxcar2 = -10;
	}

	// Check for collisions
	if ((*frog_xpos == 0.25**dxcar1+5) && (*frog_ypos == 10)) {
		*collision = 1;
		*lives = *lives -1;
		drawX(*frog_xpos, *frog_ypos-1);
		resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);
	}
	// note: having troubles checking successive collisions again
	if ((*frog_xpos == 0.5**dxcar2+5) && (*frog_ypos == 8)) {
		*collision = 1;
		*lives = *lives - 1;
		drawX(*frog_xpos, *frog_ypos-1);
		resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);
	} 
}

void drawLog(int *dxlog1, int *dxlog2, int *dxlog3, int *frog_xpos, int *frog_ypos, int *dxfrog, int *dyfrog, int *ride, int *win, int *collision, int *lives)
{	
	// Draw logs	gfx_color(121, 68, 7);	gfx_fill_rectangle((1*XSCALE)+4**dxlog1,YSIZE-(9.8*YSCALE),(3*XSCALE),(.6*YSCALE));// log going right 	gfx_fill_rectangle((3*XSCALE)+3**dxlog2,YSIZE-(10.8*YSCALE),(2*XSCALE),(.6*YSCALE));// log going left	gfx_fill_rectangle((9*XSCALE)+5**dxlog3,YSIZE-(11.8*YSCALE),(3*XSCALE),(.6*YSCALE));// log going right	// Increment log positions	(*dxlog1)++;	if (*dxlog1 > 550/4){		*dxlog1 = -100/4;	}	(*dxlog2)--;	if (*dxlog2 < -300/3){		*dxlog2 = 350/3;	}	(*dxlog3)++;	if (*dxlog3 > 200/5){		*dxlog3 = -450/5;	}	// Check for frog ride	if ((*frog_xpos == (*dxlog1*XSCALE*1) || (*dxlog1*XSCALE*2) || (*dxlog1*XSCALE*3)) && (*frog_ypos == 4)){		*ride = 1;		//drawFrog(dxfrog, dyfrog, ride, dxlog1, frog_xpos, frog_ypos, win);		if (*frog_xpos == 13){			*ride = 0;			*lives = *lives - 1;			*collision = 1;			drawX(*frog_xpos, *frog_ypos-1);			resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);		}	}

/*	// Draw logs
	gfx_color(121, 68, 7);
	gfx_fill_rectangle((7*XSCALE)+0.25**dxlog1*XSCALE,YSIZE-(9.8*YSCALE),(2.5*XSCALE),(.6*YSCALE));	// log going right 
	gfx_fill_rectangle((3*XSCALE)-0.5**dxlog2*XSCALE,YSIZE-(10.8*YSCALE),(2*XSCALE),(.6*YSCALE));	// log going left
	gfx_fill_rectangle((9*XSCALE)+0.35**dxlog3*XSCALE,YSIZE-(11.8*YSCALE),(3*XSCALE),(.6*YSCALE));	// log going right
	
	// Increment log positions
	(*dxlog1)++;
	if (0.25**dxlog1 > 20) {
		*dxlog1 = -40;
	}
//	printf("%d\n",*dxlog1);
	(*dxlog2)++;
	if (0.5**dxlog2 > 20) {
		*dxlog1 = -20;
	}
	(*dxlog3)++;
	if (0.35**dxlog3 > 10) {
		*dxlog1 = -40;
	}

	// Check for frog ride
	// note: currently having issues w/ not performing well after multiple rides & dropping off frog in weird places
	// check if frog in water

	if (((*frog_xpos == 0.25**dxlog1+8)||(*frog_xpos == 0.25**dxlog1+9)||(*frog_xpos == 0.25**dxlog1+10)) && (*frog_ypos == 4)){
		*ride = 1;
	}
	// why isn't this working??
	if (((*frog_xpos != 0.25**dxlog1+8)||(*frog_xpos != 0.25**dxlog1+9)||(*frog_xpos != 0.25**dxlog1+10)) && (*frog_ypos == 4)) {
		*ride = 0;
		*collision = 1;
		*lives = *lives - 1;
		drawX(*frog_xpos, *frog_ypos-1);
		resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);
	} 
	*/
}

void drawTurtle(int *dxturtle, int *dxturtle1)
{
/*	double i,j,k;	
	for (k=3.5;k<=5.5;k++){	
		for (j=-1; j <=1; j+=0.5){
			for (i=0;i<=130;i+=13){
				gfx_color(9, 110, 23);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE) + *dxturtle+i*j*XSCALE), (YSIZE-(9.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 0, 180);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE) + *dxturtle+i*j*XSCALE), (YSIZE-(9.7*YSCALE)), (.7*YSCALE),(.5*YSCALE), 180,360);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 27 + *dxturtle+i*j*XSCALE), (YSIZE-9.45*YSCALE)-7.5, 15, 15, 0, 360);
				gfx_color(255, 255, 255);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 37 + *dxturtle+i*j*XSCALE), (YSIZE-9.25*YSCALE)-7.5, 5, 5, 0, 360);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 37 + *dxturtle+i*j*XSCALE), (YSIZE-9.45*YSCALE)-7.5, 5, 5, 0, 360);
				gfx_color(0, 0, 0);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 39 + *dxturtle+i*j*XSCALE), (YSIZE-9.25*YSCALE)-7.5, 4, 4, 0, 360);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 39 + *dxturtle+i*j*XSCALE), (YSIZE-9.45*YSCALE)-7.5, 4, 4, 0, 360);
			}
		}
	}	
	for (k=6;k<=7;k++){	
		for (j=-1; j <=1; j+=0.5){
			for (i=0;i<=130;i+=13){
				gfx_color(9, 110, 23);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE) + *dxturtle1+i*j*XSCALE), (YSIZE-(11.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 0, 180);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE) + *dxturtle1+i*j*XSCALE), (YSIZE-(11.7*YSCALE)), (.7*YSCALE),(.5*YSCALE), 180,360);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 27 + *dxturtle1+i*j*XSCALE), (YSIZE-11.45*YSCALE)-7.5, 15, 15, 0, 360);
				gfx_color(255, 255, 255);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 37 + *dxturtle1+i*j*XSCALE), (YSIZE-11.25*YSCALE)-7.5, 5, 5, 0, 360);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 37 + *dxturtle1+i*j*XSCALE), (YSIZE-11.45*YSCALE)-7.5, 5, 5, 0, 360);
				gfx_color(0, 0, 0);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 39 + *dxturtle1+i*j*XSCALE), (YSIZE-11.25*YSCALE)-7.5, 4, 4, 0, 360);
				gfx_fill_arc((k*XSCALE-(.25*XSCALE)+ 39 + *dxturtle1+i*j*XSCALE), (YSIZE-11.45*YSCALE)-7.5, 4, 4, 0, 360);
			}
		}
	}
	(*dxturtle)+=2;
	(*dxturtle1)+=3;
*/
}

void drawFrog(int *dxfrog, int *dyfrog, int *ride, int *dxlog1, int *frog_xpos, int *frog_ypos, int *win, int *collision, int *lives)
{
	// NOTE: frog will move in the x and y direction where dx and dy will be incremented by XSCALE and YSCALE respectively 
	if (*ride == 0) {
		// frog green body
		gfx_color(43, 255, 0);
		gfx_fill_arc((7.25*XSCALE + *dxfrog*XSCALE), (YSIZE-(.8*YSCALE) + *dyfrog*YSCALE), (.5*YSCALE), (.7*YSCALE), 0, 180);
		gfx_fill_arc((7.25*XSCALE + *dxfrog*XSCALE), (YSIZE-(.8*YSCALE) + *dyfrog*YSCALE), (.5*YSCALE), (.7*YSCALE), 180, 360);
		// frog yellow body
		gfx_color(243, 255, 58);
		gfx_fill_arc((7.35*XSCALE + *dxfrog*XSCALE), (YSIZE-(.7*YSCALE) + *dyfrog*YSCALE), (.3*YSCALE), (.5*YSCALE), 0, 180);
		gfx_fill_arc((7.35*XSCALE + *dxfrog*XSCALE), (YSIZE-(.7*YSCALE) + *dyfrog*YSCALE), (.3*YSCALE), (.5*YSCALE), 180, 360);
		// frog eyes
		gfx_color(239, 20, 239);
		gfx_fill_arc((7.3*XSCALE)-5+*dxfrog*XSCALE,YSIZE-(.7*YSCALE)-5+*dyfrog*YSCALE,10,10,0,360);
		gfx_fill_arc((7.7*XSCALE)-5+*dxfrog*XSCALE,YSIZE-(.7*YSCALE)-5+*dyfrog*YSCALE,10,10,0,360);
	}
	if (*ride == 1) {
		// frog green body
		gfx_color(43, 255, 0);
		gfx_fill_arc((1.25*XSCALE +4**dxlog1), (YSIZE-(.8*YSCALE) + *dyfrog*YSCALE), (.5*YSCALE), (.7*YSCALE), 0, 180);
		gfx_fill_arc((1.25*XSCALE +4**dxlog1), (YSIZE-(.8*YSCALE) + *dyfrog*YSCALE), (.5*YSCALE), (.7*YSCALE), 180, 360);
		// frog yellow body
		gfx_color(243, 255, 58);
		gfx_fill_arc((1.35*XSCALE +4**dxlog1), (YSIZE-(.7*YSCALE) + *dyfrog*YSCALE), (.3*YSCALE), (.5*YSCALE), 0, 180);
		gfx_fill_arc((1.35*XSCALE +4**dxlog1), (YSIZE-(.7*YSCALE) + *dyfrog*YSCALE), (.3*YSCALE), (.5*YSCALE), 180, 360);
		// frog eyes
		gfx_color(239, 20, 239);
		gfx_fill_arc((1.3*XSCALE)-5+4**dxlog1,YSIZE-(.7*YSCALE)-5+*dyfrog*YSCALE,10,10,0,360);
		gfx_fill_arc((1.7*XSCALE)-5+4**dxlog1,YSIZE-(.7*YSCALE)-5+*dyfrog*YSCALE,10,10,0,360);
	}	
	
	// check for ride
	if (*frog_ypos != 4) {
		*ride = 0;
	}
	
	// check for lilypad
	if (*frog_ypos == 1) {
		if ((*frog_xpos = 3) || (*frog_xpos == 5) || (*frog_xpos == 7) || (*frog_xpos == 9) ||(*frog_xpos == 11)) {
			*win = 1;
		}
		else {
			*collision = 1;
			*lives = *lives - 1;
			drawX(*frog_xpos, *frog_ypos-1);
			resetFrog(frog_xpos, frog_ypos, collision, dxfrog, dyfrog);
		}
	}		

}

void resetFrog(int *frog_xpos, int *frog_ypos, int *collision, int *dxfrog, int *dyfrog)
{
	//	waitFor(2);		
		*frog_xpos = 8;
		*frog_ypos = 13;
		*dxfrog = 0;
		*dyfrog = 0;
		*collision = 0;
}

void drawX(int x, int y)
{
	gfx_color(255, 0, 0);
	gfx_line(x*XSCALE, y*YSCALE, x*XSCALE - XSCALE, y*YSCALE + YSCALE);
	gfx_line(x*XSCALE, y*YSCALE + YSCALE, x*XSCALE - XSCALE, y*YSCALE);
}
