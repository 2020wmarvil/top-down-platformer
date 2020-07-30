#pragma once

#include "player.h"

class EventHandler {
private:
	Player *player;

	bool quit = false;

	void handleKeyDownEvent(SDL_KeyboardEvent &key) {
		switch (key.keysym.scancode) {
			case SDL_SCANCODE_ESCAPE: {
				quit = true; 
				break;
			} case SDL_SCANCODE_D: {
				if(!key.repeat) player->setX(player->getX()+1);
				break;
			} case SDL_SCANCODE_A: {
				if(!key.repeat) player->setX(player->getX()-1);
				break;
			} case SDL_SCANCODE_W: {
				if(!key.repeat) player->setY(player->getY()-1);
				break;
			} case SDL_SCANCODE_S: {
				if(!key.repeat) player->setY(player->getY()+1);
				break;
			} default: {
				break;
			}
		}
	}
	
	void handleKeyUpEvent(SDL_KeyboardEvent &key) {
		switch (key.keysym.scancode) {
			case SDL_SCANCODE_W: {
				break;
			} default: {
				break;
			}
		}
	}
public:
	EventHandler(Player *player) { this->player = player; };
	~EventHandler() {};

	int handleEvent(SDL_Event &event) {
		switch(event.type) {
			case SDL_QUIT: {
				quit = true;
				break;
			} case SDL_KEYDOWN: {
				handleKeyDownEvent(event.key);
				break;
			} case SDL_KEYUP: {
				handleKeyUpEvent(event.key);
				break;
			}
		}

		if (quit) return 1;

		return 0;
	}
};
