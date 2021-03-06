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
	float FullyOpenDuration = 0.0f; 
	float Time = 0.0f;
	Sequence iCurSequence = Sequence::Opening;
	bool FullyOpened = false;
	Vec2 pos;
private:
	std::vector<Animation> animations;
	Surface sprite = "Images\\portal65x65.bmp";

};