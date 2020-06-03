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
		animations.emplace_back(Animation(0, 64 * (i-4), 64, 64, 13, sprite, 0.20f));
	}
}

void Archer::Draw(Graphics& gfx) const
{

	if (isShooting)
	{
		animations[(int)shooting].Draw((Vei2)pos, gfx);
	}
	else
	{
		animations[(int)iCurSequence].Draw((Vei2)pos, gfx);
	}
}

void Archer::SetDirection()
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
				shooting = Sequence::ShootingRight;
			}
			else if (vel.x < 0.0f)
			{
				iCurSequence = Sequence::StandingLeft;
				shooting = Sequence::ShootingLeft;
			}
			else if (vel.y < 0.0f)
			{
				iCurSequence = Sequence::StandingUp;
				shooting = Sequence::ShootingUp;
			}
			else if (vel.y > 0.0f)
			{
				iCurSequence = Sequence::StandingDown;
				shooting = Sequence::ShootingDown;
			}
		}
		
	vel = dir*speed;
}



void Archer::Update(float dt)
{
	pos += vel * dt;
	

	if (isShooting)
	{
			animations[(int)shooting].Update(dt);
	}
	else
	{
		animations[(int)iCurSequence].Update(dt);
	}
	
}
