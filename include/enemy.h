#pragma once

#include <cmath>

#include "entity.h"

class Enemy : public Entity {
private:
	Entity *target;

	int target_x, target_y;
public:
	Enemy(Entity *target) {
		this->x = 14;
		this->y = 14;

		this->target = target;
	}

	void setTarget(Entity *target) { this->target = target; }

	void path() {
		int del_x = target->getX() - this->x;
		int del_y = target->getY() - this->y;

		int dx = 0, dy = 0;
		if (del_x != 0) dx = (del_x) / (int)abs(del_x);
		if (del_y != 0) dy = (del_y) / (int)abs(del_y);

		if (abs(del_x) >= abs(del_y)) {
			target_x = this->x + dx;
			setX(target_x);
		} else {
			target_y = this->y + dy;
			setY(target_y);
		}

		if (this->x == target->getX() && this->y == target->getY()) {
			Uint32 time = SDL_GetTicks();

			std::cout << "You survived for " << time / 1000.0 << " seconds!\n";
			exit(1);
		}
	}


	
};
