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
void drawTurtle(int *dx);

int main()
{
	char c;
	int dx = 0;					// initiate movement in the x direction
	int deltat = 25000;

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
		drawTurtle(&dx);

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
	gfx_color(108, 105, 105);
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
			gfx_fill_arc((k*XSCALE-20),(.5*YSCALE-20),40,40,0,360);
		}
}

// NOTE: for moving objects truck, car, and log only need to increment x position
// Cannot figure out how to generate multiple objects in one line going across
// tried for loop incrementing i in the x position and that just changed speed? 

void drawTruck(int *dx)
{
	// TRUCK GOING RIGHT
	// Truck Body 
	gfx_color(255,255,255);
	gfx_fill_rectangle(0+*dx,YSIZE-(2.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	// Truck top 
	gfx_color(210, 27, 27);
	gfx_fill_rectangle((1.5*XSCALE) + *dx,YSIZE-(2.8*YSCALE),(.5*XSCALE),(.6*YSCALE));
	// Truck Middle 
	gfx_color(0, 0, 0);
	gfx_fill_rectangle((1.5*XSCALE) + *dx,YSIZE-(2.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	// Truck Window
	gfx_color(81, 227, 255);
	gfx_fill_rectangle((1.85*XSCALE) + *dx, YSIZE-(2.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	(*dx)++;

	// TRUCK GOING RIGHT
	// Truck Body 
	gfx_color(255,255,255);
	gfx_fill_rectangle(2+*dx,YSIZE-(6.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	// Truck top 
	gfx_color(210, 27, 27);
	gfx_fill_rectangle((1.5*XSCALE) + *dx,YSIZE-(6.8*YSCALE),(.5*XSCALE),(.6*YSCALE));
	// Truck Middle 
	gfx_color(0, 0, 0);
	gfx_fill_rectangle((1.5*XSCALE) + *dx,YSIZE-(6.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	// Truck Window
	gfx_color(81, 227, 255);
	gfx_fill_rectangle((1.85*XSCALE) + *dx, YSIZE-(6.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	(*dx)++;

	// TRUCK GOING LEFT
	// Truck Body 
	gfx_color(255,255,255);
	gfx_fill_rectangle(XSIZE-(1.5*XSCALE) - *dx,YSIZE-(4.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	// Truck top 
	gfx_color(210, 27, 27);
	gfx_fill_rectangle(XSIZE-(2.0*XSCALE) - *dx,YSIZE-(4.8*YSCALE),(.5*XSCALE),(.6*YSCALE));
	// Truck Middle 
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(XSIZE-(1.65*XSCALE) - *dx,YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	// Truck Window
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(XSIZE-(2.00*XSCALE) - *dx, YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	(*dx)--;

}

void drawCar(int *dx)
{
	// CAR GOING RIGHT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(((4*XSCALE) + *dx),YSIZE-(3.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(((4.9*XSCALE) + *dx),YSIZE-(3.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(((4.9*XSCALE) + *dx),YSIZE-(3.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(((4.3*XSCALE) + *dx),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(((4.6*XSCALE) + *dx),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	(*dx)++;

	// CAR GOING LEFT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle((XSIZE-(4*XSCALE) - *dx),YSIZE-(5.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle((XSIZE-(4*XSCALE) - *dx),YSIZE-(5.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle((XSIZE-(4*XSCALE) - *dx),YSIZE-(5.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle((XSIZE-(3.4*XSCALE) - *dx),YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle((XSIZE-(3.7*XSCALE) - *dx),YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	(*dx)--;

}

void drawLog(int *dx)
{
	gfx_color(121, 68, 7);
	gfx_fill_rectangle((7*XSCALE)+*dx,YSIZE-(9.8*YSCALE),(2.5*XSCALE),(.6*YSCALE));
	gfx_fill_rectangle((3*XSCALE)+*dx,YSIZE-(10.8*YSCALE),(2*XSCALE),(.6*YSCALE));
	gfx_fill_rectangle((9*XSCALE)+*dx,YSIZE-(11.8*YSCALE),(3*XSCALE),(.6*YSCALE));
	
	(*dx)++;
}

void drawTurtle(int *dx)
{
	// HOW CAN WE MAKE THREE TURTLES WITH A FOR LOOP? 
	// Turtle 1
	gfx_color(9, 110, 23);
	gfx_fill_arc((5*XSCALE - (.25*XSCALE) + *dx), (YSIZE-(9.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 0, 180);
	gfx_fill_arc((5*XSCALE - (.25*XSCALE) + *dx), (YSIZE-(9.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 180, 360);
	gfx_fill_arc((5*XSCALE-(.25*XSCALE)+ 27 + *dx), (YSIZE-9.45*YSCALE)-7.5, 15, 15, 0, 360);
	gfx_color(255, 255, 255);
	gfx_fill_arc((5*XSCALE-(.25*XSCALE)+ 37 + *dx), (YSIZE-9.25*YSCALE)-7.5, 5, 5, 0, 360);
	gfx_fill_arc((5*XSCALE-(.25*XSCALE)+ 37 + *dx), (YSIZE-9.45*YSCALE)-7.5, 5, 5, 0, 360);
	gfx_color(0, 0, 0);
	gfx_fill_arc((5*XSCALE-(.25*XSCALE)+ 39 + *dx), (YSIZE-9.25*YSCALE)-7.5, 4, 4, 0, 360);
	gfx_fill_arc((5*XSCALE-(.25*XSCALE)+ 39 + *dx), (YSIZE-9.45*YSCALE)-7.5, 4, 4, 0, 360);
	
	// Turtle 2
	gfx_color(9, 110, 23);
	gfx_fill_arc((4*XSCALE - (.25*XSCALE) + *dx), (YSIZE-(9.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 0, 180);
	gfx_fill_arc((4*XSCALE - (.25*XSCALE) + *dx), (YSIZE-(9.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 180, 360);
	gfx_fill_arc((4*XSCALE-(.25*XSCALE)+ 27 + *dx), (YSIZE-9.45*YSCALE)-7.5, 15, 15, 0, 360);
	gfx_color(255, 255, 255);
	gfx_fill_arc((4*XSCALE-(.25*XSCALE)+ 37 + *dx), (YSIZE-9.25*YSCALE)-7.5, 5, 5, 0, 360);
	gfx_fill_arc((4*XSCALE-(.25*XSCALE)+ 37 + *dx), (YSIZE-9.45*YSCALE)-7.5, 5, 5, 0, 360);
	gfx_color(0, 0, 0);
	gfx_fill_arc((4*XSCALE-(.25*XSCALE)+ 39 + *dx), (YSIZE-9.25*YSCALE)-7.5, 4, 4, 0, 360);
	gfx_fill_arc((4*XSCALE-(.25*XSCALE)+ 39 + *dx), (YSIZE-9.45*YSCALE)-7.5, 4, 4, 0, 360);
	
	// Turtle 3	
	gfx_color(9, 110, 23);
	gfx_fill_arc((3*XSCALE - (.25*XSCALE) + *dx), (YSIZE-(9.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 0, 180);
	gfx_fill_arc((3*XSCALE - (.25*XSCALE) + *dx), (YSIZE-(9.7*YSCALE)), (.7*YSCALE), (.5*YSCALE), 180, 360);
	gfx_fill_arc((3*XSCALE-(.25*XSCALE)+ 27 + *dx), (YSIZE-9.45*YSCALE)-7.5, 15, 15, 0, 360);
	gfx_color(255, 255, 255);
	gfx_fill_arc((3*XSCALE-(.25*XSCALE)+ 37 + *dx), (YSIZE-9.25*YSCALE)-7.5, 5, 5, 0, 360);
	gfx_fill_arc((3*XSCALE-(.25*XSCALE)+ 37 + *dx), (YSIZE-9.45*YSCALE)-7.5, 5, 5, 0, 360);
	gfx_color(0, 0, 0);
	gfx_fill_arc((3*XSCALE-(.25*XSCALE)+ 39 + *dx), (YSIZE-9.25*YSCALE)-7.5, 4, 4, 0, 360);
	gfx_fill_arc((3*XSCALE-(.25*XSCALE)+ 39 + *dx), (YSIZE-9.45*YSCALE)-7.5, 4, 4, 0, 360);
}

void drawFrog()
{
	// NOTE: frog will move in the x and y direction where dx and dy will be incremented by XSCALE and YSCALE respectively 
	// frog green body
	gfx_color(43, 255, 0);
	gfx_fill_arc((7.5*XSCALE - (.25*XSCALE)), (YSIZE-(.4*YSCALE)-(.4*YSCALE)), (.5*YSCALE), (.7*YSCALE), 0, 180);
	gfx_fill_arc((7.5*XSCALE - (.25*XSCALE)), (YSIZE-(.4*YSCALE)-(.4*YSCALE)), (.5*YSCALE), (.7*YSCALE), 180, 360);
	
	// frog yellow body
	gfx_color(243, 255, 58);
	gfx_fill_arc((7.5*XSCALE - (.15*XSCALE)), (YSIZE-(.3*YSCALE)-(.4*YSCALE)), (.3*YSCALE), (.5*YSCALE), 0, 180);
	gfx_fill_arc((7.5*XSCALE - (.15*XSCALE)), (YSIZE-(.3*YSCALE)-(.4*YSCALE)), (.3*YSCALE), (.5*YSCALE), 180, 360);
	
	// frog eyes
	gfx_color(239, 20, 239);
	gfx_fill_arc((7.3*XSCALE)-5,YSIZE-(.7*YSCALE)-5,10,10,0,360);
	gfx_fill_arc((7.7*XSCALE)-5,YSIZE-(.7*YSCALE)-5,10,10,0,360);
}
	
// void levelUp();

// void contorlTimer();

// void controlLives();

