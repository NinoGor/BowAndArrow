#pragma once

#include "Animation.h"
#include "Vec2.h"
#include "Balloon.h"
#include "SpriteEffect.h"
#include "Mouse.h"
#include <math.h> 

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

		StretchingUp,
		StretchingLeft,
		StretchingDown,
		StretchingRight,

		StretchedUp,
		StretchedLeft,
		StretchedDown,
		StretchedRight,

		Count
	};
public:
	class Arrow
	{
	public:
		Arrow() = default;
		void Draw(Graphics& gfx) const;
		Surface Sprite = "Arrow.bmp";
		Vec2 pos = {0.0f,0.0f};
		Vec2 vel = {0.0f,0.0f};
		float speed = 350.0f;
		Vec2 dir = { 0.0f,1.0f };
		Color chroma = Colors::Magenta;
	};
public:
	Archer(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void SetDirection();
	void Update(float dt, const Mouse& mouse);
	void ClampToRect(const RectI& rect);
	Vec2 GetArcherCentre();
	void Shooting(float dt, const Mouse& mouse);
	bool ArrowIsFlying = false;
	bool bowIsStretched = false;
	bool isShooting = false;
	bool isStretching = false;

	float fullStretchTime = 0.7f;

	float shootingTime = 0.0f;
	bool isMoving = false;
	Vec2 dir = { 0.0f,0.0f };
	Vec2 AimDir = { 0.0f,1.0f };
	std::vector<Arrow> arrows;
	bool AnimIsReset = false;

private:
	Surface sprite;
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	std::vector<Animation> animations;
	Arrow arr1;
	Sequence iCurSequence = Sequence::StandingDown;
	float speed = 80.0f;
};