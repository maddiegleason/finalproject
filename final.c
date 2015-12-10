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

void drawBackground();
void drawLilyPads();
void drawTruck(int *dx);
void drawCar(int *dx);
void drawLog(int *dx);
void drawFrog();

int main()
{
	char c;
	int dx = 0;					// initiate movement in the x direction
	int deltat = 20000;

	// Open Window
	gfx_open(XSIZE, YSIZE, "Frogger");

	while (1){
		gfx_clear();
		
		drawBackground();
		drawLilyPads();
		drawTruck(&dx);
		drawCar(&dx);
		drawLog(&dx);
		drawFrog();

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

	/* Set Grid
	int i, j;
	gfx_color(0, 0, 0);
	for (i = 0; i <=XSIZE; i=i+XSCALE){
		gfx_line(i, 0, i, YSIZE);
	}
	for (j= 0; j<=YSIZE; j=j+YSCALE){
		gfx_line(0, j, XSIZE, j);
	}*/	
}

void drawLilyPads()
{
		gfx_color(243, 164, 246);
		double k;
		for (k = 2.5; k <=10.5; k = k+2){
			gfx_fill_arc(((k*XSCALE)-20),.5*YSCALE-20,40,40,0,360);
		}
}

// NOTE: for moving objects truck, car, and log only need to increment x position
// Cannot figure out how to generate multiple objects in one line going across
// tried for loop incrementing i in the x position and that just changed speed? 

void drawTruck(int *dx)
{
	gfx_color(255,255,255);
	gfx_fill_rectangle(0+*dx,YSIZE-(2.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	
	gfx_color(210, 27, 27);
	gfx_fill_rectangle((1.5*XSCALE) + *dx,YSIZE-(2.8*YSCALE),(.5*XSCALE),(.6*YSCALE));
	
	gfx_color(0, 0, 0);
	gfx_fill_rectangle((1.5*XSCALE) + *dx,YSIZE-(2.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	
	gfx_color(81, 227, 255);
	gfx_fill_rectangle((1.85*XSCALE) + *dx, YSIZE-(2.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	
	(*dx)++;

}

void drawCar(int *dx)
{
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(((4*XSCALE) + *dx),YSIZE-(3.8*YSCALE),XSCALE,(.6*YSCALE));
	
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(((4.9*XSCALE) + *dx),YSIZE-(3.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(((4.9*XSCALE) + *dx),YSIZE-(3.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(((4.3*XSCALE) + *dx),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(((4.6*XSCALE) + *dx),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	
	(*dx)++;
}

void drawLog(int *dx)
{
	gfx_color(121, 68, 7);
	gfx_fill_rectangle((7*XSCALE)+*dx,YSIZE-(9.8*YSCALE),(2.5*XSCALE),(.6*YSCALE));
	gfx_fill_rectangle((3*XSCALE)+*dx,YSIZE-(10.8*YSCALE),(2*XSCALE),(.6*YSCALE));
	gfx_fill_rectangle((9*XSCALE)+*dx,YSIZE-(11.8*YSCALE),(3*XSCALE),(.6*YSCALE));
	
	(*dx)++;
}

// Still working on frog body
void drawFrog()
{
	gfx_color(9, 110, 23);
	gfx_ellipse(7.5*XSCALE, YSIZE-(.5*YSCALE), (.3*XSCALE), (.4*YSCALE));

	gfx_color(243, 255, 58);
	gfx_ellipse(7.5*XSCALE, YSIZE-(.5*YSCALE), (.2*XSCALE), (.3*YSCALE));

	gfx_color(239, 20, 239);
	gfx_fill_arc((7.3*XSCALE)-5,YSIZE-(.8*YSCALE)-5,10,10,0,360);
	gfx_fill_arc((7.7*XSCALE)-5,YSIZE-(.8*YSCALE)-5,10,10,0,360);

	//gfx_line(
	//gfx_line(
	//gfx_line(
	//gfx_line(
	//gfx_line(
	//gfx_line(
	//gfx_line(
	//gfx_line(
}
	
// void levelUp();

// void contorlTimer();

// void controlLives();

