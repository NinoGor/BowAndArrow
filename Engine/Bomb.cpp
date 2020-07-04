#include "Bomb.h"

Bomb::Bomb(Vec2 pos)
	:
	pos(pos)
{
	animations.emplace_back(Animation(0, 0, 39, 39, 1, sprite, 0.16f));
	animations.emplace_back(Animation(39, 0, 39, 39, 5, sprite, 0.1f));
}

void Bomb::Draw(Graphics& gfx)
{
	if(explosionTime < explosionDuration)
	animations[(int)iCurSequence].Draw(Vei2(pos), gfx);
}

void Bomb::Update(float dt)
{
	pos.x += sinf(angle * 2 * PI) * amplitude;	
	pos.y += speed * dt;
	if (angle == 2.0f * float(PI))
	{
		angle = 0.0f;
	}
	else
	{
		angle = std::min(angle += dt, 4 * float(PI));
	}

	if (isHit)
	{
		if (pos.y < Graphics::ScreenHeight)
		{
			explosionTime += dt;
			if (explosionTime <= explosionDuration)
			{
				animations[(int)iCurSequence].Update(dt);
			}
			iCurSequence = Sequence::Exploding;
		}
	}
	if(pos.y >= Graphics::ScreenHeight)
	{
		leftTheScreen = true;
	}

}

RectF Bomb::GetHitbox() const
{
	return RectF(pos.x +7.0f,pos.x+33.0f,pos.y+10.0f,pos.y+36.0f);
}
