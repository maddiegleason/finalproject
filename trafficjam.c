// Authors: Madeline Gleason and Taylor Rongaus
// Date: December 13, 2015
// final.c is the game "traffic jam"

#include <stdio.h>
#include <math.h>
#include <time.h>
#include "gfx4.h"
#define XSIZE 650
#define YSIZE 650
#define XSCALE 50 
#define YSCALE 50
#define GRID 13

char *num2str(int n);
void drawBackground();
void drawBase();
void printInfo(int *lives, int *score, int *levelup);
void drawTruck(int *dxtruck1, int *dxtruck2, int *dxtruck3, int *dxtruck4, int *dxtruck5, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives);
void drawCar(int *dxcar1, int *dxcar2, int *dxcar3, int *dxcar4, int *dxcar5, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives);
void drawplayer(int *dxplayer, int *dyplayer, int *player_xpos, int *player_ypos, int *win, int *collision, int *lives);
void resetplayer(int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer);
void drawX(int x, int y);
void checkEvents(char *w, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *win, int *lives, int *levelup, int *deltat);

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
	int dxtruck4 = 0;
	int dxtruck5 = 0;
	int dxcar1 = 0; 
	int dxcar2 = 0;
	int dxcar3 = 0;
	int dxcar4 = 0;
	int dxcar5 = 0;
	int player_xpos = 8;
	int player_ypos = 13;
	int collision = 0;
	int lives = 9;
	int win = 0;
	int score = 0;
	int levelup = 1;

	// Open Window
	gfx_open(XSIZE, YSIZE, "Traffic Jam");
	gfx_clear();
	gfx_color(255,255,255);
	gfx_changefont("12x24");
	gfx_text(XSIZE/2-40,YSIZE/2-15,"Traffic Jam");
	gfx_changefont("6x9");	gfx_text(XSIZE/2-20,YSIZE/2-5,"click to start");
	gfx_changefont("8x13");	gfx_text(XSIZE/2-30,YSIZE/2+50,"INSTRUCTIONS:");
	gfx_changefont("6x9");	gfx_text(XSIZE/2-22,YSIZE/2+65,"don't get hit");
	gfx_text(XSIZE/2-40,YSIZE/2+75,"you have nine lives");
	gfx_text(XSIZE/2-45,YSIZE/2+85,"each level gets faster");
	gfx_text(XSIZE/2-25,YSIZE/2+95,"press q to quit");

	while (1){
		if(gfx_event_waiting()){			w = gfx_wait();			if (w == 'q') return;		}
	
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
			printInfo(&lives, &score, &levelup);
			drawTruck(&dxtruck1, &dxtruck2, &dxtruck3, &dxtruck4, &dxtruck5, &player_xpos, &player_ypos, &collision, &dxplayer, &dyplayer, &lives);
			drawCar(&dxcar1, &dxcar2, &dxcar3, &dxcar4, &dxcar5, &player_xpos, &player_ypos, &collision, &dxplayer, &dyplayer, &lives);
			drawplayer(&dxplayer,&dyplayer,&player_xpos,&player_ypos,&win,&collision,&lives);		
			checkEvents(&w,&player_xpos,&player_ypos,&collision,&dxplayer,&dyplayer,&win,&lives,&levelup,&deltat);
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
}

char *num2str(int n) 
{
  static char a[10], *p = a;
  snprintf(p, 10, "%d", n);
  return p;
}

void drawBackground()
{	
	// Set Roads
	gfx_color(0, 0, 0);	
	gfx_fill_rectangle(0,YSIZE-2*YSCALE,XSIZE,2*YSCALE);
	gfx_fill_rectangle(0,0,XSIZE,YSCALE);
	gfx_color(158, 162, 158);	
	gfx_fill_rectangle(0,YSIZE-7*YSCALE,XSIZE,5*YSCALE);
	gfx_fill_rectangle(0,YSIZE-9*YSCALE,XSIZE,2*YSCALE);
	gfx_fill_rectangle(0,YSIZE-12*YSCALE,XSIZE,3*YSCALE);

	// Set Grid	int i, j, k;		gfx_color(255, 255, 0);	for (j= 2*YSCALE; j<=(YSIZE-3*YSCALE); j=j+YSCALE){		for (k = 0; k <=YSIZE; k=k+XSCALE/2){			gfx_line(k, j, k+XSCALE/4, j);		}	}
}

void drawBase()
{
	gfx_color(255, 255, 0);
	double k;
	for (k = 2.5; k <=10.5; k = k+2){
		gfx_fill_arc((k*XSCALE-20),(.5*YSCALE-20),40,40,0,360);
	}
}

void printInfo(int *lives, int *score, int *levelup){
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
	
	char *numlevel;
	numlevel = num2str(*levelup);
	gfx_text(5,YSIZE-55,"Level:");
	gfx_text(80,YSIZE-55,numlevel);
}

void drawTruck(int *dxtruck1, int *dxtruck2, int *dxtruck3, int *dxtruck4, int *dxtruck5, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives)
{
	// TRUCK1 GOING RIGHT	// Truck Body 	gfx_color(255,255,255);	gfx_fill_rectangle(XSCALE+0.25**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(1.5*XSCALE),(.6*YSCALE));	// Truck top 	gfx_color(210, 27, 27);	gfx_fill_rectangle(1.5*XSCALE+XSCALE+0.25**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(.5*XSCALE),(.6*YSCALE));	// Truck Middle 	gfx_color(0, 0, 0);	gfx_fill_rectangle(1.5*XSCALE+XSCALE+0.25**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));	// Truck Window	gfx_color(81, 227, 255);	gfx_fill_rectangle(1.85*XSCALE+XSCALE+0.25**dxtruck1*XSCALE,YSIZE-((2.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));	// TRUCK2 GOING LEFT	// Truck Body 	gfx_color(255,255,255);	gfx_fill_rectangle(XSIZE-1.5*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));	// Truck top 	gfx_color(210, 27, 27);	gfx_fill_rectangle(XSIZE-2.0*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(.5*XSCALE),(.6*YSCALE));	// Truck Middle 	gfx_color(0, 0, 0);	gfx_fill_rectangle(XSIZE-1.65*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));	// Truck Window	gfx_color(81, 227, 255);	gfx_fill_rectangle(XSIZE-2.0*XSCALE-0.5**dxtruck2*XSCALE,YSIZE-(4.8*YSCALE),(.15*XSCALE),(.6*YSCALE));	// TRUCK3 GOING RIGHT	gfx_color(255,255,255);	gfx_fill_rectangle(4*XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(1.5*XSCALE),(.6*YSCALE));	// Truck top 	gfx_color(210, 27, 27);	gfx_fill_rectangle(4.5*XSCALE+XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(.5*XSCALE),(.6*YSCALE));	// Truck Middle 	gfx_color(0, 0, 0);	gfx_fill_rectangle(4.5*XSCALE+XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));	// Truck Window	gfx_color(81, 227, 255);	gfx_fill_rectangle(4.85*XSCALE+XSCALE+0.5**dxtruck3*XSCALE,YSIZE-((6.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));	// TRUCK4 GOING LEFT	// Truck Body 	gfx_color(255,255,255);	gfx_fill_rectangle(XSIZE-7.5*XSCALE-0.6**dxtruck4*XSCALE,YSIZE-(8.8*YSCALE),(1.5*XSCALE),(.6*YSCALE));	// Truck top 	gfx_color(210, 27, 27);	gfx_fill_rectangle(XSIZE-8.0*XSCALE-0.6**dxtruck4*XSCALE,YSIZE-(8.8*YSCALE),(.5*XSCALE),(.6*YSCALE));	// Truck Middle 	gfx_color(0, 0, 0);	gfx_fill_rectangle(XSIZE-7.65*XSCALE-0.6**dxtruck4*XSCALE,YSIZE-(8.8*YSCALE),(.15*XSCALE),(.6*YSCALE));	// Truck Window	gfx_color(81, 227, 255);	gfx_fill_rectangle(XSIZE-8.0*XSCALE-0.6**dxtruck4*XSCALE,YSIZE-(8.8*YSCALE),(.15*XSCALE),(.6*YSCALE));	// TRUCK5 GOING RIGHT	gfx_color(255,255,255);	gfx_fill_rectangle(5*XSCALE+0.5**dxtruck5*XSCALE,YSIZE-((10.8)*YSCALE),(1.5*XSCALE),(.6*YSCALE));	// Truck top 	gfx_color(210, 27, 27);	gfx_fill_rectangle(5.5*XSCALE+XSCALE+0.5**dxtruck5*XSCALE,YSIZE-((10.8)*YSCALE),(.5*XSCALE),(.6*YSCALE));	// Truck Middle 	gfx_color(0, 0, 0);	gfx_fill_rectangle(5.5*XSCALE+XSCALE+0.5**dxtruck5*XSCALE,YSIZE-((10.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));	// Truck Window	gfx_color(81, 227, 255);	gfx_fill_rectangle(5.85*XSCALE+XSCALE+0.5**dxtruck5*XSCALE,YSIZE-((10.8)*YSCALE),(.15*XSCALE),(.6*YSCALE));
	
	// Increment truck positions	(*dxtruck1)++;	if (0.25**dxtruck1 > 18) {		*dxtruck1 = -17;	}	(*dxtruck2)++;	if (0.5**dxtruck2 > 14) {		*dxtruck2 = -10;	}	(*dxtruck3)++;	if (0.5**dxtruck3 > 15) {		*dxtruck3 = -10;	}	(*dxtruck4)++;	if (0.6**dxtruck2 > 13) {		*dxtruck4 = -15;	}	(*dxtruck5)++;	if (0.5**dxtruck5 > 13) {		*dxtruck5 = -20;	}
	
	// Check for collisions	if((((*player_xpos == *dxtruck1+1) || (*player_xpos == *dxtruck1)) && (*player_ypos == 11)) ||	 (((*player_xpos == *dxtruck2+8) || (*player_xpos == *dxtruck2+9)) && (*player_ypos == 9)) ||	 (((*player_xpos == *dxtruck3+4) || (*player_xpos == *dxtruck3+3)) && (*player_ypos == 7)) ||	 (((*player_xpos == *dxtruck4+9) || (*player_xpos == *dxtruck4+10)) && (*player_ypos == 5)) ||	 (((*player_xpos == *dxtruck5+5) || (*player_xpos == *dxtruck5+4)) && (*player_ypos == 3))) 
	 {		*collision = 1;		*lives = *lives - 1;		drawX(*player_xpos, *player_ypos-1);		resetplayer(player_xpos, player_ypos, collision, dxplayer, dyplayer);	}

}

void drawCar(int *dxcar1, int *dxcar2, int *dxcar3, int *dxcar4, int *dxcar5, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *lives)
{
	// CAR 1 GOING RIGHT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(4*XSCALE+0.2**dxcar1*XSCALE,YSIZE-(3.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(3.9*XSCALE+XSCALE+0.2**dxcar1*XSCALE,YSIZE-(3.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(3.9*XSCALE+XSCALE+0.2**dxcar1*XSCALE,YSIZE-(3.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(3.3*XSCALE+XSCALE+0.2**dxcar1*XSCALE,YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(3.6*XSCALE+XSCALE+0.2**dxcar1*XSCALE,YSIZE-(3.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// CAR 2 GOING LEFT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(XSIZE-(4*XSCALE)-0.8**dxcar2*XSCALE,YSIZE-(5.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(XSIZE-(4*XSCALE)-0.8**dxcar2*XSCALE,YSIZE-(5.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(XSIZE-(4*XSCALE)-0.8**dxcar2*XSCALE,YSIZE-(5.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(XSIZE-(3.4*XSCALE)-0.8**dxcar2*XSCALE,YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(XSIZE-(3.7*XSCALE)-0.8**dxcar2*XSCALE,YSIZE-(5.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// CAR 3 GOING RIGHT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(6*XSCALE+0.6**dxcar3*XSCALE,YSIZE-(7.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(5.9*XSCALE+XSCALE+0.6**dxcar3*XSCALE,YSIZE-(7.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(5.9*XSCALE+XSCALE+0.6**dxcar3*XSCALE,YSIZE-(7.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(5.3*XSCALE+XSCALE+0.6**dxcar3*XSCALE,YSIZE-(7.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(5.6*XSCALE+XSCALE+0.6**dxcar3*XSCALE,YSIZE-(7.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// CAR 4 GOING LEFT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(XSIZE-(8*XSCALE)-*dxcar4*XSCALE,YSIZE-(9.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(XSIZE-(8*XSCALE)-*dxcar4*XSCALE,YSIZE-(9.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(XSIZE-(8*XSCALE)-*dxcar4*XSCALE,YSIZE-(9.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(XSIZE-(7.4*XSCALE)-*dxcar4*XSCALE,YSIZE-(9.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(XSIZE-(7.7*XSCALE)-*dxcar4*XSCALE,YSIZE-(9.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// CAR 5 GOING RIGHT
	// Car Body
	gfx_color(165, 29, 124);
	gfx_fill_rectangle(2*XSCALE+0.4**dxcar5*XSCALE,YSIZE-(11.8*YSCALE),XSCALE,(.6*YSCALE));
	// Headlights
	gfx_color(253, 234, 59);
	gfx_fill_rectangle(1.9*XSCALE+XSCALE+0.4**dxcar5*XSCALE,YSIZE-(11.8*YSCALE),(.1*XSCALE),(.1*YSCALE));
	gfx_fill_rectangle(1.9*XSCALE+XSCALE+0.4**dxcar5*XSCALE,YSIZE-(11.3*YSCALE),(.1*XSCALE),(.1*YSCALE));
	// Windows
	gfx_color(81, 227, 255);
	gfx_fill_rectangle(1.3*XSCALE+XSCALE+0.4**dxcar5*XSCALE,YSIZE-(11.65*YSCALE),(.1*XSCALE),(.3*YSCALE));
	gfx_fill_rectangle(1.6*XSCALE+XSCALE+0.4**dxcar5*XSCALE,YSIZE-(11.65*YSCALE),(.1*XSCALE),(.3*YSCALE));

	// Increment car positions
	(*dxcar1)++;
	if (0.2**dxcar1 > 13) {
		*dxcar1 = -25;
	}
	(*dxcar2)++;
	if (0.6**dxcar2 > 13) {
		*dxcar2 = -15;
	}
	(*dxcar3)++;
	if (0.8**dxcar3 > 13) {
		*dxcar3 = -20;
	}
	(*dxcar4)++;
	if (*dxcar4 > 13) {
		*dxcar4 = -20;
	}
	(*dxcar5)++;
	if (0.4**dxcar5 > 13) {
		*dxcar5 = -15;
	}
	
	// Check for collisions
	if (((*player_xpos == *dxcar1+4) && (*player_ypos == 10)) || 
		((*player_xpos == *dxcar2+5) && (*player_ypos == 8)) ||
		((*player_xpos == *dxcar3+6) && (*player_ypos == 6)) ||
		((*player_xpos == *dxcar4+7) && (*player_ypos == 4)) ||
		((*player_xpos == *dxcar5+2) && (*player_ypos == 2)))
	{
		*collision = 1;
		*lives = *lives -1;
		drawX(*player_xpos, *player_ypos-1);
		resetplayer(player_xpos, player_ypos, collision, dxplayer, dyplayer);
	} 
}


void drawplayer(int *dxplayer, int *dyplayer, int *player_xpos, int *player_ypos, int *win, int *collision, int *lives)
{
	// red body
	gfx_color(255, 0, 0);
	gfx_fill_arc((7.25*XSCALE + *dxplayer*XSCALE), (YSIZE-(.8*YSCALE) + *dyplayer*YSCALE), 30, 30, 0, 360);
	// yellow body
	gfx_color(255, 255, 255);
	gfx_fill_arc((7.35*XSCALE + *dxplayer*XSCALE), (YSIZE-(.7*YSCALE) + *dyplayer*YSCALE), 20, 20, 0, 360);


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

void checkEvents(char *w, int *player_xpos, int *player_ypos, int *collision, int *dxplayer, int *dyplayer, int *win, int *lives, int *levelup, int *deltat) {

	// check to see if game level up
	if (*player_ypos == 1) {
		if ((*player_xpos == 3) || (*player_xpos == 5) || (*player_xpos == 7) || (*player_xpos == 9) ||(*player_xpos == 11)) {
			*levelup = *levelup + 1;
			*deltat = *deltat - 10000;
			resetplayer(player_xpos,player_ypos,collision,dxplayer,dyplayer);
			if (*levelup == 4) {
				*win = 1;
			}
		}
		else { // player stepped on invalid base
			*collision = 1;
			*lives = *lives - 1;
			drawX(*player_xpos, *player_ypos-1);
			resetplayer(player_xpos,player_ypos,collision,dxplayer,dyplayer);
		}
	}
	
	// display win screen	
	if (*win == 1) {
		*w = '+';
		gfx_clear();
		gfx_color(255,255,255);
		gfx_text(XSIZE/2-20,YSIZE/2-20,"YOU WIN");	
		gfx_changefont("6x9");
		gfx_text(XSIZE/2-25,YSIZE/2-10,"press 'q' to quit");
		if(gfx_event_waiting()){			*w = gfx_wait();			if (*w == 'q') return;		}
	}
	
	// check to see if out of lives
	if (*lives == 0) {
		*w = '+';
		gfx_clear();
		gfx_color(255,255,255);
		gfx_text(XSIZE/2-20,YSIZE/2-20,"YOU LOSE");	
		gfx_changefont("6x9");
		gfx_text(XSIZE/2-22,YSIZE/2-10,"press 'q' to quit");
		if(gfx_event_waiting()){			*w = gfx_wait();			if ((*w == 'q')) return;
		}
	}
}

