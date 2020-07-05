/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include <random>
#include "Surface.h"
#include "Animation.h"
#include "FrameTimer.h"
#include "Archer.h"
#include "Portal.h"
#include "Balloon.h"
#include "Bomb.h"
#include "SpriteEffect.h"
#include "Font.h"
#include "Sound.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	std::random_device rd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist1;
	std::uniform_int_distribution<int> xDist2;
	std::uniform_int_distribution<int> x1v2;

	bool gameIsStarted = false;
	bool gameIsOver = false;

	int counter = 0;
	int hearts = 3;
	int score = 0;
	bool paused = false;

	float pauseTime = 0.0f;
	float pauseDuration = 4.0f;

	Surface bckgrnd = "Images\\Background.bmp";
	Surface startScreen = "Images\\StartScreen.bmp";
	Surface gameOverScreen = "Images\\GameOverScreen.bmp";
	Surface rtcl = "Images\\Reticle.bmp";
	Surface scoreBar = "Images\\ScoreBar188x39.bmp";
	Surface heart = "Images\\Heart12x13.bmp";
	FrameTimer ft;
	Archer archer = Archer({367.0f,250.0f});

	Balloon b1 = Balloon({0.0f,0.0f}, 0.0f);
	int numOfBalloons = 16;
	float balloonSpawnCounter = 0.0f;
	float balloonSpawnDelay = 0.384f;
	std::vector<Balloon> balloons;

	Bomb bomb1 = Bomb({ 100.0f,-100.0f });
	std::vector<Bomb> bombs;
	float bombSpawnCounter = 0.0f;
	float bombSpawnDelay = 10.0f;

	Font font = "Images\\Font.bmp";

	Sound startMusic = Sound(L"Sounds\\startScreen.wav", Sound::LoopType::AutoFullSound);
	Sound music = Sound(L"Sounds\\Music.wav", Sound::LoopType::AutoFullSound);
	Sound gameOverMusic = Sound(L"Sounds\\GameOver.wav");
	Sound soundPause = Sound(L"Sounds\\Pause.wav");
	Sound soundPop = Sound( L"Sounds\\BalloonPop.wav");
	Sound soundExplosion = Sound(L"Sounds\\Explosion.wav");
	
	/********************************/
};