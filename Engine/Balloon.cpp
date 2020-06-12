#include "Balloon.h"

Balloon::Balloon()
{
	animations.emplace_back(Animation(0, 0, 27, 56, 4, sprite, 0.16f));
	animations.emplace_back(Animation(0, 56, 27, 56, 6, sprite, 0.1f));
}

void Balloon::Draw(Graphics& gfx)
{
	portal.Draw(gfx);

	if (portal.FullyOpened)
	{
		if (linearMovingTime < linearMovingDuration)
		{
			animations[(int)iCurSequence].Draw((Vei2)pos, gfx);

		}
		else
		{
			animations[(int)iCurSequence].Draw(Vei2(pos), gfx);
		}
	}
}

void Balloon::Update(float dt)
{
	portal.Update(dt);

	if (portal.FullyOpened)
	{
		
		if (linearMovingTime < linearMovingDuration && !isPierced)
		{
			linearMovingTime += dt;
			pos.y -= speed * dt;
		}
		else if(linearMovingTime >= linearMovingDuration && !isPierced)
		{
			animations[(int)iCurSequence].Update(dt);
			pos = { float(screenCenter.x + 200 * cos(angle)), float(screenCenter.y + 200 * sin(angle)) };
			if (angle == 2.0f * float(PI))
			{
				angle = 0.0f;
			}
			else
			{
				angle = std::min(angle += dt, 2 * float(PI));
			}
		}
		else if (isPierced)
		{
			if (pos.y < Graphics::ScreenHeight)
			{
				poppingTime += dt;
				if (poppingTime < poppingDuration)
				{
					animations[(int)iCurSequence].Update(dt);
				}
				iCurSequence = Sequence::Popping;
				pos.y += 2 * speed * dt;
			}
		}
	}
	
	
}




