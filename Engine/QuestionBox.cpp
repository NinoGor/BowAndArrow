#include "QuestionBox.h"

QuestionBox::QuestionBox(Vec2 pos, std::mt19937& rng)
	:
	type(0,4),
	pos(pos)
{
	animations.emplace_back(Animation(0, 0, 34, 34, 1, sprite, 0.16f));
	animations.emplace_back(Animation(34, 0, 34, 34, 1, sprite, 0.1f));

	int Type = type(rng);
	if (Type == 0)
	{
		effect = Effect::Multishot;
	}
	if (Type == 1)
	{
		effect = Effect::FullHealth;
	}
	if (Type == 2)
	{
		effect = Effect::Invincibility;
	}
	if (Type == 3)
	{
		effect = Effect::Slowness;
	}
	if (Type == 4)
	{
		effect = Effect::MoreBombs;
	}
}

void QuestionBox::Draw(Graphics& gfx)
{
	animations[(int)iCurSequence].Draw(Vei2(pos), gfx);
}

void QuestionBox::Update(float dt)
{
	if (!isHit)
	{
		pos.x += sinf(angle * 2 * PI) * amplitude;
		pos.y -= speed * dt;
		if (angle == 2.0f * float(PI))
		{
			angle = 0.0f;
		}
		else
		{
			angle = std::min(angle += dt, 4 * float(PI));
		}
	}
	else 
	{
		if (!leftTheScreen)
		{
			pos.y += 2 * speed * dt;
			iCurSequence = Sequence::Deactivated;
		}
		if (pos.y >= Graphics::ScreenHeight + 60.0f)
			leftTheScreen = true;
	}
	if (pos.y + 35.0f <= 0.0f)
	{
		leftTheScreen = true;
	}
}

RectF QuestionBox::GetHitbox() const
{
	return RectF(pos.x,pos.x+35.0f,pos.y,pos.y+35.0f);
}
