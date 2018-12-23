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
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 2,2 }),
	goal(rng, brd, snek),
	brdOffset(20)
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
	if (!gameStarted && !gameIsOver)
	{
		SpriteCodex::DrawTitle(gfx.ScreenWidth / 2 - 213/2, gfx.ScreenHeight / 2 - 70, gfx);
		
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			gameStarted = true;
		}
	}
	else if (!gameIsOver && gameStarted) {
		if (wnd.kbd.KeyIsPressed(VK_UP)) {
			delta_loc = { 0, -1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
			delta_loc = { 0, 1 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
			delta_loc = { -1, 0 };
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
			delta_loc = { 1, 0 };
		}
		++snakeMoveCounter;

		if (snakeMoveCounter > snakeMoveRate)
		{
			snakeMoveCounter = 0;
			const Location nextSnekLoc = snek.GetNextHeadLoc(delta_loc);
			if (!brd.IsInsideBoard(nextSnekLoc) ||
				snek.IsInTileExceptEnd(nextSnekLoc))
			{
				gameIsOver = true;
			}
			else {
				const bool snekEating = nextSnekLoc == goal.GetLocation();
				if (snekEating)
				{
					snek.Grow();
				}
				snek.MoveBy(delta_loc);
				if (snekEating)
				{
					snek.MoveBy(delta_loc);
					goal.Respawn(rng, brd, snek);
				}
			}
		}
	}
	
}

void Game::ComposeFrame()
{

	//Draw border
	//for (int x = 0; x < gfx.ScreenWidth; ++x)
	//{
	//	for (int y = 0; y < gfx.ScreenHeight; ++y)
	//	{
	//		if((x <= brdOffset) || (y <= brdOffset) || (y >= gfx.ScreenHeight - brdOffset) || (x >= gfx.ScreenWidth - brdOffset))
	//		gfx.PutPixel(x, y, Colors::Cyan);
	//		//if()
	//	}
	//}
	

	if (gameStarted) {
	snek.Draw(brd);
	goal.Draw(brd);
	}
	if (gameIsOver)
	{
		SpriteCodex::DrawGameOver(gfx.ScreenWidth/2 - 50,gfx.ScreenHeight/2 - 50, gfx);
	}
}
