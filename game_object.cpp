#include "game_object.h"

GameObject::GameObject()
{
	velocity_ = abfw::Vector2(0,0);
}

GameObject::~GameObject()
{
}

void GameObject::move(int pWidth, int pHeight)
{
	// Moving based on the velocity
	set_position(position_.x + velocity_.x, position_.y + velocity_.y, position_.z);
}

void GameObject::moveTo(float targetX, float targetY)
{
	abfw::Vector3 target(targetX, targetY, 0);
	set_position(target);
}

bool GameObject::collision_check(GameObject target)
{
	float halfW = width_ * 0.5;
	float halfTW = target.width() * 0.5;
	float halfH = height_ * 0.5f;
	float halfTH = target.height() * 0.5;
	float tPosX = target.position().x;
	float tPosY = target.position().y;

	if((position_.x + halfW) < (tPosX - halfTW)) return false;	// Right side doesn't collide with left side of target
	if((position_.x - halfW) > (tPosX + halfTW)) return false;	// Left side doesn't collide with right side of target
	if((position_.y + halfH) < (tPosY - halfTH)) return false;	// Top of current doesn't collide with bottom of target
	if((position_.y - halfH) > (tPosY + halfTH)) return false;	// Bottom of current doesn't collide with top of target
	return true;	// Collision
}