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
				arr1.dir = { 1.0f,0.0f };
			}
			else if (vel.x < 0.0f)
			{
				iCurSequence = Sequence::StandingLeft;
				arr1.dir = { -1.0f,0.0f };
			}
			else if (vel.y < 0.0f)
			{
				iCurSequence = Sequence::StandingUp;
				arr1.dir = { 0.0f, -1.0f };
			}
			else if (vel.y > 0.0f)
			{
				iCurSequence = Sequence::StandingDown;
				arr1.dir = { 0.0f,1.0f };
			}
		}
		
	vel = dir*speed;
}



void Archer::Update(float dt)
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
	
	Shooting(dt);

}

void Archer::ClampToRect(const RectI & rect)
{
	if (pos.x+20.0f < (float)rect.left)
	{
		pos.x = -20.0f;
	}
	else if (pos.x+64.0f - 20.0f >= (float)rect.right)
	{
		pos.x = float(rect.right) - 64.0f + 20.0f;
	}

	if (pos.y+10.0f < (float)rect.top)
	{
		pos.y= -10.0f;
	}
	else if (pos.y+64.0f >= (float)rect.bottom)
	{
		pos.y = float(rect.bottom) - 64.0f;
	}
}

void Archer::Shooting(float dt)
{
	if (ArrowIsFlying)
	{
		if (!isShooting && !isMoving)
		{
			arr1.pos = Vec2(float(pos.x + 20), float(pos.y + 29));
			arr1.vel = arr1.dir*arr1.speed;
			arrows.emplace_back(arr1);
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
	if (dir.x > 0.0f)
	{
		gfx.DrawSprite((int)pos.x, (int)pos.y, RectI{ 0,34,0,9 }, ArrowSprite, SpriteEffect::Chroma{chroma});
	}
	else if (dir.x < 0.0f)
	{
		gfx.DrawSprite((int)pos.x, (int)pos.y, RectI{ 34,68,0,9 }, ArrowSprite, SpriteEffect::Chroma{chroma});
	}
	else if (dir.y > 0.0f)
	{
		gfx.DrawSprite((int)pos.x, (int)pos.y, RectI{ 0,9,0,34 }, ArrowSprite2, SpriteEffect::Chroma{chroma});
	}
	else if (dir.y < 0.0f)
	{
		gfx.DrawSprite((int)pos.x, (int)pos.y, RectI{ 0,9,34,68 }, ArrowSprite2, SpriteEffect::Chroma{chroma});
	}
	
}


