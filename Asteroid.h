#ifndef ASTEROID_H
#define ASTEROID_H

#include "LTexture.h"

//Player texture
extern LTexture gAsteroidTexture;

class Asteroid {
public:
	//The dimensions of the asteroid
	static const int ASTEROID_WIDTH = 64;
	static const int ASTEROID_HEIGHT = 64;
	
	Asteroid(int xPos, int yPos);
	
	//move the asteroid
	void move();
	
	//Shows the asteroid on the screen
	void render();

	//Get the position of the asteroid
	int getX() const;
	int getY() const;

private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelY;
};

#endif