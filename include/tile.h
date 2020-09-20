#pragma once

class Tile {
private:
	int tile_id;
public:
	Tile(int tile_id) { this->tile_id = tile_id; }
	~Tile() {}

	int getTileID() const { return tile_id; }
};
