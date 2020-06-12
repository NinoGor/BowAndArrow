#pragma once

#include "Animation.h"
#include "Vec2.h"

class Portal
{
private:
	enum class Sequence
	{
		Opening,
		FullyOpen,
		Closing,

		Count
	};
public:
	Portal(const Vec2& pos);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	float FullyOpenDuration = 10.0f;
	float Time = 0.0f;
	Sequence iCurSequence = Sequence::Opening;
	bool isOnScreen = true;
private:
	std::vector<Animation> animations;
	Surface sprite = "portal65x65.bmp";
	Vec2 pos;
};