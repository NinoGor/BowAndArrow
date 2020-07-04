#pragma once

#include "Animation.h"
#include "Vec2.h"
#include <algorithm>
#define PI acos(-1.0)

class Bomb
{
private:
	enum class Sequence
	{
		Normal,
		Exploding,
		Count
	};
public:
	Bomb(Vec2 pos);
	void Draw(Graphics& gfx);
	void Update(float dt);
	RectF GetHitbox() const;
	Vec2 pos;
	bool isHit = false;
	bool leftTheScreen = false;
private:
	float angle = 0.0f;
	float explosionTime = 0.0f;
	float explosionDuration = 0.5f;

	Sequence iCurSequence = Sequence::Normal;
	Surface sprite = "Images\\bomb40x40.bmp";
	float amplitude = 5.0f;
	float speed = 80.0f;
	std::vector<Animation> animations;
};