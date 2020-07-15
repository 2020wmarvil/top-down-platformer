#include <iostream>
#include <SDL2/SDL.h>

int SCREEN_WIDTH, SCREEN_HEIGHT;

const int viewport_tiles = 11;
int tile_width, viewport_size, x_offset, y_offset;

const int win_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE;

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void updateDisplay(SDL_Window* win);

int main(int argc, char** argv){
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *win = SDL_CreateWindow("Platformy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, win_flags);

	updateDisplay(win);

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Texture *background = loadTexture("assets/default_tile.bmp", ren);
	SDL_Texture *player = loadTexture("assets/npc.bmp", ren);

	int bW, bH;
	SDL_QueryTexture(background, NULL, NULL, &bW, &bH);

	SDL_Event event;
	while(event.type != SDL_KEYDOWN && event.type != SDL_QUIT) {
		SDL_PollEvent(&event);

		SDL_SetRenderDrawColor(ren, 50, 50, 100, 255);
		SDL_RenderClear(ren);

		for (int c=0; c<viewport_tiles; c++) {
			for (int r=0; r<viewport_tiles; r++) {
				renderTexture(background, ren, x_offset + c*tile_width, y_offset + r*tile_width);
			}
		}
		
		renderTexture(player, ren, x_offset + (viewport_size / 2) - (tile_width / 2), y_offset + (viewport_size / 2) - (tile_width / 2));
		
		SDL_RenderPresent(ren);
	}

	SDL_Quit();

	return 0;
}


SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	texture = SDL_CreateTextureFromSurface(ren, loadedImage);

	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y) {
	SDL_Rect dst;
	dst.x = x; dst.y = y;

	dst.w = tile_width;
	dst.h = tile_width;

	SDL_RenderCopy(ren, tex, NULL, &dst);
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
