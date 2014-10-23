#include "Block.h"
#include <iostream>

Block::Block(Block::Material mat, Block::Shape shape, int x, int y)
{
	set_position(x, y, 0);
	set_velocity(0, 0);
	matVal_ = mat;
	shapeVal_ = shape;

	// Changing the colour and hp of the block based on it's material
	switch(matVal_)
	{
		//Colour(A,B,G,R);

		case GLASS:
			hitpoints_ = 5;
			mass_ = 20;
			set_colour(0xFFFFFFCC);
			break;
		case WOOD:
			hitpoints_ = 10;
			set_colour(0xFF336699);
			break;
		case STONE:
			hitpoints_ = 20;
			set_colour(0xFF808080);
			break;
	}

	switch(shapeVal_)
	{
		case SQUARE:
			set_width(32);
			set_height(32);
			break;
		case RECT:
			set_width(32);
			set_height(64);
			break;
		case TRIANGLE:
			std::cout << "Tri's aren't done yet!" << std::endl;
			break;
	}
}

void Block::Update(abfw::Vector2 acceleration, int pWidth, int pHeight)
{
	set_velocity(velocity().x + acceleration.x, velocity().y + acceleration.y);
	move(pWidth, pHeight);
}


Block::~Block(void)
{
}

Block::Block(void)
{
}