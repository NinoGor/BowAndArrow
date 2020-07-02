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
	Balloon(Vec2 pos,float linearMovingDuration);
	void Draw(Graphics& gfx);
	void Update(float dt);
	Vec2 pos;
	Vec2 Center = { pos.x - 18.0f,pos.y };
	bool hasPortal = true;
	Portal portal = Portal(Center);
	bool isPierced = false;
	bool isOutOfScreen = false;
	float linearMovingDuration = 1.2f;
private:
	float linearMovingTime = 0.0f;
	

	float poppingTime = 0.0f;
	float poppingDuration = 0.6f;

	float angle = -1.38f;
	Sequence iCurSequence = Sequence::Floating;
	Surface sprite = "Balloon27x56.bmp";
	float speed = 80.0f;
	std::vector<Animation> animations;
};