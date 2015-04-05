#include "res_path.h"
#include <stdio.h>
#include <time.h>
#include <SDL_image.h>
#include "globals.h"
#include "LTexture.h"
#include "Player.h"
#include "Asteroid.h"
#include "Leap.h"
#include "SimpleListener.h"
using namespace Leap;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//Scene textures
LTexture gBGTexture;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load player texture
	if (!gPlayerTexture.loadFromFile("player.bmp"))
	{
		printf("Failed to load player texture!\n");
		success = false;
	}

	//Load player texture
	if (!gAsteroidTexture.loadFromFile("asteroid.png"))
	{
		printf("Failed to load asteroid texture!\n");
		success = false;
	}

	//Load background texture
	if (!gBGTexture.loadFromFile("bg.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}

bool checkCollision(Player* p, Asteroid* a)
{
	if (p->getX() != a->getX())
		return false;

	return p->getY() <= a->getY();
}

void close()
{
	//Free loaded images
	gPlayerTexture.free();
	gBGTexture.free();
	gAsteroidTexture.free();

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The player that will be moving around on the screen
			Player player;

			//The asteroid coming after the player
			Asteroid asteroid(SCREEN_WIDTH / 4, -SCREEN_HEIGHT / 4), asteroid2(SCREEN_WIDTH / 4 * 3, -SCREEN_HEIGHT/4*3), asteroid3(SCREEN_WIDTH / 4, -SCREEN_HEIGHT * 2);

			//The background scrolling offset
			int scrollingOffset = 0;

			Controller testController;
			SimpleListener testListener;
			testController.addListener(testListener);

			unsigned long timeStart = clock();

			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the dot
					player.handleEvent(e);
				}

				// LeapMotion controls
				switch (leapDirection) {
					case 2: player.changeXVel(-SCREEN_WIDTH / 2); break;
					case 1: player.changeXVel(SCREEN_WIDTH / 2);  break;
					default: break;
				}

				//Move the player
				player.move();
				
				//Move the asteroids
				asteroid.move();
				asteroid2.move();
				asteroid3.move();

				player.resetXVel();

				//Check if there was a collision
				if (checkCollision(&player, &asteroid))
					break;

				if (checkCollision(&player, &asteroid2))
					break;

				if (checkCollision(&player, &asteroid3))
					break;

				//Scroll background
				++scrollingOffset;
				if (scrollingOffset > gBGTexture.getHeight())
				{
					scrollingOffset = 0;
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background
				gBGTexture.render(0, scrollingOffset);
				gBGTexture.render(0, scrollingOffset - gBGTexture.getHeight());

				//Render objects
				player.render();
				asteroid.render();
				asteroid2.render();
				asteroid3.render();

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
			//Ending Game Screen
			unsigned long score = clock() - timeStart;

			std::cout << score << std::endl;

			testController.removeListener(testListener);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}