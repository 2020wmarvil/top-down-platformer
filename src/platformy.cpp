#define VIEWPORT_TILES 15

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "res_path.h"
#include "event_handler.h"
#include "player.h"
#include "enemy.h"
#include "tile.h"
#include "level.h"

int SCREEN_WIDTH=640, SCREEN_HEIGHT=480;
bool exit_game_loop = false;

int tile_width, viewport_size, x_offset, y_offset;

const int win_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;

const std::string resource_path = getResourcePath();

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip=nullptr);
void updateDisplay(SDL_Window* win);

Uint32 enemyPathing(Uint32 interval, void *params);

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window *win = SDL_CreateWindow("Platformy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, win_flags);

	updateDisplay(win);

	SDL_Renderer *ren = SDL_GetRenderer(win);
	if(!ren) ren = SDL_CreateRenderer(win, -1, 0);

	SDL_Texture *tile_textures[] = {
		loadTexture(resource_path + "grass_tile.png", ren),
		loadTexture(resource_path + "sand_tile.png", ren),
		loadTexture(resource_path + "cobble_tile.png", ren)
	};

	SDL_Texture *spritesheet = loadTexture(resource_path + "npc_spritesheet.png", ren);
	SDL_Texture *enemy_sprite = loadTexture(resource_path + "gary.png", ren);

	// LOAD TILE ARRAY
	Level level;
	for (int c=0; c<VIEWPORT_TILES; c++) {
		for (int r=0; r<VIEWPORT_TILES; r++) {
			level.setTile(r, c, new Tile((r+c) % 2));
		}
	}

	Player player;
	Enemy enemy(&player);

	SDL_TimerID enemy_pathing_timer = SDL_AddTimer(1000, enemyPathing, &enemy);

	SDL_Event event;
	EventHandler handler(&player);
	while (!exit_game_loop){
		while (SDL_PollEvent(&event)){
			exit_game_loop = handler.handleEvent(event);
		}

		SDL_SetRenderDrawColor(ren, 50, 50, 100, 255);
		SDL_RenderClear(ren);

		for (int c=0; c<VIEWPORT_TILES; c++) {
			for (int r=0; r<VIEWPORT_TILES; r++) {
				renderTexture(tile_textures[level.getTile(r, c).getTileID()],
						ren, x_offset + c*tile_width, y_offset + r*tile_width);
			}
		}

		int sprite_cols = 4, sprite_rows = 4, sprite_size = 16;
		//int sprite = (SDL_GetTicks() / 500) % (sprite_cols*sprite_rows);
		int sprite = player.getSprite();

		SDL_Rect player_clip;

		player_clip.x = (sprite % sprite_cols) * sprite_size;
		player_clip.y = (sprite / sprite_rows) * sprite_size;
		player_clip.w = sprite_size; player_clip.h = sprite_size;

		renderTexture(spritesheet, ren, x_offset + player.getX() * tile_width,
						y_offset + player.getY() * tile_width,
						&player_clip);

		SDL_Rect enemy_clip;

		enemy_clip.x = 0; enemy_clip.y = 0;
		enemy_clip.w = sprite_size; enemy_clip.h = sprite_size;
		renderTexture(enemy_sprite, ren, x_offset + enemy.getX() * tile_width,
						y_offset + enemy.getY() * tile_width,
						&enemy_clip);

		SDL_RenderPresent(ren);

		std::string error;
		if ((error=SDL_GetError()) != "") { std::cout << error << std::endl; }
	}

	SDL_Quit();

	return 0;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());

	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip) {
	SDL_Rect dst;
	dst.x = x; dst.y = y;

	dst.w = tile_width;
	dst.h = tile_width;

	SDL_RenderCopy(ren, tex, clip, &dst);
}

void updateDisplay(SDL_Window* win) {
	SDL_Rect r;
	SDL_GetDisplayUsableBounds(0, &r);
	SCREEN_WIDTH = r.w;
	SCREEN_HEIGHT = r.h;
	SDL_SetWindowSize(win, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Surface* surface = SDL_GetWindowSurface(win);
	tile_width = std::min(surface->w, surface->h) / VIEWPORT_TILES;

	viewport_size = tile_width * VIEWPORT_TILES;

	x_offset = (surface->w - viewport_size) / 2;
	y_offset = (surface->h - viewport_size) / 2;
}

Uint32 enemyPathing(Uint32 interval, void *params) {
	((Enemy*)params)->path();

	return interval;
}
