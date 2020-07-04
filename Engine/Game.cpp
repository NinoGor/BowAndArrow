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
	music.Play(1.0f, 1.0f);
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

	
	float dtb = b.Mark();
	float dt = ft.Mark();

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
			b1.portal.FullyOpenDuration = balloonSpawnDelay * (numOfBalloons-1);
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
	}
	for (int n = 0; n < bombs.size(); n++)
	{
		if (bombs[n].leftTheScreen)
		{
			bombs.erase(bombs.begin() + n);
		}
		if (!bombs[n].isHit)
		{
			const auto bomb_hitbox = bombs[n].GetHitbox();
			for (auto& arrow : archer.arrows)
			{
				if (arrow.GetHitbox().IsOverlappingWith(bomb_hitbox))
				{
					soundExplosion.Play();
					bombs[n].isHit = true;
				}
			}
		}
	}

	archer.SetDirection();
	archer.ClampToRect(RectI{335,465, 195, 355});
	archer.Update(dt, wnd.mouse);

	for (int i = 0; i < bombs.size(); i++)
	{
		if (bombs[i].leftTheScreen) 
		{
			bombs.erase(bombs.begin() + i);
		}
   		bombs[i].Update(dt);
	}
	for (int i = 0; i< balloons.size(); i++)
	{
		balloons[i].Update(dt);
	}
	
}

void Game::ComposeFrame()
{
	gfx.DrawSprite(0, 0, bckgrnd, SpriteEffect::Copy{});
	gfx.DrawSprite(306, 550, scoreBar, SpriteEffect::Chroma{Colors::Magenta});
	font.DrawText("Score:",Vei2(320,563),Colors::White,gfx);
	font.DrawText(std::to_string(score), Vei2(370, 563), Colors::White, gfx);

	
	for (auto& bomb:bombs)
	{
		bomb.Draw(gfx);
	} 
	for (auto& balloon:balloons)
	{
		if(balloon.hasPortal)
		balloon.portal.Draw(gfx);
	}
	archer.Draw(gfx);
	for (auto& balloon : balloons)
	{
		balloon.Draw(gfx);
	}

	
	gfx.DrawSprite(wnd.mouse.GetPosX() - 14, wnd.mouse.GetPosY() - 14, rtcl, SpriteEffect::Chroma{ Color{255,0,255} });

	

}
