#pragma once

#include "Animation.h"
#include "Vec2.h"
#include "Keyboard.h"

class Archer
{
private:
	enum class Sequence
	{
		WalkingUp,
		WalkingLeft,
		WalkingDown,
		WalkingRight,
		StandingUp,
		StandingLeft,
		StandingDown,
		StandingRight,

	    ShootingUp,
		ShootingLeft,
		ShootingDown,
		ShootingRight,

		Count
	};
	class Arrow
	{
	public:
		Arrow() = default;
		void Draw(Graphics& gfx) const;
		Surface ArrowSprite = "ArrowH.bmp";
		Surface ArrowSprite2 = "ArrowV.bmp";
		Vec2 pos;
		Vec2 vel = {0.0f,0.0f};
		float speed = 350.0f;
		Vec2 dir = { 0.0f,1.0f };
	};
public:
	Archer(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void SetDirection();
	void Update(float dt);
	void ClampToRect(const RectI& rect);

	void Shooting(float dt);
	bool arrowIsBeingShot = false;
	bool isShooting = false;
	Vec2 dir = { 0.0f,0.0f };
private:
	Surface sprite;
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	std::vector<Animation> animations;
	Arrow arr1;  
	std::vector<Arrow> arrows;
	Sequence iCurSequence = Sequence::StandingDown;
	Sequence shooting = Sequence::ShootingDown;
	float speed = 80.0f;
};