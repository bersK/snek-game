#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx, int offsetForTheGrid)
	:
	gfx(gfx),
	gridOffset(offsetForTheGrid)
{

}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= gridOffset);
	assert(loc.x < width-gridOffset);
	assert(loc.y >= gridOffset);
	assert(loc.y < height-gridOffset);
	gfx.DrawRectDim(loc.x*cellDimension, loc.y*cellDimension, cellDimension, cellDimension, c);
}

int Board::GetGridWidth() const
{
	return width-gridOffset;
}

int Board::GetGridHeight() const
{
	return height-gridOffset;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return 
		loc.x <= (width-gridOffset) && 
		loc.x >= gridOffset &&
		loc.y >= gridOffset && 
		loc.y <= (height-gridOffset);
}
