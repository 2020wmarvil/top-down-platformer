#pragma once

#ifndef VIEWPORT_TILES
#define VIEWPORT_TILES 1
#endif

#include <string>

#include "tile.h"

class Square { 
public:
	Tile *tile;
	Entity * entity;

	Square(Tile *tile=nullptr, Entity *entity=nullptr) : tile(tile), entity(entity) {}
};

class Level {
private:
	Square board[VIEWPORT_TILES][VIEWPORT_TILES];
public:
	Level() {}
	~Level() {}

	const Tile& getTile(int x, int y) { return *(board[x][y].tile); }
	const Entity& getEntity(int x, int y) { return *(board[x][y].entity); }
	const Square& getSquare(int x, int y) { return board[x][y]; }

	void setTile(int x, int y, Tile *tile) { board[x][y].tile = tile; }
	void setEntity(int x, int y, Entity *entity) { board[x][y].entity = entity; }
};
