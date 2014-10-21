#include "game_object.h"

GameObject::GameObject()
{
	velocity_ = abfw::Vector2(0,0);
	mass = 0;
}

GameObject::~GameObject()
{
}

void GameObject::move(int pWidth, int pHeight)
{
	// Moving based on the velocity
	set_position(position_.x + velocity_.x, position_.y + velocity_.y, position_.z);

	// Changing the velocity if the sprite is offscreen
	if(position_.x - (width_ * 0.5) <= 0 || position_.x + (width_ * 0.5) > pWidth)
		velocity_.x *= -1;
	if(position_.y - (height_ * 0.5) <= 0 || position_.y + (height_ * 0.5) > pHeight)
		velocity_.y *= -1;
}