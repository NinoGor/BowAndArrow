#include "Archer.h"

Archer::Archer(const Vec2& pos)
	:
	sprite("Archer.bmp"),
	pos(pos)
{
	for (int i = 0; i < (int)Sequence::StandingUp; i++)
	{
		animations.emplace_back(Animation(64, 64*i, 64, 64, 8, sprite, 0.16f));
	}
	for (int i = (int)Sequence::StandingUp; i < (int)Sequence::ShootingUp; i++)
	{
		animations.emplace_back(Animation(0, 64 * (i- (int)Sequence::StandingUp), 64, 64, 1, sprite, 0.16f));
	}

	for (int i = (int)Sequence::ShootingUp; i < (int)Sequence::Count; i++)
	{
		animations.emplace_back(Animation(0, 64 * i, 64, 64, 9, sprite, 0.16f));
	}
}

void Archer::Draw(Graphics& gfx) const
{
	animations[(int)iCurSequence].Draw((Vei2)pos, gfx);
}

void Archer::SetDirection(const Vec2& dir)
{
		if (dir.x > 0.0f)
		{
			iCurSequence = Sequence::WalkingRight;
		}
		else if (dir.x < 0.0f)
		{
			iCurSequence = Sequence::WalkingLeft;
		}
		else if (dir.y < 0.0f)
		{
			iCurSequence = Sequence::WalkingUp;
		}
		else if (dir.y > 0.0f)
		{
			iCurSequence = Sequence::WalkingDown;
		}
		else
		{
			if (vel.x > 0.0f)
			{
				iCurSequence = Sequence::StandingRight;
			}
			else if (vel.x < 0.0f)
			{
				iCurSequence = Sequence::StandingLeft;
			}
			else if (vel.y < 0.0f)
			{
				iCurSequence = Sequence::StandingUp;
			}
			else if (vel.y > 0.0f)
			{
				iCurSequence = Sequence::StandingDown;
			}
		}
	vel = dir*speed;
}

void Archer::Update(float dt)
{
	pos += vel * dt;
	animations[(int)iCurSequence].Update(dt);
}
