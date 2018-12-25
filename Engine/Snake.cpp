#include "Snake.h"
#include <assert.h>

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(const Color& in_color)
{
	c = in_color;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location Snake::Segment::GetLocation() const
{
	return loc;
}

Snake::Snake(const Location & loc)
{
	segments[0].InitHead(loc);
	StoreInitLocation(loc);
}

void Snake::StoreInitLocation(const Location & init_loc)
{
	initLocation = init_loc;
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i-1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		if(nSegments%2 == 0)
			segments[nSegments].InitBody(bodyColor);
		else {
			segments[nSegments].InitBody(bodyColorAlt);
		}
		++nSegments;
	}
}

void Snake::ResetSnake()
{
	nSegments = 1;
	segments[0].InitHead(initLocation);
}

int Snake::GetSnakeSegmentsCount()
{
	return nSegments;
}

void Snake::Draw(Board & brd) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location & target_loc) const
{
	bool result = false;
	for (int i = 0; i < nSegments - 1; ++i)
	{
		if (segments[i].GetLocation() == target_loc)
		{
			result = true;
		}
	}
	return result;
}

bool Snake::IsInTile(const Location & target_loc) const
{
	bool result = false;
	for (int i = 0; i < nSegments; ++i)
	{
		if (segments[i].GetLocation() == target_loc)
		{
			result = true;
		}
	}
	return result;
}

Location Snake::GetNextHeadLoc(const Location & delta_loc) const
{
	Location l = segments[0].GetLocation();
	l.Add(delta_loc);
	return l;
}
