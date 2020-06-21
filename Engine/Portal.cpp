#include "Portal.h"

Portal::Portal(const Vec2& pos, float FullyOpenDuration)
	:
	pos(pos),
	FullyOpenDuration(FullyOpenDuration)
{
	animations.emplace_back(Animation(0, 0, 65, 65, 4, sprite, 0.3f));
	animations.emplace_back(Animation(260, 0, 65, 65, 1, sprite, 0.16f));
	animations.emplace_back(Animation(0, 65, 65, 65, 5, sprite, 0.16f));
	
}

void Portal::Draw(Graphics& gfx) const
{
	float t = FullyOpenDuration + 0.8f;
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
		//at this point the portal is fully open
		FullyOpened = true;
		iCurSequence = Sequence::FullyOpen;
	}
	if (Time >= FullyOpenDuration)
	{
		//at this point the portal needs to close
		iCurSequence = Sequence::Closing;
	}

	animations[(int)iCurSequence].Update(dt);
}
