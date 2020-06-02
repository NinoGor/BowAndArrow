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

	        WalkingUpWithBow,
	      WalkingLeftWithBow,
	      WalkingDownWithBow,
		 WalkingRightWithBow,
		   StandingUpWithBow,
		 StandingLeftWithBow,
	   	 StandingDownWithBow,
		StandingRightWithBow,

		Count
	};
public:
	Archer(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void SetDirection(const Vec2& dir);
	void Update(float dt);
private:
	Surface sprite;
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	std::vector<Animation> animations;
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 80.0f;
};