#ifndef _BIRD_H
#define _BIRD_H

#include "game_object.h"
#include <cmath>

class Bird: public GameObject
{
	public:
		Bird();

		void update();
		void shoot(float i, float j);
		void bounceGround(float e);
		void bounceX(float e);
		void bounceY(float e);
		void reset(float x, float y);

	protected:
		float dTime;	
		bool flying;
		float flightX, flightY;
};

#endif