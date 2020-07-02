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
	xDist(400, 700),
	yDist(100, 500)
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
	

	for (int n = 0; n < balloons.size(); n++)
	{
		if (balloons[n].isOutOfScreen)
		{
			balloons.erase(balloons.begin() + n);
		}
		for (int i = 0; i < archer.arrows.size(); i++)
		{
			if (isColliding(archer.arrows[i], balloons[n]) && balloons[n].portal.FullyOpened)
			{
				soundPop.Play();
				balloons[n].isPierced = true;
			}
		}
	}


	archer.SetDirection();
	archer.ClampToRect(RectI{335,465, 195, 355});
	archer.Update(dt, wnd.mouse);
	
	for (int i = 0; i< balloons.size(); i++)
	{
		balloons[i].Update(dtb);
	}
	
}

bool Game::isColliding(const Archer::Arrow& a, Balloon b)
{
	if (a.pos.x + 33.0f >= b.pos.x + 2 &&
		a.pos.x <= b.pos.x + 27.0f &&
		a.pos.y + 6.0f >= b.pos.y + 2 &&
		a.pos.y <= b.pos.y + 32.0f)
	{
		if (!b.isPierced)
		{
			return true;
		}
	}
	return false;
}

void Game::ComposeFrame()
{

	gfx.DrawSprite(0, 0, bckgrnd, SpriteEffect::Copy{});
	archer.Draw(gfx);
	for (int i = 0; i < balloons.size(); i++)
	{
		if(balloons[i].hasPortal)
		balloons[i].portal.Draw(gfx);
	}
	for (int i = 0; i < balloons.size(); i++)
	{
		balloons[i].Draw(gfx);
	}

	
	gfx.DrawSprite(wnd.mouse.GetPosX() - 14, wnd.mouse.GetPosY() - 14, rtcl, SpriteEffect::Chroma{ Color{255,0,255} });

	

}
