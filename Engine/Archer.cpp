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
		animations.emplace_back(Animation(0, 64 * (i-4), 64, 65, 11, sprite, 0.20f));
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
				arr1.dir = { 1.0f,0.0f };
			}
			else if (vel.x < 0.0f)
			{
				iCurSequence = Sequence::StandingLeft;
				shooting = Sequence::ShootingLeft;
				arr1.dir = { -1.0f,0.0f };
			}
			else if (vel.y < 0.0f)
			{
				iCurSequence = Sequence::StandingUp;
				shooting = Sequence::ShootingUp;
				arr1.dir = { 0.0f, -1.0f };
			}
			else if (vel.y > 0.0f)
			{
				iCurSequence = Sequence::StandingDown;
				shooting = Sequence::ShootingDown;
				arr1.dir = { 0.0f,1.0f };
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

void Archer::Shooting(Graphics& gfx, float dt)
{
	if (arrowIsBeingShot)
	{
		if (!isShooting)
		{
			arr1.pos = Vec2(float(pos.x + 32), float(pos.y + 29));
			arr1.vel = arr1.dir*arr1.speed;
			arrows.emplace_back(Arrow(arr1));
			arrowIsBeingShot = false;
		}
	}
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].pos += arrows[i].vel*dt;
		arrows[i].Draw(gfx);
		if (int(arrows[i].pos.x) < 0 || int(arrows[i].pos.x) > gfx.ScreenWidth
			|| int(arrows[i].pos.y) < 0 || int(arrows[i].pos.y) > gfx.ScreenHeight)
		{
			arrows.erase(arrows.begin() + i);
		}

	}
}


void Archer::Arrow::Draw(Graphics & gfx) const
{
	gfx.DrawSprite((int)pos.x, (int)pos.y, ArrowSprite);
}


