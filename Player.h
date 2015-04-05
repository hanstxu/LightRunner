#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include <SDL.h>
#include "LTexture.h"

//Player texture
extern LTexture gPlayerTexture;

//The dot that will move around on the screen
class Player
{
public:
	//The dimensions of the player
	static const int PLAYER_WIDTH = 100;
	static const int PLAYER_HEIGHT = 100;

	//Maximum axis velocity of the player
	static const int PLAYER_VEL = SCREEN_WIDTH / 2;

	//Initializes the variables
	Player();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the player
	void move();

	//Shows the player on the screen
	void render();

	//Change the velocity
	void changeXVel(int amount);
	
	//Reset the velocity
	void resetXVel();

	//Get the position of the asteroid
	int getX() const;
	int getY() const;
private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;
};

#endif PLAYER_H