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
	void Draw(Graphics& gfx);
	void Update(float dt);
	Vec2 pos = { 520.0f,270.0f };
	Vec2 screenCenter = { 520.0f,270.0f };
	bool isPierced = false;
private:
	float linearMovingTime = 0.0f;
	float linearMovingDuration = 2.5f;

	float poppingTime = 0.0f;
	float poppingDuration = 0.6f;
	
	Portal portal = Portal({ 500.0f,260.0f });
	float angle = -1.55f;
	Sequence iCurSequence = Sequence::Floating;
	Surface sprite = "Balloon27x56.bmp";
	float speed = 80.0f;
	std::vector<Animation> animations;
};