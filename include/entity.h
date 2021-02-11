#pragma once

class Entity {
protected:
	int x, y, id, sprite;

	bool isTileValid(int x, int y) {
		return x >=0 && x < VIEWPORT_TILES && y >=0 && y < VIEWPORT_TILES;
	}
public:
	Entity() : x(0), y(0), sprite(0) {}

	int getX() { return x; }
	int getY() { return y; }
	int getSprite() { return sprite; }

	void setX(int x) {
		if (isTileValid(x, this->y)) {
			this->x=x;
		}
	}
	void setY(int y) {
		if (isTileValid(this->x, y)) {
			this->y=y;
		}
	}
	void setSprite(int sprite) { this->sprite=sprite; }

//	virtual void onCollide(const Entity& entity);// {
//			if (entit.id = PLAYER_ID) {
//					// do nothing
//			}
//
//			if (entit.id = zomie_id) {
//					this->hp - entity.damage;
//			}
//
//	}
};
