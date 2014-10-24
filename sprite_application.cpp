#include "sprite_application.h"
#include <system/platform.h>
#include <iostream>
#include <random>

SpriteApplication::SpriteApplication(abfw::Platform& platform) :
	abfw::Application(platform),
	sprite_renderer_(NULL),
	controller_manager_(NULL),
	touch_manager_(NULL)
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
	touch_manager_ = platform_.CreateTouchInputManager();
	touch_manager_->EnablePanel(0);
	physics_.Init(platform_.width(), platform_.height());

<<<<<<< HEAD
	blocks.push_back(Block::Block(Block::WOOD, Block::RECT, 900, 200));
	blocks.push_back(Block::Block(Block::GLASS, Block::SQUARE, 880, 150));
	blocks.push_back(Block::Block(Block::STONE, Block::RECT, 840, 200));
=======
	blocks.push_back(Block::Block(Block::WOOD, Block::RECT, 50, 20));
	blocks.push_back(Block::Block(Block::GLASS, Block::SQUARE, 60, 200));
>>>>>>> 5535a8eddcf9b9445aa49765debfc21192bf362e
}

void SpriteApplication::CleanUp()
{
	// free up controller manager
	delete controller_manager_;
	controller_manager_ = NULL;

	// free up the sprite renderer
	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	// free up the touch manager
	delete touch_manager_;
	touch_manager_ = NULL;
}

bool SpriteApplication::Update(float ticks)
{
	// calculate the frame rate
	frame_rate_ = 1.0f / ticks;

	// getting the screen bounds
	int pWidth = platform_.width();
	int pHeight = platform_.height();

<<<<<<< HEAD
	bird.update();

=======
>>>>>>> 5535a8eddcf9b9445aa49765debfc21192bf362e
	// Clearing the checked collisions
	checkedCollisions_.clear();

	controller_manager_->Update();
	touch_manager_->Update();

	// get the first controller attached to the hardware platform
	// we only have one on PS Vita
	const abfw::SonyController* controller = controller_manager_->GetController(0);
	const abfw::Touch* touch_screen = &touch_manager_->GetTouch(0, 0);

	// check we have a valid controller object (one that isn't NULL)
	if(controller)
	{
		if ((controller->buttons_down() & (ABFW_SONY_CTRL_START | ABFW_SONY_CTRL_SELECT)) == (ABFW_SONY_CTRL_START | ABFW_SONY_CTRL_SELECT))
		{
			std::cout << "start and select pressed" << std::endl;
			exit(0);
			// return false - don't do this, resets the vita
		}

		if(controller->buttons_down() & (ABFW_SONY_CTRL_TRIANGLE))
		{
			bird.reset(50.0f, 300.0f);
		}
	}
	
	if (touch_screen)
	{
		if(touch_screen->type == abfw::TT_NEW && !bird.flight())
		{
			if(touch_screen->position.x < platform_.width() / 2)
				bird.reset(touch_screen->position.x, touch_screen->position.y);
		}
		if(touch_screen->type == abfw::TT_RELEASED)
		{
			if(touch_screen->position.x < platform_.width() / 2 && !bird.flight())
				bird.shoot(bird.position().x - touch_screen->position.x,
					touch_screen->position.y - bird.position().y);
		}
	}

	for(int i = 0; i < blocks.size(); ++i)
	{
		// Updating the block
		blocks[i].Update(gravityVector_, platform_.width(), platform_.height());
		physics_.WallCollision(blocks[i]);

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
<<<<<<< HEAD
					physics_.Stop(blocks[i], blocks[j], gravityVector_);
					physics_.Seperate(blocks[i], blocks[j]);
=======
					physics_.Stop(blocks[0], blocks[1], gravityVector_);
					std::cout << physics_.BoundingBoxSides(blocks[0], blocks[1]) << std::endl;	//TODO, fix this malarky
>>>>>>> 5535a8eddcf9b9445aa49765debfc21192bf362e
				}

				// Flagging the current collision as checked
				checkedCollisions_.push_back(abfw::Vector2(i,j));
			}

			// Checking for collision with the bird
			if(physics_.BoundingBox(bird, blocks[i]))
			{
				int collisionResult = physics_.BoundingBoxSides(bird, blocks[i]);
				blocks[i].TakeDamage(bird.velocity());

				if(collisionResult == 1 || collisionResult == 2)
					bird.bounceX(blocks[i].bouncyness());
				else if (collisionResult == 3 || collisionResult == 4)
					bird.bounceX(blocks[i].bouncyness());

				physics_.Seperate(blocks[i], bird);
			}
		}

		// Cleaning up the blocks vector
		std::vector<Block> newBlocks;

		std::vector<Block>::iterator blockItr;
		for(blockItr = blocks.begin(); blockItr != blocks.end(); ++blockItr)
		{
			if(blockItr->hitpoints() > 0)
			{
				newBlocks.push_back(*blockItr);
			}
		}
		blocks = newBlocks;
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

<<<<<<< HEAD
	// rendering the bird
	bird.render(sprite_renderer_);

=======
>>>>>>> 5535a8eddcf9b9445aa49765debfc21192bf362e
	// tell sprite renderer that all sprites have been drawn
	sprite_renderer_->End();
}