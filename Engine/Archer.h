#pragma once

#include "Animation.h"
#include "Vec2.h"

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
public:
	Archer(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2& dir);
	void Update(float dt);
	bool isShooting = false;
private:
	Surface sprite;
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	std::vector<Animation> animations;
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 80.0f;
};