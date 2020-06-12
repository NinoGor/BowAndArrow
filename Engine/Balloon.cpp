#include "Balloon.h"

Balloon::Balloon()
{
	
	animations.emplace_back(Animation(0, 0, 27, 56, 4, sprite, 0.16f));
	
	animations.emplace_back(Animation(0, 56, 27, 56, 6, sprite, 0.16f));
}

void Balloon::DrawAndUpdate(Graphics& gfx, float dt)
{
	portal.Update(dt);
	portal.Draw(gfx);
	
	
		//if (angle == 2.0f * float(PI))
		//{
		//	angle = 0.0f;
		//}
		//else
		//{
		//	angle = std::min(angle += dt, 2 * float(PI));
		//}
		//animations[(int)iCurSequence].Draw({ int(pos.x + 200 * cos(angle)), int(pos.y + 200 * sin(angle)) }, gfx);
	
	
		if (portal.FullyOpened)
		{
			linearMovingTime += dt;
			if (linearMovingTime < linearMovingDuration)
			{
			pos.y -= speed * dt;
			animations[(int)iCurSequence].Draw({ int(pos.x), int(pos.y) }, gfx);
			
			}
			else
			{
			    pos = { 520.0f,270.0f };
				if (angle == 2.0f * float(PI))
				{
					angle = 0.0f;
				}
				else
				{
					angle = std::min(angle += dt, 2 * float(PI));
				}
				animations[(int)iCurSequence].Draw({ int(pos.x + 200 * cos(angle)), int(pos.y + 200 * sin(angle)) }, gfx);
			}
		}
	
}


