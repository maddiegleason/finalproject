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
#include "gfx2.h"
#define XSIZE 650
#define YSIZE 650
#define XSCALE 50 
#define YSCALE 50
#define GRID 13

void drawBackground();
void drawLilyPads();
void drawTruck(int *dxtruck1, int *dxtruck2);
void drawCar(int *dxcar1, int *dxcar2);
void drawLog(int *dxlog1, int *dxlog2, int *dxlog3);
void drawFrog(int *dxfrog, int *dyfrog);
void drawTurtle(int *dxturtle, int *dxturtle1);
void resetFrog(int *frog_xpos, int *frog_ypos, int *collision);
void drawX(int x, int y);

int main()
{
	char c;
	int deltat = 25000;
	int dxfrog = 0, dyfrog = 0;			// initialize frog hop coordinates
	int dxtruck1 = 0, dxtruck2 = 0;
	int dxcar1 = 0, dxcar2 = 0;
	int dxlog1 = 0, dxlog2 = 0, dxlog3 = 0;
	int dxturtle = 0, dxturtle1= 0;
	int frog_xpos = 8;
	int frog_ypos = 13;
	int truck_xpos1 = 1, truck_ypos1 = 11;
	int truck_xpos2 = 5, truck_ypos2 = 9;
	int truck_xpos3 = 12, truck_ypos3 = 7; 
	int car[GRID];
	int log[GRID];
	int turtle[GRID];
	int collision = 0;
	

	// Open Window
	gfx_open(XSIZE, YSIZE, "Frogger");

	while (1){
		switch(c) {
			case 'R': // up arrow
				if (dyfrog > -12) {				// criteria establihsed based on starting point of frog
					dyfrog--;
					frog_ypos+=-1;
				}
				drawFrog(&dxfrog,&dyfrog);
				c = '+';
				break;
			case 'Q': // left arrow
				if (dxfrog > -7) {
					dxfrog--;
					frog_xpos+=-1;
				}
				drawFrog(&dxfrog,&dyfrog);
				c = '+';
				break;
			case 'T': // down arrow
				if (dyfrog < 0) {
					dyfrog++;
					frog_ypos+=1;
				}
				drawFrog(&dxfrog,&dyfrog);
				c = '+';
				break;
			case 'S': // right arrow
				if (dxfrog<5) {
					dxfrog++;
					frog_xpos+=1;
				}
				drawFrog(&dxfrog,&dyfrog);
				c = '+';
				break;
			}
			// Check positions for collisions between frog and objects
		
			switch (frog_ypos){
				case 1: //LilyPad 
					if (frog_xpos == 3 || 5 || 7 || 9 || 11){
						// level up				
					}
					break;
				case 2:	//Log 3 moving right with turtles
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					break;
				case 3:	//Log 2 moving left
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					break;
				case 4:	//Log 1	moving right with turtles
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					break;
				case 7:	//Truck 1 moving right
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					break;
				case 8:	//Car 2 moving left
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					break;
				case 9:	//Truck 2 moving left
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					break;
				case 10:	//Car 1 moving right
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					break;
				case 11://Truck 1 moving right
					if ((frog_xpos == truck_xpos1) || (truck_xpos1 + 1)){
						collision = 1;
						resetFrog(&frog_xpos, &frog_ypos, &collision);
					}
					break;
			}
			
			gfx_clear();
			drawBackground();
			drawLilyPads();
			drawTruck(&dxtruck1, &dxtruck2);
			drawCar(&dxcar1,&dxcar2);
			drawLog(&dxlog1,&dxlog2,&dxlog3);
			drawTurtle(&dxturtle, &dxturtle1);
			drawFrog(&dxfrog,&dyfrog);

			gfx_flush();
			usleep(deltat);
	
			if(gfx_event_waiting()){
			c = gfx_wait();
				if (c=='q'){
					return 0;			// quit program if user enters q
				}
			}
	}	
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

void drawTruck(int *dxtruck1, int *dxtruck2) 
{
	double i, j, k;
	for (k=0; k<=5;k+=4) {
		for (j=-1; j <= 1 ; j+=0.5){	
			for (i=0; i<=130; i+=13) {
				// TRUCKS GOING RIGHT
				// Truck Body 
				gfx_color(255,255,255);
				gfx_fill_rectangle((k+0)*XSCALE+i*j*XSCALE + *dxtruck1,YSIZE-((k+2.8)*YSCALE),(1.5*XSCALE),(.6*YSCALE));
				// Truck top 
				gfx_color(210, 27, 27);
				gfx_fill_rectangle(((k+1.5)*XSCALE+i*j*XSCALE) + *dxtruck1,YSIZE-((k+2.8)*YSCALE),(.5*XSCALE),(.6*YSCALE));
				// Truck Middle 
				gfx_color(0, 0, 0);
				gfx_fill_rectangle(((k+1.5)*XSCALE+i*j*XSCALE) + *dxtruck1,YSIZE-((k+2.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));
				// Truck Window
				gfx_color(81, 227, 255);
				gfx_fill_rectangle(((k+1.85)*XSCALE+i*j*XSCALE) + *dxtruck1, YSIZE-((k+2.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));

				// TRUCKs GOING LEFT
				// Truck Body 
				gfx_color(255,255,255);
				gfx_fill_rectangle(XSIZE-(1.5*XSCALE+i*j*XSCALE) - *dxtruck2,YSIZE-(4.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));
				// Truck top 
				gfx_color(210, 27, 27);
				gfx_fill_rectangle(XSIZE-(2.0*XSCALE+i*j*XSCALE) - *dxtruck2,YSIZE-(4.8*YSCALE),(.5*XSCALE),(.6*YSCALE));
				// Truck Middle 
				gfx_color(0, 0, 0);
				gfx_fill_rectangle(XSIZE-(1.65*XSCALE+i*j*XSCALE) - *dxtruck2,YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
				// Truck Window
				gfx_color(81, 227, 255);
				gfx_fill_rectangle(XSIZE-(2.00*XSCALE+i*j*XSCALE) - *dxtruck2, YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
			}	
		}	
	}	
	(*dxtruck1)++;
	(*dxtruck2)+=2;
}

void drawCar(int *dxcar1, int *dxcar2)
{
	double i,j;
	for (j=-1; j <=1; j+=0.5){
		for (i=0;i<=130;i+=13) {
			// CAR GOING RIGHT
			// Car Body
			gfx_color(165, 29, 124);
			gfx_fill_rectangle(((3*XSCALE) + *dxcar1 +i*j*XSCALE),YSIZE-(3.8*YSCALE),XSCALE,(.6*YSCALE));
			// Headlights
			gfx_color(253, 234, 59);
			gfx_fill_rectangle(((3.9*XSCALE) + *dxcar1+i*j*XSCALE),YSIZE-(3.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
			gfx_fill_rectangle(((3.9*XSCALE) + *dxcar1+i*j*XSCALE),YSIZE-(3.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
			// Windows
			gfx_color(81, 227, 255);
			gfx_fill_rectangle(((3.3*XSCALE) + *dxcar1+i*j*XSCALE),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
			gfx_fill_rectangle(((3.6*XSCALE) + *dxcar1+i*j*XSCALE),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

			// CAR GOING LEFT
			// Car Body
			gfx_color(165, 29, 124);
			gfx_fill_rectangle((XSIZE-(4*XSCALE) - *dxcar2+i*j*XSCALE),YSIZE-(5.8*YSCALE),XSCALE,(.6*YSCALE));
			// Headlights
			gfx_color(253, 234, 59);
			gfx_fill_rectangle((XSIZE-(4*XSCALE) - *dxcar2+i*j*XSCALE),YSIZE-(5.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
			gfx_fill_rectangle((XSIZE-(4*XSCALE) - *dxcar2+i*j*XSCALE),YSIZE-(5.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
			// Windows
			gfx_color(81, 227, 255);
			gfx_fill_rectangle((XSIZE-(3.4*XSCALE) - *dxcar2+i*j*XSCALE),YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
			gfx_fill_rectangle((XSIZE-(3.7*XSCALE) - *dxcar2+i*j*XSCALE),YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
		}
	}
	(*dxcar1)++;
	(*dxcar2)+=2;
}

void drawLog(int *dxlog1, int *dxlog2, int *dxlog3)
{
	double i,j;
	for (j=-5; j <=5; j+=0.5){
		for (i=0;i<=130;i+=13) {
			gfx_color(121, 68, 7);	
			gfx_fill_rectangle((7*XSCALE)+*dxlog1+i*j*XSCALE,YSIZE-(9.8*YSCALE),(2.5*XSCALE),(.6*YSCALE));	// log going right 
			gfx_fill_rectangle((3*XSCALE)-*dxlog2+i*j*XSCALE,YSIZE-(10.8*YSCALE),(2*XSCALE),(.6*YSCALE));	// log going left
			gfx_fill_rectangle((9*XSCALE)+*dxlog3+i*j*XSCALE,YSIZE-(11.8*YSCALE),(3*XSCALE),(.6*YSCALE));	// log going right
		}
	}
	(*dxlog1)+=2;
	(*dxlog2)++;
	(*dxlog3)+=3;
}

void drawTurtle(int *dxturtle, int *dxturtle1)
{
	double i,j,k;	
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
}

void drawFrog(int *dxfrog, int *dyfrog)
{
	// NOTE: frog will move in the x and y direction where dx and dy will be incremented by XSCALE and YSCALE respectively 
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

void resetFrog(int *frog_xpos, int *frog_ypos, int *collision)
{
	if (*collision){
		drawX(*frog_xpos, *frog_ypos);
		*frog_xpos = 8;
		*frog_ypos = 13;
	}
	*collision = 0;
}

void drawX(int x, int y)
{
	gfx_color(255, 0, 0);
	gfx_line(x, y, x - XSCALE, y + YSCALE);
	gfx_line(x, y + YSCALE, x - XSCALE, y);
}

// void levelUp();

// void contorlTimer();

// void controlLives();

