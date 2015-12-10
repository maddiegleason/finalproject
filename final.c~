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
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "gfx2.h"
#define XSIZE 650
#define YSIZE 650
#define XSCALE 50 
#define YSCALE 50

void drawBackground();
void drawObjects();

int main()
{
	char c;

	// Open Window
	gfx_open(XSIZE, YSIZE, "Frogger");

	while (1){
		
		drawBackground();
		drawObjects();
	
		c = gfx_wait();
		if (c == 'q') return 0;
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
}

void drawObjects()
{
	// drawTruck
	gfx_color(255,255,255);
	gfx_fill_rectangle(0,YSIZE-(2.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));
	
	gfx_color(210, 27, 27);
	gfx_fill_rectangle((1.5*XSCALE),YSIZE-(2.8*YSCALE),(.5*XSCALE),(.6*YSCALE));
	
	gfx_color(0, 0, 0);
	gfx_fill_rectangle((1.5*XSCALE),YSIZE-(2.8*YSCALE),(.15*XSCALE),(.6*YSCALE));
	
	gfx_color(81, 227, 255);
	gfx_fill_rectangle((1.85*XSCALE), YSIZE-(2.8*YSCALE),(.15*XSCALE),(.6*YSCALE));

	// drawCar
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(4*XSCALE,YSIZE-(3.8*YSCALE),XSCALE,(.6*YSCALE));
	
	gfx_color(253, 234, 59);
	gfx_fill_rectangle((4.9*XSCALE),YSIZE-(3.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle((4.9*XSCALE),YSIZE-(3.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	
	gfx_color(81, 227, 255);
	gfx_fill_rectangle((4.3*XSCALE),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle((4.6*XSCALE),YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// drawLog
	gfx_color(121, 68, 7);
	gfx_fill_rectangle((7*XSCALE),YSIZE-(9.8*YSCALE),(2.5*XSCALE),(.6*YSCALE));
	gfx_fill_rectangle((3*XSCALE),YSIZE-(10.8*YSCALE),(2*XSCALE),(.6*YSCALE));
	gfx_fill_rectangle((9*XSCALE),YSIZE-(11.8*YSCALE),(3*XSCALE),(.6*YSCALE));

	// drawFrog
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

	// drawLilies
	//gfx_fill_arc(
	//gfx_fill_arc(
	//gfx_fill_arc(
	//gfx_fill_arc(
	//gfx_fill_arc(


}	

// void moveFrog();

// void moveCar();

// void moveLog();

// void moveTurtle();

// void levelUp();

// void contorlTimer();

// void controlLives();

