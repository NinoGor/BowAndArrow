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
	xDist(350, 700),
	yDist(100, 400)
{
	balloons.emplace_back(Vec2((float)xDist(rng), (float)yDist(rng)));
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
	if (!(archer.isShooting))
	{
		archer.dir = { 0.0f,0.0f };
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			archer.dir.y -= 1.0f;
			archer.isMoving = true;
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			archer.dir.y += 1.0f;
			archer.isMoving = true;
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			archer.dir.x -= 1.0f;
			archer.isMoving = true;
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			archer.dir.x += 1.0f;
			archer.isMoving = true;
		}
		else
		{
			archer.isMoving = false;
		}
	}
	if (!archer.isMoving)
	{
		const auto e = wnd.kbd.ReadKey();
		if (e.IsPress() && e.GetCode() == VK_SPACE)
		{
			archer.isShooting = true;
			archer.isStretching = true;
			archer.shootingTime = 0.0f;
		}
		else if (e.IsRelease() && e.GetCode() == VK_SPACE)
		{
			archer.isStretching = false;
			archer.bowIsStretched = false;
			archer.isShooting = false;

		}
	}
	

	for (int n = 0; n < balloons.size(); n++)
	{
		if (balloons[n].isOutOfScreen)
		{
			balloons.erase(balloons.begin() + n);
			balloons.emplace_back(Vec2{ (float)xDist(rng), (float)yDist(rng) });
		}
		for (int i = 0; i < archer.arrows.size(); i++)
		{
			if (isColliding(archer.arrows[i], balloons[n]))
			{
				balloons[n].isPierced = true;
			}
		}
	}


	archer.SetDirection();
	archer.ClampToRect(RectI{ 0,(Graphics::ScreenWidth) / 3,0,Graphics::ScreenHeight });
	archer.Update(dt);
	
	for (int i = 0; i< balloons.size(); i++)
	{
		balloons[i].Update(dt);
	}
	
	
	
}

bool Game::isColliding(const Archer::Arrow& a, Balloon b)
{
	return
		a.pos.x + 33.0f >= b.pos.x + 2 &&
		a.pos.x <= b.pos.x + 27.0f &&
		a.pos.y + 6.0f >= b.pos.y + 2 &&
		a.pos.y <= b.pos.y + 36.0f; // height minus the string

}

void Game::ComposeFrame()
{

	gfx.DrawSprite(0, 0, bckgrnd, SpriteEffect::Copy{});
	for (int i = 0; i< balloons.size(); i++)
	{
		balloons[i].portal.Draw(gfx);
		balloons[i].Draw(gfx);
	}
	archer.Draw(gfx);
	
	
}
