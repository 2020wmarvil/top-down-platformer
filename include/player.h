#pragma once

class Player {
private:
	int x, y, sprite=0;
public:
	Player() {
		x=0;
		y=0;
	}

	int getX() { return x; }
	int getY() { return y; }
	int getSprite() { return sprite; }

	void setX(int x) { this->x=x; }
	void setY(int y) { this->y=y; }
	void setSprite(int sprite) { this->sprite=sprite; }
};
