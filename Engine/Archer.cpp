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
	for (int i = (int)Sequence::StandingUp; i < (int)Sequence::StretchingUp; i++)
	{
		animations.emplace_back(Animation(0, 64 * (i- (int)Sequence::StandingUp), 64, 64, 1, sprite, 0.16f));
	}
	for (int i = (int)Sequence::StretchingUp; i < (int)Sequence::StretchedUp; i++)
	{
		animations.emplace_back(Animation(0, 64 * (i - 4), 64, 64, 8, sprite, 0.10f));
	}
	for (int i = (int)Sequence::StretchedUp; i < (int)Sequence::Count; i++)
	{
		animations.emplace_back(Animation(8*64, 64 * (i - 8), 64, 64, 1, sprite, 0.10f));
	}
	
}


void Archer::Draw(Graphics& gfx) const
{
	
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].Draw(gfx);
	}
	if (isShooting && !isMoving)
	{
		if (isStretching && !bowIsStretched)
		{
			int i = int(iCurSequence);
			i += 4;
			animations[i].Draw((Vei2)pos, gfx);
		}
		else if (bowIsStretched)
		{
			int i = int(iCurSequence);
			i += 8;
			animations[i].Draw((Vei2)pos, gfx);
		}
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



void Archer::Update(float dt, const Mouse& mouse)
{
	pos += vel * dt;

	

	if (isShooting && !isMoving)
	{
		
		shootingTime += dt;
		if (shootingTime >= fullStretchTime)
		{
			bowIsStretched = true;
			ArrowIsFlying = true;
		}
		if (isStretching && !bowIsStretched)
		{
			int i = int(iCurSequence);
			i += 4;
			if (!AnimIsReset)
			{
				animations[i].Reset();
				AnimIsReset = true;
			}
			animations[i].Update(dt);
		}
		else if (bowIsStretched)
		{
			int i = int(iCurSequence);
			i += 8;
			animations[i].Update(dt);
		}
	}

	animations[(int)iCurSequence].Update(dt);
	
	Shooting(dt, mouse);

}

void Archer::ClampToRect(const RectI & rect)
{
	if (pos.x+20.0f < (float)rect.left)
	{
		pos.x = -20.0f + (float)rect.left;
	}
	else if (pos.x+64.0f - 20.0f >= (float)rect.right)
	{
		pos.x = float(rect.right) - 64.0f + 20.0f;
	}

	if (pos.y+10.0f < (float)rect.top)
	{
		pos.y = -10.0f + (float)rect.top;
	}
	else if (pos.y+64.0f >= (float)rect.bottom)
	{
		pos.y = float(rect.bottom) - 64.0f;
	}
}

Vec2 Archer::GetArcherCentre()
{
	return Vec2(pos.x +30.0f ,pos.y + 40.0f);
}

void Archer::Shooting(float dt, const Mouse& mouse)
{
	if (mouse.LeftIsPressed())
	{
		Vec2 mousePos = Vec2((float)mouse.GetPosX(), (float)mouse.GetPosY());
		AimDir = (mousePos - GetArcherCentre()).GetNormilized();
		if (!isMoving && bowIsStretched)
		{
			if (fabsf(AimDir.x) >= fabsf(AimDir.y))
			{
				if (AimDir.x > 0.0f)
				{
					iCurSequence = Sequence::StandingRight;
				}
				else
				{
					iCurSequence = Sequence::StandingLeft;
				}
			}
			else
			{
				if (AimDir.y > 0.0f)
				{
					iCurSequence = Sequence::StandingDown;
				}
				else
				{
					iCurSequence = Sequence::StandingUp;
				}
			}
		}
	}
	if (ArrowIsFlying)
	{
		if (!isShooting && !isMoving)
		{
			arr1.pos = Vec2(float(pos.x + 20), float(pos.y + 20));
			arr1.dir = AimDir;
			arr1.vel = arr1.dir*arr1.speed;
			arrows.emplace_back(arr1);
			soundFire.Play();
			if (true)
			{
				arr1.pos = Vec2(float(pos.x + 20), float(pos.y + 20));
				float angle1 = atan2f(AimDir.y, AimDir.x) + 0.2f;
				arr1.dir = Vec2(cosf(angle1), sinf(angle1));
				arr1.vel = arr1.dir * arr1.speed;
				arrows.emplace_back(arr1);

				arr1.pos = Vec2(float(pos.x + 20), float(pos.y + 20));
				float angle2 = atan2f(AimDir.y, AimDir.x) - 0.2f;
				arr1.dir = Vec2(cosf(angle2), sinf(angle2));
				arr1.vel = arr1.dir * arr1.speed;
				arrows.emplace_back(arr1);
			}
			ArrowIsFlying = false;
		}
		
	}
	for (int i = 0; i < arrows.size(); i++)
	{
		arrows[i].pos += arrows[i].vel*dt;
		if (int(arrows[i].pos.x) < 0 || int(arrows[i].pos.x) > Graphics::ScreenWidth
			|| int(arrows[i].pos.y) < 0 || int(arrows[i].pos.y) > Graphics::ScreenHeight)
		{
			arrows.erase(arrows.begin() + i);
		}

	}
}

void Archer::Arrow::Draw(Graphics & gfx) const 
{
	gfx.DrawSpriteRotated((int)pos.x, (int)pos.y, Sprite, atan2f(dir.y, dir.x), SpriteEffect::Chroma{chroma});
}





