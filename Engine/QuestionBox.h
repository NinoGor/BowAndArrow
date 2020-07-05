#pragma once

#include "Animation.h"
#include "Vec2.h"
#include <random>
#include <algorithm>
#define PI acos(-1.0)

class QuestionBox
{
private:
	enum class Sequence
	{
		Normal,
		Deactivated,
		Count
	};
public:
	enum class Effect
	{
		Multishot,
		FullHealth,
		Invincibility,
		Slowness,
		MoreBombs
	};
public:
	QuestionBox(Vec2 pos, std::mt19937& rng);
	void Draw(Graphics& gfx);
	void Update(float dt);
	RectF GetHitbox() const;
	
	//std::mt19937& rng;
	std::uniform_int_distribution<int> type;

	Effect effect;
	Vec2 pos;
	bool isHit = false;
	bool leftTheScreen = false;
private:
	float angle = 0.0f;

	Sequence iCurSequence = Sequence::Normal;
	Surface sprite = "Images\\QuestionBox70x35.bmp";
	float amplitude = 5.0f;
	float speed = 80.0f;
	std::vector<Animation> animations;
};