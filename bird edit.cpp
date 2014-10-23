#include "bird.h"

Bird::Bird()
	: flying(false)
	, dTime(0.1)
{
	set_width(50.0f);
	set_height(50.0f);
	set_position(abfw::Vector3(50.0f, 300.0f, .0f));
	
	////////////////sprite creation////////////////////////////////
	for (int i = 0;i<32;i++)
	{
		body[i].set_position(abfw::Vector3(50.0f, 300.0f, 0.f));
		body[i].set_colour(0xff00ff00);
	}
	eyes[0].set_position(abfw::Vector3(body[0].position().x - 8.0f, body[0].position().y - 8.0f, 0.f));
	eyes[1].set_position(abfw::Vector3(body[0].position().x + 8.0f, body[0].position().y - 8.0f, 0.f));
	beak.set_position(abfw::Vector3(body[0].position().x, body[0].position().y+8.0f, 0.f));

	float k = 0;
	for (int i = 0;i<32;i++)
	{
		body[i].set_rotation(k);
		k+=0.28125;
	}
	beak.set_rotation(0.7873163375f);

	for (int i = 0;i<32;i++)
	{
		body[i].set_width(50.0f);
		body[i].set_height(50.0f);
	}
	for (int i =0;i<2;i++)
	{
		eyes[i].set_width(12.0f);
		eyes[i].set_height(12.0f);
	}
	beak.set_width(12.0f);
	beak.set_height(12.0f);
	beak.set_colour(0xff00ffff);
	///////////////////////////////////////////////
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
	////////////////////////////////////////////////////

		for (int i = 1;i<32;i++)
	{
		body[i].set_position(abfw::Vector3(.position().x,position().y, o.f));
		eyes[0].set_position(abfw::Vector3(position().x - 8.0f, position().y - 8.0f, 0.f));
		eyes[1].set_position(abfw::Vector3(position().x + 8.0f, position().y - 8.0f, 0.f));
		beak.set_position(abfw::Vector3(position().x, position().y+8.0f, 0.f));
	}
	////////////////////////////////////////////////////
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
