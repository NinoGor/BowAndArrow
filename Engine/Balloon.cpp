#include "Balloon.h"


Balloon::Balloon(Vec2 pos, float linearMovingDuration)
	:
	pos(pos),
	linearMovingDuration(linearMovingDuration)
{
	animations.emplace_back(Animation(0, 0, 27, 56, 4, sprite, 0.16f));
	animations.emplace_back(Animation(0, 56, 27, 56, 6, sprite, 0.1f));
}

void Balloon::Draw(Graphics& gfx)
{
	if (portal.FullyOpened)
	{
		animations[(int)iCurSequence].Draw(Vei2(pos), gfx);
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
			else if (linearMovingTime >= linearMovingDuration && !isPierced)
			{
				animations[(int)iCurSequence].Update(dt);
				pos = { float(Center.x + 200 * cos(angle)), float(Center.y + 200 * sin(angle))};
				if (angle == 2.0f * float(PI))
				{
					angle = 0.0f;
				}
				else
				{
					angle = std::min(angle += dt, 2 * float(PI));
				}
			
	}
		if (isPierced)
		{
			if (pos.y < Graphics::ScreenHeight)
			{
				poppingTime += dt;
				if (poppingTime < poppingDuration)
				{
					animations[(int)iCurSequence].Update(dt);
				}
				iCurSequence = Sequence::Popping;
				pos.y += speed * dt;
			}
			else
			{
				isOutOfScreen = true;
			}
		}
	}
	
	
}

RectF Balloon::GetHitbox() const
{
	//return RectF(pos.x, pos.x + 27.0f, pos.y, pos.y + 35.0f);
	return RectF(pos.x+5.0f, pos.x + 22.0f, pos.y+5.0f, pos.y + 25.0f);
}




