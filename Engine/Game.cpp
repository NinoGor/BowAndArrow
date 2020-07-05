/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	xDist1(20, 100),
	xDist2(500, 580),
	x1v2(0,1)
{
	startMusic.Play();
}


void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{	
	float dt = ft.Mark();
	if (gameIsStarted && !gameIsOver)
	{
		if (paused)
		{
			pauseTime += dt;
			if (pauseTime >= pauseDuration)
			{
				pauseTime = 0.0f;
				hearts = 3;
				paused = false;
				gameOverMusic.Play();
				gameIsOver = true;
			}
		}
		if (!paused)
		{
			if (!(archer.isShooting))
			{
				archer.dir = { 0.0f,0.0f };
				if (wnd.kbd.KeyIsPressed('W'))
				{
					archer.dir.y -= 1.0f;
					archer.isMoving = true;
				}
				else if (wnd.kbd.KeyIsPressed('S'))
				{
					archer.dir.y += 1.0f;
					archer.isMoving = true;
				}
				else if (wnd.kbd.KeyIsPressed('A'))
				{
					archer.dir.x -= 1.0f;
					archer.isMoving = true;
				}
				else if (wnd.kbd.KeyIsPressed('D'))
				{
					archer.dir.x += 1.0f;
					archer.isMoving = true;
				}
				else
				{
					archer.isMoving = false;
				}
			}
			if (!archer.isMoving && counter > (numOfBalloons - 1))
			{
				while (!wnd.mouse.IsEmpty())
				{
					const Mouse::Event e = wnd.mouse.Read();
					if (e.GetType() == Mouse::Event::Type::LPress)
					{
						archer.AnimIsReset = false;
						archer.isShooting = true;
						archer.isStretching = true;
						archer.shootingTime = 0.0f;

					}
					else if (e.GetType() == Mouse::Event::Type::LRelease)
					{
						archer.isStretching = false;
						archer.bowIsStretched = false;
						archer.isShooting = false;

					}
				}
			}

			if (counter == 0)
			{
				b1.pos = Vec2(385, 280);
				b1.Center = { 385, 280 };
				b1.linearMovingDuration = 0.0f;
				b1.portal.FullyOpenDuration = balloonSpawnDelay * (numOfBalloons - 1);
				b1.portal.pos = { b1.Center.x - 17.0f,b1.Center.y - 205.0f };
				balloons.push_back(Balloon(b1));
				counter++;
			}
			if (counter > 0 && counter <= numOfBalloons - 1)
			{
				balloonSpawnCounter += dt;
				if (balloonSpawnCounter >= balloonSpawnDelay && balloons.size() < numOfBalloons)
				{
					b1.pos = Vec2(385, 280);
					b1.Center = { 385, 280 };
					b1.linearMovingDuration = 0.0f;
					b1.portal.FullyOpenDuration = 2.0f;
					b1.hasPortal = false;
					b1.portal.pos = { b1.Center.x,b1.Center.y - 205.0f };
					balloons.push_back(Balloon(b1));
					counter++;
					balloonSpawnCounter = 0.0f;
				}
			}
			else
			{
				balloonSpawnCounter += dt;
				if (balloonSpawnCounter >= balloonSpawnDelay && balloons.size() < numOfBalloons)
				{
					b1.pos = Vec2(385, 280);
					b1.Center = { 385, 280 };
					b1.hasPortal = true;
					b1.linearMovingDuration = 0.0f;
					b1.portal.FullyOpenDuration = 0.0f;
					b1.portal.pos = { b1.Center.x - 17.0f, b1.Center.y - 205.0f };
					balloons.push_back(Balloon(b1));

					balloonSpawnCounter = 0.0f;
					balloonSpawnDelay = 3.0f;

				}
			}

			bombSpawnCounter += dt;
			if (bombSpawnCounter >= bombSpawnDelay)
			{
				if (x1v2(rng) == 0)
				{
					bomb1.pos.x = (float)xDist1(rng);
					bombs.push_back(Bomb(bomb1));
				}
				else
				{
					bomb1.pos.x = (float)xDist2(rng);
					bombs.push_back(Bomb(bomb1));
				}
				bombSpawnCounter = 0.0f;
			}

			qBoxSpawnCounter += dt;
			if (qBoxSpawnCounter >= qBoxSpawnDelay)
			{
				if (x1v2(rng) == 0)
				{
					questionBoxes.emplace_back(Vec2{ (float)xDist1(rng) ,650.0f }, rng);
				}
				else
				{
					questionBoxes.emplace_back(Vec2{ (float)xDist2(rng) ,650.0f }, rng);
				}
				qBoxSpawnCounter = 0.0f;
			}


			for (int n = 0; n < balloons.size(); n++)
			{
				if (balloons[n].isOutOfScreen)
				{
					balloons.erase(balloons.begin() + n);
				}
				if (!balloons[n].isPierced)
				{
					const auto balloon_hitbox = balloons[n].GetHitbox();
					for (int i = 0; i < archer.arrows.size(); i++)
					{
						if (archer.arrows[i].GetHitbox().IsOverlappingWith(balloon_hitbox) && balloons[n].portal.FullyOpened)
						{
							soundPop.Play();
							balloons[n].isPierced = true;
							score++;
						}
					}
				}
				balloons[n].Update(dt);
			}
			for (int n = 0; n < bombs.size(); n++)
			{
				if (bombs[n].leftTheScreen)
				{
					bombs.erase(bombs.begin() + n);
				}
			}
			for (auto& bomb : bombs)
			{
				if (!bomb.isHit)
				{
					const auto bomb_hitbox = bomb.GetHitbox();
					for (int i = 0; i < archer.arrows.size(); i++)
					{
						if (archer.arrows[i].GetHitbox().IsOverlappingWith(bomb_hitbox))
						{

							bomb.isHit = true;
							if (!playerHasInvincibility)
								hearts--;
							if (!(hearts <= 0))
							{
								soundExplosion.Play();
								archer.arrows[i].exploded = true;

							}
							else
							{
								if (bomb.isHit)
								{
									paused = true;
									music.StopAll();
									soundPause.Play();
								}
							}
						}
						auto new_end = std::remove_if(archer.arrows.begin(), archer.arrows.end(), [](Archer::Arrow & arrow) {
							return arrow.exploded;
							});
						archer.arrows.erase(new_end, archer.arrows.end());

					}
				}
				bomb.Update(dt);
			}

			for (int n = 0; n < questionBoxes.size(); n++)
			{
				if (questionBoxes[n].leftTheScreen)
				{
					questionBoxes.erase(questionBoxes.begin() + n);
				}
			}

			for (auto& qBox : questionBoxes)
			{
				if (!qBox.isHit)
				{
					const auto qBox_hitbox = qBox.GetHitbox();
					for (auto& arrow : archer.arrows)
					{
						if (arrow.GetHitbox().IsOverlappingWith(qBox_hitbox))
						{
							qBox.isHit = true;
						}
					}
					if (qBox.isHit)
					{
						soundQBox.Play();
						if (!playerHasEffect)
						{
							if (qBox.effect == QuestionBox::Effect::Multishot)
							{
								archer.hasMultishot = true;
								playerHasEffect = true;
							}
							else if (qBox.effect == QuestionBox::Effect::FullHealth && hearts < 3)
							{
								hearts = 3;
								heartsEffect = true;
								playerHasEffect = true;
							}
							else if (qBox.effect == QuestionBox::Effect::Invincibility)
							{
								playerHasInvincibility = true;
								playerHasEffect = true;
							}
							else if (qBox.effect == QuestionBox::Effect::Slowness)
							{
								archer.hasSlowness = true;
								playerHasEffect = true;
							}
							else if (qBox.effect == QuestionBox::Effect::MoreBombs)
							{
								bombSpawnDelay = 3.0f;
								playerHasEffect = true;
							}

						}
					}
				}
				qBox.Update(dt);
			}
			if (playerHasEffect)
			{
				if (EffectDuration <= 0.0f)
				{
					if (archer.hasMultishot)
					{
						archer.hasMultishot = false;
					}
					else if (playerHasInvincibility)
					{
						playerHasInvincibility = false;
					}
					else if (archer.hasSlowness)
					{
						archer.hasSlowness = false;
					}
					else if (bombSpawnDelay == 3.0f)
					{
						bombSpawnDelay = 10.0f;
					}
					else if (heartsEffect)
					{
						heartsEffect = false;
					}
					playerHasEffect = false;
				}
				else
				{
					EffectDuration -= dt;
				}
			}
			else
			{
				EffectDuration = 20.0f;
			}

			archer.SetDirection();
			archer.ClampToRect(RectI{ 335,465, 195, 355 });
			archer.Update(dt, wnd.mouse);
		}
	}
	else if (!gameIsStarted && !gameIsOver)
	{

		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			startMusic.StopAll();
			gameIsStarted = true;
			music.Play(0.85f,0.3f);
		}
	}
	else if (gameIsOver)
	{

		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameOverMusic.StopAll();
			archer.arrows.erase(archer.arrows.begin(), archer.arrows.end());
			balloons.erase(balloons.begin(), balloons.end());
			bombs.erase(bombs.begin(), bombs.end());
			questionBoxes.erase(questionBoxes.begin(), questionBoxes.end());

			counter = 0;
			score = 0;
			archer.pos = { 367.0f,250.0f };
			balloonSpawnCounter = 0.0f;
			balloonSpawnDelay = 0.384f;
			bombSpawnCounter = 0.0f;
			bombSpawnDelay = 10.0f;
			qBoxSpawnCounter = 0.0f;

			archer.hasMultishot = false;
			heartsEffect = false;
			playerHasInvincibility = false;
			archer.hasSlowness = false;

			playerHasEffect = false;
			
			EffectDuration = 20.0f;

			music.Play(0.85f, 0.3f);

			gameIsOver = false;
		}
	}
}

void Game::ComposeFrame()
{
	if (gameIsStarted)
	{
		if (!gameIsOver)
		{
			gfx.DrawSprite(0, 0, bckgrnd, SpriteEffect::Copy{});

			for (auto& bomb : bombs)
			{
				bomb.Draw(gfx);
			}
			for (auto& qBox : questionBoxes)
			{
				qBox.Draw(gfx);
			}
			for (auto& balloon : balloons)
			{
				if (balloon.hasPortal)
					balloon.portal.Draw(gfx);
			}
			archer.Draw(gfx);

			gfx.DrawSprite(306, 550, Bar, SpriteEffect::Chroma{ Colors::Magenta });
			font.DrawText("Score:", Vei2(320, 563), Colors::White, gfx);
			font.DrawText(std::to_string(score), Vei2(370, 563), Colors::White, gfx);

			gfx.DrawSprite(306, 11, Bar, SpriteEffect::Chroma{ Colors::Magenta });
			if (playerHasEffect)
			{
				if (!heartsEffect)
				{
					std::string num_text = std::to_string(EffectDuration);
					std::string roundedED = num_text.substr(0, num_text.find(".") + 3);
					font.DrawText(roundedED, Vei2(440, 24), Colors::White, gfx);
				}
				if(archer.hasMultishot)
					font.DrawText("MULTISHOT", Vei2(320, 24), Colors::Green, gfx);
				else if(playerHasInvincibility)
					font.DrawText("INVINCIBILITY", Vei2(320, 24), Colors::Green, gfx);
				else if (heartsEffect)
					font.DrawText("HEARTS RESTORED", Vei2(345, 24), Colors::Green, gfx);
				else if(archer.hasSlowness)
					font.DrawText("SLOWNESS", Vei2(320, 24), Colors::Red, gfx);
				else if (bombSpawnDelay == 3.0f)
					font.DrawText("MORE BOMBS", Vei2(320, 24), Colors::Red, gfx);

			}
			else
			{
				font.DrawText("NO EFFECTS", Vei2(360, 24), Colors::White, gfx);
			}

			if (hearts == 3)
			{
				gfx.DrawSprite(468, 564, heart, SpriteEffect::Chroma{ Colors::Magenta });
				gfx.DrawSprite(453, 564, heart, SpriteEffect::Chroma{ Colors::Magenta });
				gfx.DrawSprite(438, 564, heart, SpriteEffect::Chroma{ Colors::Magenta });
			}
			if (hearts == 2)
			{
				gfx.DrawSprite(468, 564, heart, SpriteEffect::Chroma{ Colors::Magenta });
				gfx.DrawSprite(453, 564, heart, SpriteEffect::Chroma{ Colors::Magenta });
			}
			if (hearts == 1)
			{
				gfx.DrawSprite(468, 564, heart, SpriteEffect::Chroma{ Colors::Magenta });
			}

			for (auto& balloon : balloons)
			{
				balloon.Draw(gfx);
			}
			gfx.DrawSprite(wnd.mouse.GetPosX() - 14, wnd.mouse.GetPosY() - 14, rtcl, SpriteEffect::Chroma{ Color{255,0,255} });
		}
		else
		{
			gfx.DrawSprite(0, 0, gameOverScreen, SpriteEffect::Copy{});
		}
	}
	else
	{
		gfx.DrawSprite(0, 0, startScreen, SpriteEffect::Copy{});
	}
	

}
