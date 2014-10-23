#include "bird.h"

Bird::Bird()
	: flying(false)
	, dTime(0.1)
{
	set_width(50.0f);
	set_height(50.0f);
	set_position(abfw::Vector3(50.0f, 300.0f, .0f));
}

void Bird::shoot(float i, float j)
{
	flightX = position().x;
	flightY = position().y;
	set_velocity(i, j);
	flying = true;
}

void Bird::update()
{
	if(flying)
	{
		flightX += velocity_.x * dTime;
		flightY -= velocity_.y * dTime;
		velocity_.y += (-9.8)*dTime;

		moveTo(flightX, flightY);
	}
}

void Bird::bounceGround(float e)
{
	velocity_.x = velocity_.x * 0.8;

	velocity_.y = -velocity_.y * e;

	shoot(velocity_.x, velocity_.y);
}

void Bird::bounceX(float e)
{
	velocity_.x = -velocity_.x * e;

	shoot(velocity_.x, velocity_.y);
}

void Bird::bounceY(float e)
{
	velocity_.x = velocity_.x * 0.8;

	velocity_.y = -velocity_.y * e;

	shoot(velocity_.x, velocity_.y);
}

void Bird::reset(float x, float y)
{
	flying = false;
	set_position(abfw::Vector3(x, y, .0f));
}
