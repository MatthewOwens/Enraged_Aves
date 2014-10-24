#ifndef BLOCK_H
#define BLOCK_H
#include "game_object.h"
#include "graphics\colour.h"

class Block : public GameObject
{
public:
	enum Material {GLASS, WOOD, STONE};
	enum Shape {SQUARE, RECT, TRIANGLE};

	//Block(Material mat, Shape shape, int x, int y);
	Block();
	~Block(void);
	Block(Material mat, Shape shape, int x, int y);
	void Update(abfw::Vector2 acceleration, int pWidth, int pHeight);
	void TakeDamage(abfw::Vector2 incomingVelocity);
	float bouncyness();
	inline int hitpoints() { return hitpoints_; }
private:
	Material matVal_;
	Shape shapeVal_;
	int hitpoints_;
	float bounce;
};

#endif