#include "Portal.h"

Portal::Portal(const Vec2& pos)
	:
	pos(pos)
{
	animations.emplace_back(Animation(0, 0, 65, 65, 4, sprite, 0.3f));
	animations.emplace_back(Animation(260, 0, 65, 65, 1, sprite, 0.16f));
	animations.emplace_back(Animation(0, 65, 65, 65, 5, sprite, 0.16f));
	
}

void Portal::Draw(Graphics& gfx) const
{
	float t = 1.2f + FullyOpenDuration + 0.6f; 
		if (Time < t)
		{
			animations[(int)iCurSequence].Draw((Vei2)pos, gfx);
		}
}

void Portal::Update(float dt)
{
	Time += dt;
	if (Time >= 1.2f)
	{
		FullyOpened = true;
		iCurSequence = Sequence::FullyOpen;
	}
	if (Time >= 1.2f + FullyOpenDuration)
	{
		iCurSequence = Sequence::Closing;
	}

	animations[(int)iCurSequence].Update(dt);
}
