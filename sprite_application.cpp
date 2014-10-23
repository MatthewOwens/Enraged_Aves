#include "sprite_application.h"
#include <system/platform.h>
#include <iostream>
#include <random>

SpriteApplication::SpriteApplication(abfw::Platform& platform) :
	abfw::Application(platform),
	sprite_renderer_(NULL),
	controller_manager_(NULL)
{
}

SpriteApplication::~SpriteApplication()
{
}

void SpriteApplication::Init()
{
	// create a sprite renderer to draw the sprites
	sprite_renderer_ = platform_.CreateSpriteRenderer();

	// create a controller manager to receive controller input
	controller_manager_ = platform_.CreateSonyControllerInputManager();
	physics_.Init(platform_.width(), platform_.height());

	blocks.push_back(Block::Block(Block::WOOD, Block::RECT, 50, 20));
	blocks.push_back(Block::Block(Block::GLASS, Block::SQUARE, 60, 200));
}

void SpriteApplication::CleanUp()
{
	// free up controller manager
	delete controller_manager_;
	controller_manager_ = NULL;

	// free up the sprite renderer
	delete sprite_renderer_;
	sprite_renderer_ = NULL;
}

bool SpriteApplication::Update(float ticks)
{
	// calculate the frame rate
	frame_rate_ = 1.0f / ticks;

	// getting the screen bounds
	int pWidth = platform_.width();
	int pHeight = platform_.height();

	// Clearing the checked collisions
	checkedCollisions_.clear();

	controller_manager_->Update();

	// get the first controller attached to the hardware platform
	// we only have one on PS Vita
	const abfw::SonyController* controller = controller_manager_->GetController(0);

	// check we have a valid controller object (one that isn't NULL)
	if(controller)
	{
		if ((controller->buttons_down() & (ABFW_SONY_CTRL_START | ABFW_SONY_CTRL_SELECT)) == (ABFW_SONY_CTRL_START | ABFW_SONY_CTRL_SELECT))
		{
			std::cout << "start and select pressed" << std::endl;
		}
	}

	for(int i = 0; i < blocks.size(); ++i)
	{
		// Updating the block
		blocks[i].Update(gravityVector_, platform_.width(), platform_.height());

		// Checking for collision with other blocks
		for(int j = 0; j < blocks.size(); ++j)
		{
			auto check1 = std::find(std::begin(checkedCollisions_),
						std::end(checkedCollisions_), abfw::vector2(i,j));
			auto check2 = std::find(std::begin(checkedCollisions_),
						std::end(checkedCollisions_), abfw::vector2(j,i));
			if(i != j && !(check1 == std::end(checkedCollisions_ || check2 == std::end(checkedCollisions_))))
			{
				if(physics_.BoundingBox(blocks[i], blocks[j]))
				{
					// Temp, to be replaced with real velocities
					physics_.Stop(blocks[0], blocks[1], gravityVector_);
					std::cout << physics_.BoundingBoxSides(blocks[0], blocks[1]) << std::endl;	//TODO, fix this malarky
				}

				// Flagging the current collision as checked
				checkedCollisions_.push_back(abfw::Vector2(i,j));
			}
		}
				
		physics_.WallCollision(blocks[i]);
	}

	// return if the application is still running
	// this should always be true on PS Vita
	return true;
}

void SpriteApplication::Render()
{
	// set up sprite renderer for drawing
	sprite_renderer_->Begin();

	//sprite_renderer_->DrawSprite(block);
	for(int i = 0; i < blocks.size(); ++i)
		sprite_renderer_->DrawSprite(blocks[i]);

	// tell sprite renderer that all sprites have been drawn
	sprite_renderer_->End();
}