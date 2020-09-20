#pragma once

class Entity {
private:
	int x, y, id, sprite;
public:
	Entity() : x(0), y(0), sprite(0) {}

	int getX() { return x; }
	int getY() { return y; }
	int getSprite() { return sprite; }

	void setX(int x) { this->x=x; }
	void setY(int y) { this->y=y; }
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
