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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
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
	float dt = fpst.Mark();

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
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		if (!archer.isMoving)
		{
			archer.isShooting = true;
			archer.arrowIsBeingShot = true;
		}
	}
	if (archer.isShooting)
	{
		counter += 1;
		if (counter >= int(1.1f * FPS)/*(1.0f/dt)*/)
		{
			archer.isShooting = false;
			counter = 1;
		}
	}

	archer.Shooting(ft2.Mark());
	archer.SetDirection();
	archer.ClampToRect(RectI{ 0,(Graphics::ScreenWidth) / 3,0,Graphics::ScreenHeight });
	archer.Update(ft.Mark());
	//balloons.emplace_back(Vec2{200.0f, 200.0f});
	//b1.Update(ft.Mark());
	b1.DrawAndUpdate(gfx, b.Mark());
	

	
}

void Game::ComposeFrame()
{
	for (int i = 0; i < 600; i++)
	{
			gfx.PutPixel(Graphics::ScreenWidth / 3, i, Colors::Cyan);
	}
	archer.Draw(gfx);
	
}
