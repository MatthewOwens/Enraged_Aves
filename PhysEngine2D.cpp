#include "PhysEngine2D.h"
#include <iostream>


PhysEngine2D::PhysEngine2D(void)
{
}


PhysEngine2D::~PhysEngine2D(void)
{
}

void PhysEngine2D::Init(int platformW, int platformH)
{
	screenW_ = platformW;
	screenH_ = platformH;
}


void PhysEngine2D::WallCollision(GameObject& object1)
{
	abfw::Vector3 pos = object1.position();
	abfw::Vector2 vel = object1.velocity();
	float width = object1.width();
	float height = object1.height();

	// Collision between the bottom of the object and the bottom of the screen
	if(pos.y + (height * 0.5f) > screenH_)
	{
		object1.set_position(pos.x, screenH_ - (height * 0.5f), 0);
		object1.set_velocity(vel.x, 0);
	}
<<<<<<< HEAD
	return false;
=======

	// Collision between the top of the object and the top of the screen
	if(pos.y - (height * 0.5f) < 0)
	{
		object1.set_position(pos.x, (height * 0.5f), 0);
		object1.set_velocity(vel.x, 0);
	}

	// Collision between the right of the object and the right of the screen
	if(pos.x + (width * 0.5f) > screenW_)
	{
		object1.set_position(pos.x - (width * 0.5f), pos.y, 0);
		object1.set_velocity(0, vel.y);
	}

	// Collision between the left of the object and the left of the screen
	if(pos.x - (width * 0.5f) < 0)
	{
		object1.set_position((width * 0.5f), pos.y, 0);
		object1.set_velocity(0, vel.y);
	}
>>>>>>> 5535a8eddcf9b9445aa49765debfc21192bf362e
}

void PhysEngine2D::SwapVelocities(GameObject& object1, GameObject& object2)
{
	// Swapping the velocities
	object1.set_velocity(object2.velocity());
	object2.set_velocity(object1.velocity());
}

void PhysEngine2D::ReverseVelocities(GameObject& object1, GameObject& object2)
{
	// Inverting the velocities
	object1.set_velocity(object1.velocity() * -1);
	object2.set_velocity(object2.velocity() * -1);
}

void PhysEngine2D::Stop(GameObject& object1, GameObject& object2,
	const abfw::Vector2 gravity)
{
	// Stopping the objects
	object1.set_velocity(gravity * -1);
	object2.set_velocity(gravity * -1);
}

void PhysEngine2D::RealVelocities(GameObject& object1, GameObject& object2)
{
	float halfw1 = object1.width()*0.5f;
	float halfh1 = object1.height()*0.5f;
	float halfw2 = object2.width()*0.5f;
	float halfh2 = object2.height()*0.5f;
	float posx1 = object1.position().x;
	float posy1 = object1.position().y;
	float posx2 = object2.position().x;
	float posy2 = object2.position().y;

	// If there was collision on the right side of object1
	//if(posx1 + halfw1 < posx2 - halfw2)
		/// TODO: Collision Responses
}

bool PhysEngine2D::BoundingBox(const GameObject& object1, const GameObject& object2)
{
	float halfw1 = object1.width()*0.5f;
	float halfh1 = object1.height()*0.5f;
	float halfw2 = object2.width()*0.5f;
	float halfh2 = object2.height()*0.5f;
	float posx1 = object1.position().x;
	float posy1 = object1.position().y;
	float posx2 = object2.position().x;
	float posy2 = object2.position().y;

	if((posx1 + halfw1) < (posx2 - halfw2)) return false;	// Right side of 1 doesn't collide with left side of 2
	if((posx1 - halfw1) > (posx2 + halfw2)) return false;	// Left side of 1 doesn't collide with the right side of 2
	if((posy1 + halfh1) < (posy2 - halfh2)) return false;	// Bottom of 1 doesn't collide with top of 2
	if((posy1 - halfh1) > (posy2 + halfh2)) return false;	// Top of 1 doesn't collide with bottom of 2
	return true;	// There was collision
}

int PhysEngine2D::BoundingBoxSides(const GameObject& object1, const GameObject& object2)
{
	float halfw1 = object1.width()*0.5f;
	float halfh1 = object1.height()*0.5f;
	float halfw2 = object2.width()*0.5f;
	float halfh2 = object2.height()*0.5f;
	float posx1 = object1.position().x;
	float posy1 = object1.position().y;
	float posx2 = object2.position().x;
	float posy2 = object2.position().y;

	if(((posy1 - halfh1) < (posy2 + halfh2)) && (posy1 > posy2))// top
		return 1;
	if(((posy1 + halfh1) > (posy2 - halfh2)) && (posy1 < posy2))// bottom
		return 2;
	if(((posx1 - halfw1) < (posx2 + halfw2)) && (posx1 > posx2))// left
		return 3;
	if(((posx1 + halfw1) > (posx2 - halfw2)) && (posx1 < posx2))// right
		return 4;

	return 0;
}

void PhysEngine2D::Seperate(GameObject& object1, GameObject& object2)
{
	float halfw1 = object1.width()*0.5f;
	float halfh1 = object1.height()*0.5f;
	float halfw2 = object2.width()*0.5f;
	float halfh2 = object2.height()*0.5f;
	float posx1 = object1.position().x;
	float posy1 = object1.position().y;
	float posx2 = object2.position().x;
	float posy2 = object2.position().y;

	switch (BoundingBoxSides(object1, object2))
	{
	case 1:
		if(posy1 - halfh1 - halfh2 - 1> 0)
			object2.moveTo(posx2, posy1 - halfh1 - halfh2 - 1);
		else
			object1.moveTo(posx1, posx2 + halfh1 + halfh2 + 1);
		break;
	case 2:
		if(posy1 + halfh1 + halfh2 + 1 < screenH_ - halfh2)
			object2.moveTo(posx2, posy1 + halfh1 + halfh2 + 1);
		else
			object1.moveTo(posx1, posy2 - halfh2 - halfh1 - 1);
		break;
	case 3:
		object2.moveTo(posx1 - halfw1 - halfw2 - 1, posy2);
		break;
	case 4:
		object2.moveTo(posx1 + halfw1 + halfw2 + 1, posy2);
		break;
	case 0:
		//std::cout << "Something went wrong, seperate was called when two blocks wern't colliding" << std::endl;
		break;
	}
}