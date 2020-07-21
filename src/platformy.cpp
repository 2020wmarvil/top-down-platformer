#include <iostream>

#include <SDL2/SDL.h>
#include <SDL_image.h>

#include "res_path.h"

int SCREEN_WIDTH, SCREEN_HEIGHT;

const int viewport_tiles = 11;
int tile_width, viewport_size, x_offset, y_offset;

const int win_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;

const std::string resource_path = getResourcePath();

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, SDL_Rect *clip=nullptr);
void updateDisplay(SDL_Window* win);

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	SDL_Window *win = SDL_CreateWindow("Platformy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, win_flags);

	updateDisplay(win);

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture *background = loadTexture(resource_path + "default_tile.png", ren);
	SDL_Texture *spritesheet = loadTexture(resource_path + "npc_spritesheet.png", ren);	

	int bW, bH;
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);

	SDL_Event event;
	bool quit=false;
	while (!quit){
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) quit = true;
		}

		SDL_SetRenderDrawColor(ren, 50, 50, 100, 255);
		SDL_RenderClear(ren);

		for (int c=0; c<viewport_tiles; c++) {
			for (int r=0; r<viewport_tiles; r++) {
				renderTexture(background, ren, x_offset + c*tile_width, y_offset + r*tile_width);
			}
		}
		
		int sprite = 0, sprite_size = 16;
		int sprite_cols = 4, sprite_rows = 4;
		SDL_Rect player_clip;
		player_clip.x = (sprite % sprite_cols) * sprite_size;
		player_clip.y = (sprite / sprite_rows) * sprite_size;
		player_clip.w = sprite_size; player_clip.h = sprite_size;

		renderTexture(spritesheet, ren, x_offset + (viewport_size / 2) - (tile_width / 2), 
					   y_offset + (viewport_size / 2) - (tile_width / 2), &player_clip);
		
		SDL_RenderPresent(ren);
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
	tile_width = std::min(surface->w, surface->h) / viewport_tiles;

	viewport_size = tile_width * viewport_tiles;

	x_offset = (surface->w - viewport_size) / 2;
	y_offset = (surface->h - viewport_size) / 2;
}
