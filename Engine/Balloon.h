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
	Balloon();
	void DrawAndUpdate(Graphics& gfx, float dt);
	Vec2 pos = { 520.0f,270.0f };
private:
	float linearMovingTime = 0.0f;
	float linearMovingDuration = 2.5f;
	Portal portal = Portal({ 500.0f,260.0f });
	float angle = -1.55f;
	Sequence iCurSequence = Sequence::Floating;
	Surface sprite = "Balloon27x56.bmp";
	
	//Vec2 vel = { 0.0f,0.0f };
	float speed = 80.0f;
	std::vector<Animation> animations;
};