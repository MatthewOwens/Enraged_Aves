#pragma once
#include "game_object.h"
class PhysEngine2D
{
public:
	PhysEngine2D(void);
	~PhysEngine2D(void);

	// Collision Detection Algorithms
	///@param[in] The game objects to check for collision
	///@param[out] Wether or not there was collision
	bool BoundingBox(const GameObject& object1, const GameObject& object2);

	///@param[in] The game objects to check for collision
	///@param[out] Wether or not there was collision
	bool BoundingCircle(const GameObject& object1, const GameObject& object2);

	// Collision responses
	///@param[in] The game objects who's velocities we want to swap
	void SwapVelocities(GameObject& object1, GameObject& object2);
	///@param[in] The game objects who's velocities we want to reverse
	void ReverseVelocities(GameObject& object1, GameObject& object2);
	///@param[in] The game objects who's new velocities we want to calculate
	void RealVelocities(GameObject& object1, GameObject& object2);

	// Environmental collision
	///@param[in] The game object that we're going to check for environmental collision with
	void WallCollision(GameObject& object1);
};

