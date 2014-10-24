#ifndef _BIRD_H
#define _BIRD_H

#include "game_object.h"
#include "graphics/sprite_renderer.h"
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
		inline bool flight() {return flying; }
		void render(abfw::SpriteRenderer* sr);

		Sprite body[32];
		Sprite eyes[2];
		Sprite beak;

	protected:
		float dTime;	
		bool flying;
		float flightX, flightY;
};

#endif