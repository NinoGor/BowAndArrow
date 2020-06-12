#include "Balloon.h"

Balloon::Balloon(const Vec2& pos)
	:
	pos(pos)
{
	
	animations.emplace_back(Animation(0, 0, 27, 56, 4, sprite, 0.16f));
	
	animations.emplace_back(Animation(0, 56, 27, 56, 6, sprite, 0.16f));
}

void Balloon::DrawAndUpdate(Graphics& gfx, float dt)
{
	portal.Update(dt);
	portal.Draw(gfx);
	
	if (angle == 2.0f * float(PI))
	{
		angle = 0.0f;
	}
	else
	{
		angle = std::min(angle += dt, 2 * float(PI));
	}
	animations[(int)iCurSequence].Draw({ int(pos.x + 80 * cos(angle)), int(pos.y + 80 * sin(angle)) }, gfx);
}


