#include "Asteroid.h"
#include "globals.h"
#include "LTexture.h"
#include <stdlib.h>
#include <time.h>

LTexture gAsteroidTexture;

Asteroid::Asteroid(int xPos, int yPos)
{
	//Initialize the offsets
	mPosX = xPos;
	mPosY = yPos;
	srand(time(NULL));
	int vel = rand() % 3 + 2;
	mVelY = vel;
}

void Asteroid::move()
{
	//Move the Asteroid up or down
	mPosY += mVelY;

	//If the Asteroid went too far up
	if (mPosY < 0 && mVelY < 0)
	{
		//Move back
		mPosY -= mVelY;
		mPosY = 0;
	}
	//If the asteroid went too far down
	else if (mPosY + ASTEROID_HEIGHT > SCREEN_HEIGHT && mVelY > 0)
	{

		// Initialize a new position
		srand(time(NULL));
		int randNum = rand() % 10 + 1;
		int vel = rand() % 3 + 2;
		mPosY = -SCREEN_HEIGHT/4 * randNum;
		mVelY = vel;
	}
}

void Asteroid::render()
{
	//Show the Asteroid
	gAsteroidTexture.render(mPosX, mPosY);
}

int Asteroid::getX() const {
	return mPosX;
}

int Asteroid::getY() const {
	return mPosY + ASTEROID_HEIGHT/4;
}