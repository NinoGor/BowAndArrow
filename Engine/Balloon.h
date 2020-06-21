#pragma once
#include "Animation.h"
#include "Vec2.h"
#include "math.h"
#include <algorithm>
#include "Portal.h"
#define PI acos(-1.0)

class Balloon
{
private:
	enum class Sequence
	{
		Floating,
		Popping,
		Count
	};

public:
	Balloon(Vec2 pos);
	void Draw(Graphics& gfx);
	void Update(float dt);
	Vec2 pos;
	Vec2 Center = { pos.x - 18.0f,pos.y };
	Portal portal = Portal(Center, 2.0f);
	bool isPierced = false;
	bool isOutOfScreen = false;
private:
	float linearMovingTime = 0.0f;
	float linearMovingDuration = 1.2f;

	float poppingTime = 0.0f;
	float poppingDuration = 0.6f;

	float angle = -1.38f;
	Sequence iCurSequence = Sequence::Floating;
	Surface sprite = "Balloon27x56.bmp";
	float speed = 80.0f;
	std::vector<Animation> animations;
};