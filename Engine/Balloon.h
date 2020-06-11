#pragma once
#include "Animation.h"
#include "Vec2.h"
#include "math.h"
#include <algorithm>
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
	Balloon(const Vec2& pos);
	void DrawAndUpdate(Graphics& gfx, float dt);
	Vec2 pos;
private:
	float angle = 0.0f;
	Sequence iCurSequence = Sequence::Floating;
	Surface sprite = "Balloon27x56.bmp";
	
	//Vec2 vel = { 0.0f,0.0f };
	float speed = 80.0f;
	std::vector<Animation> animations;
};