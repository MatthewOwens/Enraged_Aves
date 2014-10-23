#ifndef _SPRITE_APPLICATION_H
#define _SPRITE_APPLICATION_H

#include <system/application.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <input/sony_controller_input_manager.h>
#include <vector>
#include "Block.h"
#include "PhysEngine2D.h"

namespace abfw
{
	class Platform;
}

class SpriteApplication : public abfw::Application
{
public:
	SpriteApplication(abfw::Platform& platform);
	~SpriteApplication();
	void Init();
	void CleanUp();
	bool Update(float ticks);
	void Render();

private:
	abfw::SonyControllerInputManager* controller_manager_;
	std::vector<Block> blocks;
	std::vector<abfw::Vector2> checkedCollisions_;
	PhysEngine2D physics_;
	abfw::Font font_;
	abfw::SpriteRenderer* sprite_renderer_;
	float frame_rate_;
	const float gravity_ = 9.8f;
	const abfw::Vector2 gravityVector_ = abfw::Vector2(0, 0.2);
};

#endif // _SPRITE_APPLICATION_H