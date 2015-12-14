// Authors: Madeline Gleason and Taylor Rongaus
// Date: December 13, 2015
// final.c is the game "playerger"

/* Game Notes: 
- you have 3 lives, and lose a life from: 
	- moving outside game scene
	- jumping in to water
	- jumping to an already occupied home
	- running out of time
- player moves with arrow keys
- get 10 points when moving a step forward, 500 points when reaching an empty home 
- timer counts down, faster every level (vehicles, players, logs move faster)
- 5 lanes of vehicles, 3 lanes with logs, 2 with turtles
- each lane moves at randomly chosen speed
- when an available home gets occupied, a player appears at the starting point and you control player from the starting point
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
void drawBase();
void printInfo(int *lives, int *score);
void drawTruck(int *dxtruck1, int *dxtruck2, int *dxtruck3, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives); 
void drawCar(int *dxcar1, int *dxcar2, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives);
void drawplayer(int *dxplayer, int *dyplayer, int *player_xpos, int *player_ypos, int *win, int *collision, int *lives);
void resetplayer(int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer);
void drawX(int x, int y);
void checkWin(int *player_xpos, int *player_ypos, int *win);

int main()
{
	char c;
	char w;
	int deltat = 50000;
	int dxplayer = 0; 		// initialize player hop coordinates
	int dyplayer = 0;	
	int dxtruck1 = 0; 
	int dxtruck2 = 0;
	int dxtruck3 = 0;
	int dxcar1 = 0; 
	int dxcar2 = 0;
	int player_xpos = 8;
	int player_ypos = 13;
	int collision = 0;
	int lives = 15;
	int win = 0;
	int score = 0;

	// Open Window
	gfx_open(XSIZE, YSIZE, "Traffic Jam");
	gfx_clear();
	gfx_color(255,255,255);
	gfx_changefont("12x24");
	gfx_text(XSIZE/2-35,YSIZE/2-20,"Traffic Jam");
	gfx_changefont("6x9");	gfx_text(XSIZE/2-25,YSIZE/2-5,"click to start");
	gfx_changefont("8x13");	gfx_text(XSIZE/2-30,YSIZE/2+50,"INSTRUCTIONS:");
	gfx_changefont("6x9");	gfx_text(XSIZE/2-25,YSIZE/2+65,"don't get hit lol");
	gfx_text(XSIZE/2-40,YSIZE/2+75,"you have three lives");
	gfx_text(XSIZE/2-22,YSIZE/2+85,"press q to quit");

	while (1){
	if(gfx_event_waiting()){		w = gfx_wait();		if (w == 'q') return;	}
	
	while (w == 1) {
	
		switch(c) {
			case 'R': // up arrow
				if (dyplayer > -12) {				// criteria established based on starting point of player
					dyplayer--;
					player_ypos+=-1;
					score += 10;
				}
		//		printf("player y position: %d\n", player_ypos);
				drawplayer(&dxplayer,&dyplayer,&player_xpos,&player_ypos,&win,&collision,&lives);
				c = '+';
				break;
			case 'Q': // left arrow
				if (dxplayer > -7) {
					dxplayer--;
					player_xpos+=-1;
				}
		//		printf("player x position: %d\n", player_xpos);
				drawplayer(&dxplayer,&dyplayer,&player_xpos,&player_ypos,&win,&collision,&lives);
				c = '+';
				break;
			case 'T': // down arrow
				if (dyplayer < 0) {
					dyplayer++;
					player_ypos+=1;
		//			printf("player y position: %d\n", player_ypos);
				}
				drawplayer(&dxplayer,&dyplayer,&player_xpos,&player_ypos,&win,&collision,&lives);
				c = '+';
				break;
			case 'S': // right arrow
				if (dxplayer<5) {
					dxplayer++;
					player_xpos+=1;
		//			printf("player x position: %d\n", player_xpos);
				}
				drawplayer(&dxplayer,&dyplayer,&player_xpos,&player_ypos,&win,&collision,&lives);
				c = '+';
				break;
			}
				
			gfx_clear();
			drawBackground();
			drawBase();
			printInfo(&lives, &score);
			drawTruck(&dxtruck1, &dxtruck2, &dxtruck3, &player_xpos, &player_ypos, &collision, &dxplayer, &dyplayer, &lives);
			drawCar(&dxcar1, &dxcar2, &player_xpos, &player_ypos, &collision, &dxplayer, &dyplayer, &lives);
			drawplayer(&dxplayer,&dyplayer,&player_xpos,&player_ypos,&win,&collision,&lives);

			gfx_flush();
			usleep(deltat);
			
			// check to see if out of lives
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
			// check to see if game won
			if (player_ypos == 1) {
				if ((player_xpos == 3) || (player_xpos == 5) || (player_xpos == 7) || (player_xpos == 9) ||(player_xpos == 11)) {
					win = 1;
				}
				else {
					collision = 1;
					lives = lives - 1;
					drawX(player_xpos, player_ypos-1);
					resetplayer(&player_xpos,&player_ypos,&collision,&dxplayer,&dyplayer);
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
	gfx_color(0, 0, 0);	
	gfx_fill_rectangle(0,YSIZE-2*YSCALE,XSIZE,2*YSCALE);
	// Set Road
	gfx_color(158, 162, 158);
	gfx_fill_rectangle(0,YSIZE-7*YSCALE,XSIZE,5*YSCALE);
	// Set Grass 2
	gfx_color(158, 162, 158);
	gfx_fill_rectangle(0,YSIZE-9*YSCALE,XSIZE,2*YSCALE);
	// Set Water
	gfx_color(158, 162, 158);
	gfx_fill_rectangle(0,YSIZE-12*YSCALE,XSIZE,3*YSCALE);
	// Set Grass 3
	gfx_color(0, 0, 0);
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

void drawBase()
{
	gfx_color(255, 255, 0);
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

void drawTruck(int *dxtruck1, int *dxtruck2, int *dxtruck3, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives) 
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
	if (((*player_xpos == 0.5**dxtruck1+1)||(*player_xpos == 0.5**dxtruck1+2)||(*player_xpos == 0.5**dxtruck1+3)) && (*player_ypos == 11)) {
		*collision = 1;
		*lives = *lives - 1;
		drawX(*player_xpos, *player_ypos-1);
		resetplayer(player_xpos, player_ypos, collision, dxplayer, dyplayer);
	}
	if (((*player_xpos == 0.5**dxtruck2+4)||(*player_xpos == 0.5**dxtruck2+2)||(*player_xpos == 0.5**dxtruck2+3)) && (*player_ypos == 9)) {
		*collision = 1;
		*lives = *lives -1;
		drawX(*player_xpos, *player_ypos-1);
		resetplayer(player_xpos, player_ypos, collision, dxplayer, dyplayer);
	}
	if (((*player_xpos == 0.5**dxtruck3+4)||(*player_xpos == 0.5**dxtruck3+5)||(*player_xpos == 0.5**dxtruck3+6)) && (*player_ypos == 7)) {
		*collision = 1;
		*lives = *lives -1;
		drawX(*player_xpos, *player_ypos-1);
		resetplayer(player_xpos, player_ypos, collision, dxplayer, dyplayer);
	}

}

void drawCar(int *dxcar1, int *dxcar2, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives)
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
	if ((*player_xpos == 0.25**dxcar1+5) && (*player_ypos == 10)) {
		*collision = 1;
		*lives = *lives -1;
		drawX(*player_xpos, *player_ypos-1);
		resetplayer(player_xpos, player_ypos, collision, dxplayer, dyplayer);
	}
	if ((*player_xpos == 0.5**dxcar2+5) && (*player_ypos == 8)) {
		*collision = 1;
		*lives = *lives - 1;
		drawX(*player_xpos, *player_ypos-1);
		resetplayer(player_xpos, player_ypos, collision, dxplayer, dyplayer);
	} 
}


void drawplayer(int *dxplayer, int *dyplayer, int *player_xpos, int *player_ypos, int *win, int *collision, int *lives)
{

	// player red body
	gfx_color(255, 0, 0);
	gfx_fill_arc((7.25*XSCALE + *dxplayer*XSCALE), (YSIZE-(.8*YSCALE) + *dyplayer*YSCALE), (.5*YSCALE), (.7*YSCALE), 0, 180);
	gfx_fill_arc((7.25*XSCALE + *dxplayer*XSCALE), (YSIZE-(.8*YSCALE) + *dyplayer*YSCALE), (.5*YSCALE), (.7*YSCALE), 180, 360);
	// player yellow body
	gfx_color(243, 255, 58);
	gfx_fill_arc((7.35*XSCALE + *dxplayer*XSCALE), (YSIZE-(.7*YSCALE) + *dyplayer*YSCALE), (.3*YSCALE), (.5*YSCALE), 0, 180);
	gfx_fill_arc((7.35*XSCALE + *dxplayer*XSCALE), (YSIZE-(.7*YSCALE) + *dyplayer*YSCALE), (.3*YSCALE), (.5*YSCALE), 180, 360);

		
}

void resetplayer(int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer)
{
		*player_xpos = 8;
		*player_ypos = 13;
		*dxplayer = 0;
		*dyplayer = 0;
		*collision = 0;
}

void drawX(int x, int y)
{
	gfx_color(255, 0, 0);
	gfx_line(x*XSCALE, y*YSCALE, x*XSCALE - XSCALE, y*YSCALE + YSCALE);
	gfx_line(x*XSCALE, y*YSCALE + YSCALE, x*XSCALE - XSCALE, y*YSCALE);
}
