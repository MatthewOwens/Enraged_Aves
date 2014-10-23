#include "sprite_application.h"
#include <system/platform.h>
#include <iostream>
#include <iterator>
//#include <algorithm>

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

	blocks.push_back(Block::Block(Block::WOOD, Block::RECT, 50, 200));
	blocks.push_back(Block::Block(Block::GLASS, Block::SQUARE, 60, 20));

	bird.shoot(30, 50);	// TODO: Proper launching
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

	// Firing the bird
	bird.update();

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
			exit(0);
			// return false - don't do this, resets the vita
		}
	}

	// Bouncing the bird
	if(physics_.WallCollision(bird))
		bird.bounceGround(0.5);

	for(int i = 0; i < blocks.size(); ++i)
	{
		// Updating the block
		blocks[i].Update(gravityVector_, platform_.width(), platform_.height());

		// Checking for collision with other blocks
		for(int j = 0; j < blocks.size(); ++j)
		{
			auto check1 = std::find(checkedCollisions_.begin(), checkedCollisions_.end(), abfw::Vector2(i,j));
			auto check2 = std::find(checkedCollisions_.begin(), checkedCollisions_.end(), abfw::Vector2(j,i));

			if(i != j && (check1 == checkedCollisions_.end() && check2 == checkedCollisions_.end()))
			{
				if(physics_.BoundingBox(blocks[i], blocks[j]))
				{
					// Temp, to be replaced with real velocities
					physics_.Stop(blocks[i], blocks[j], gravityVector_);
					physics_.Seperate(blocks[i], blocks[j]);
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

	// rendering the blocks
	for(int i = 0; i < blocks.size(); ++i)
		sprite_renderer_->DrawSprite(blocks[i]);

	// rendering the bird
	sprite_renderer_->DrawSprite(bird);

	// tell sprite renderer that all sprites have been drawn
	sprite_renderer_->End();
}