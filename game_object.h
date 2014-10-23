#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include <graphics/sprite.h>

class GameObject : public abfw::Sprite
{
public:
	GameObject();
	virtual ~GameObject();

	/// @alter the sprite_ position based on velocity_
	/// @param[in] the width and height of the platform screen
	void move(int pWidth, int pHeight);

	/// @param[in] the x and y coords to move the object to
	void moveTo(float targetX, float targetY);

	/// @param[in] the game_object to check for collision with
	/// @param[out] wether or not there was collision
	bool collision_check(GameObject target);

	/// @param[out] the velocity of the game object
	inline abfw::Vector2 velocity(){return velocity_;}

	/// @param[in] the new velocity of the game object
	inline void set_velocity(float x, float y){velocity_.x = x; velocity_.y = y;}

	/// @param[in] the new velocity of the game object
	inline void set_velocity(abfw::Vector2 velocity) {velocity_ = velocity;}

protected:
	abfw::Vector2 velocity_;
	int mass_;
};

#endif // _GAME_OBJECT_H