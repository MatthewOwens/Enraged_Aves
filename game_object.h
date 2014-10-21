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

	/// @param[out] the velocity of the game object
	inline abfw::Vector2 velocity(){return velocity_;}

	/// @param[in] the new velocity of the game object
	inline void set_velocity(int x, int y){velocity_.x = x; velocity_.y = y;}

	/// @param[in] the new velocity of the game object
	inline void set_velocity(abfw::Vector2 velocity) {velocity_ = velocity;}

	///@param[out] the mass of the game object
	inline int mass(){return mass;}
private:
	abfw::Vector2 velocity_;
	int mass;
};

#endif // _GAME_OBJECT_H