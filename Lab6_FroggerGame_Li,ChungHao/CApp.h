//==============================================================================
// Frogger to its pond
//==============================================================================
#ifndef _CAPP_H_
#define _CAPP_H_

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <time.h>
#include <string>


#include <SDL.h>
#include <SDL_ttf.h>			//for fonts
#include <SDL_mixer.h>          //for sound and music


#include "CPlayer.h"
#include "CScroll_Player.h"
#include "CSpriteSheet.h"
#include "mywindow.h"


#define TICK_INTERVAL       10
#define NUM_SPRITES         16
#define MAX_SPEED           1

//====================================================================================================
class CApp
{
	private:
		bool            Running;
		TTF_Font * font;					// Pointer to font, stores the type and size of the font
		TTF_Font * font1;					// Pointer to font1, stores the type and size of the font

		SDL_Color color;					// Text Color
		SDL_Color color1;					// Text Color

		char message[100];					// Message String

		SDL_Surface * messageSurface;		// Pointer to the Surface where we display the message
		SDL_Texture * messageTexture;		// Pointer to the texture, converts the surface to texture
		SDL_Rect messageRect;				// Location

		//The music that will be played
		Mix_Music *gMusic = NULL;

		//Sound effects that will be used
		Mix_Chunk *gScratch = NULL;
		Mix_Chunk* gScratch1 = NULL;
		Mix_Chunk* gScratch2 = NULL;
		

		Uint32 next_time;
		SDL_Window *window;
		SDL_Renderer *renderer;

		CPlayer car[NUM_SPRITES]; // car array
		CPlayer log[NUM_SPRITES]; //log array
		
		CPlayer line[NUM_SPRITES]; //line array for developping needs
		CPlayer top; //the green platform to cover the background on the top, so it won't scroll with it
		
		CScroll_Player background;
		CPlayer frog;				

		int live, score;					// Variables to Store number of lives and score
		bool gameOver = false;
		bool gameWin = false;
		bool freezeFrog = false;
	public:
		CApp();
		Uint32 time_left(void);
		int OnExecute();

	public:
		bool OnInit();
		
		void OnEvent(SDL_Event* Event);

		void OnLoop();

		void OnRender();

		void OnCleanup();

		// Helper functions

		bool loadMedia();

		bool check_collision(SDL_Rect A, SDL_Rect B);
		bool check_LogCollision(SDL_Rect A, SDL_Rect B);
		bool check_onLog(SDL_Rect A, SDL_Rect B);
		void displayGameStats(int x, int y, const char* formattedString, int number);
		void displayGameOver(int x, int y, const char* formattedString);

		void MoveSprites();	
		
};

//==============================================================================

#endif
