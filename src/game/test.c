#include <stdio.h>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_dreamcast.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define BLK_HEIGHT 15
#define BLK_WIDTH 20

int main() {
	SDL_Surface *screen;                                         
        SDL_Surface *image;
	SDL_Rect sprite_position;
	SDL_Event event;
	int game_over = 0;

        Uint32 flags = SDL_SWSURFACE|SDL_FULLSCREEN;
        screen = SDL_SetVideoMode(640, 480, 16, flags);
        //screen = SDL_SetVideoMode(1920, 1080, 16, flags);

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                return -1;
        }

	// Dreamcast Specific
	//SDL_DC_ShowAskHz(SDL_FALSE);
	//SDL_DC_Default60Hz(SDL_FALSE);
	//SDL_DC_VerticalWait(SDL_FALSE);
	//SDL_DC_SetVideoDriver(SDL_DC_DMA_VIDEO);

        image = IMG_Load("assets/player.png");
	SDL_DisplayFormat(image);

	sprite_position.x = 0;
	sprite_position.y = 0;

	// Draw Level (Put into function)
	FILE *lvl_file = fopen("levels/lvl01.lvl", "r");
	if (lvl_file == NULL) {
		printf("File open failed.\n");
	}

	char temp_row_read[BLK_WIDTH];

	for (int i = 0; i < BLK_HEIGHT; i++) {
		fscanf(lvl_file, "%s", &temp_row_read);
        	printf("%s\n", temp_row_read);
	}
	fclose(lvl_file);

	while (!game_over)
	{
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_q) {
					game_over = 1;
				}
				if (event.key.keysym.sym == SDLK_UP) {
                                        sprite_position.y -= 32;
                                }
				if (event.key.keysym.sym == SDLK_DOWN) {
                                        sprite_position.y += 32;
                                }
				if (event.key.keysym.sym == SDLK_LEFT) {
                                        sprite_position.x -= 32;
                                }
				if (event.key.keysym.sym == SDLK_RIGHT) {
                                        sprite_position.x += 32;
                                }
			}
		}
		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

		SDL_BlitSurface(image, NULL, screen, &sprite_position);
		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}

	SDL_FreeSurface(image);
	SDL_Quit();

	printf("Hello World!\n");
}
