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
	if (wnd.kbd.KeyIsPressed(VK_SPACE))
	{
		archer.isShooting = true;
		
	}
	
	if(archer.isShooting)
	{
		counter++;
		if ((float)counter >= 2.2f * (1.0f/dt))
		{
			archer.isShooting = false;
			counter = 0;
		}
		
	}
	
	if (!archer.isShooting)
	{
		archer.dir = { 0.0f,0.0f };
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			archer.dir.y -= 1.0f;
		}
		if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			archer.dir.y += 1.0f;
		}
		if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			archer.dir.x -= 1.0f;
		}
		if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			archer.dir.x += 1.0f;
		}
	}
	
	archer.SetDirection();
	
	archer.Update(ft.Mark());
}

void Game::ComposeFrame()
{
	archer.Draw(gfx);
}
