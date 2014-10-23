#pragma once
#include "game_object.h"
class PhysEngine2D
{
public:
	PhysEngine2D(void);
	~PhysEngine2D(void);
	void Init(int platformW, int platformH);

	// Collision Detection Algorithms
	///@param[in] The game objects to check for collision
	///@param[out] Wether or not there was collision, with respect to object1:
	bool BoundingBox(const GameObject& object1, const GameObject& object2);

	///@param[in] The game objects to check for collision
	///@param[out] where collision is occuring relative to object1
	/// 1 - Top, 2 - bottom, 3 - left, 4 - right
	int BoundingBoxSides(const GameObject& object1, const GameObject& object2);

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
	///@param[in] The game objects we want to stop and the current gravity
	void Stop(GameObject& object1, GameObject& object2, const abfw::Vector2 gravity);

	// Environmental collision
	///@param[in] The game object that we're going to check for environmental collision with
	void WallCollision(GameObject& object1);

private:
	int screenW_;
	int screenH_;
};

