#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{

public:
	Board(Graphics& gfx, int offsetForTheGrid);
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc)const;
private:
	static constexpr int cellDimension = 20;
	static constexpr int width = Graphics::ScreenWidth/cellDimension;
	static constexpr int height = Graphics::ScreenHeight/cellDimension;
	int gridOffset;
	Graphics& gfx;
};