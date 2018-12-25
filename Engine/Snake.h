#pragma once
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(const Color& in_color);
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd) const;
		const Location GetLocation() const;
		
	private:
		Location loc;
		Color c;
		
	};
public:
	Snake(const Location& loc);
	Location GetNextHeadLoc(const Location& delta_loc) const;
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& brd)const;
	void ResetSnake();
	int GetSnakeSegmentsCount();
	void StoreInitLocation(const Location& init_loc);
	bool IsInTileExceptEnd(const Location& target_loc) const;
	bool IsInTile(const Location& target_loc) const;
private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor = Colors::White;
	static constexpr Color bodyColorAlt = Colors::LightGray;
	static constexpr int nSegmentsMax = 100;
	Location initLocation;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};