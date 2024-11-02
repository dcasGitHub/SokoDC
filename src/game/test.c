#include <stdio.h>
//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_dreamcast.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#define SCR_HEIGHT 480
#define SCR_WIDTH 640

#define BLK_SIZE 32
#define BLK_HEIGHT 15
#define BLK_WIDTH 20

struct level_blocks {
	int x_pos, y_pos;
	char block_type;
};

int main() {
	SDL_Surface *screen;                                         
	
	SDL_Event event;
	int game_over = 0;

        Uint32 flags = SDL_SWSURFACE|SDL_FULLSCREEN;
        screen = SDL_SetVideoMode(SCR_WIDTH, SCR_HEIGHT, 16, flags);

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                return -1;
        }

	// Dreamcast Specific
	//SDL_DC_ShowAskHz(SDL_FALSE);
	//SDL_DC_Default60Hz(SDL_FALSE);
	//SDL_DC_VerticalWait(SDL_FALSE);
	//SDL_DC_SetVideoDriver(SDL_DC_DMA_VIDEO);
	
	SDL_Surface *bg;
	bg = IMG_Load("assets/bg.png");

        SDL_Surface *player_sprite;
	SDL_Rect player_pos;
        player_sprite = IMG_Load("assets/player.png");

	player_pos.x = 0;
	player_pos.y = 0;

	// Draw Level (Put into function)
	FILE *lvl_file = fopen("levels/lvl01.lvl", "r");
	if (lvl_file == NULL) {
		printf("File open failed.\n");
	}

	SDL_Surface *wall_sprite;
	wall_sprite = IMG_Load("assets/wall.png");
	SDL_Rect wall_pos;

	SDL_Surface *crate_sprite;
	crate_sprite = IMG_Load("assets/crate.png");
        SDL_Rect crate_pos;

	char temp_row_read[BLK_HEIGHT * BLK_WIDTH];
	char temp_char_read;
	int x_counter = 0;
	int y_counter = 0;
	int total_counter = 0;
	struct level_blocks level_01_array[BLK_HEIGHT * BLK_WIDTH];

	for (int i = 0; i < BLK_HEIGHT; i++) {
		fscanf(lvl_file, "%s", &temp_row_read);
		for (int j = 0; j < BLK_WIDTH; j++) {
			level_01_array[j].y_pos = y_counter;
			level_01_array[i].x_pos = x_counter;
			level_01_array[total_counter].block_type
				= temp_row_read[j];
			y_counter++;
			total_counter++;
		}
		x_counter++;
		y_counter = 0; // Reset counter when row finishes
	}
	fclose(lvl_file);

	printf("\n");

	int total_counter_2 = 0; // We will need to seperate this

	for (int i = 0; i < BLK_HEIGHT; i++) {
		for (int j = 0; j < BLK_WIDTH; j++) {
			/*printf("%d | %d | %c\n",
					level_01_array[j].y_pos,
					level_01_array[i].x_pos,
					level_01_array[total_counter_2].block_type);*/
			
			// TODO: Put these into functions (and consolidate sprites to structs)
			if (level_01_array[total_counter_2].block_type == 'p') {
				// Flipped *_pos.*
				player_pos.x = level_01_array[j].y_pos * BLK_SIZE;
				player_pos.y = level_01_array[i].x_pos * BLK_SIZE;
			}
			if (level_01_array[total_counter_2].block_type == 'b') {
                                // Flipped *_pos.*
                                crate_pos.x = level_01_array[j].y_pos * BLK_SIZE;
                                crate_pos.y = level_01_array[i].x_pos * BLK_SIZE;
			}
			total_counter_2++;
		}
	}

	// Game loop
	SDL_Rect prev_player_pos;
	while (!game_over)
	{
		prev_player_pos = player_pos;

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_q) {
					game_over = 1;
				}
				if (event.key.keysym.sym == SDLK_UP) {
                                        player_pos.y -= BLK_SIZE;
                                }
				if (event.key.keysym.sym == SDLK_DOWN) {
                                        player_pos.y += BLK_SIZE;
                                }
				if (event.key.keysym.sym == SDLK_LEFT) {
                                        player_pos.x -= BLK_SIZE;
                                }
				if (event.key.keysym.sym == SDLK_RIGHT) {
                                        player_pos.x += BLK_SIZE;
                                }
			}
		}

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
		SDL_BlitSurface(bg, NULL, screen, NULL);

		SDL_BlitSurface(player_sprite, NULL, screen, &player_pos);

		total_counter = 0;
		for (int i = 0; i < BLK_HEIGHT; i++) {
			for (int j = 0; j < BLK_WIDTH; j++) {
				// TODO: Figure out why wall_pos.* needs to be flipped
				if (level_01_array[total_counter].block_type == '1') {
					wall_pos.x = level_01_array[j].y_pos * BLK_SIZE;
					wall_pos.y = level_01_array[i].x_pos * BLK_SIZE;
					SDL_BlitSurface(wall_sprite, NULL, screen, &wall_pos);
					if (player_pos.x < wall_pos.x + BLK_SIZE &&
							player_pos.x + player_pos.w > wall_pos.x &&
							player_pos.y < wall_pos.y + BLK_SIZE &&
							player_pos.y + player_pos.h > wall_pos.y) {
						// Collision detected, reset the player's position
						player_pos = prev_player_pos;
					}
				}

				if (level_01_array[total_counter].block_type == 'b') {
					//crate_pos.x = level_01_array[j].y_pos * BLK_SIZE;
					//crate_pos.y = level_01_array[i].x_pos * BLK_SIZE;
					SDL_BlitSurface(crate_sprite, NULL, screen, &crate_pos);
					if (player_pos.x < crate_pos.x + BLK_SIZE &&
                                                        player_pos.x + player_pos.w > crate_pos.x &&
                                                        player_pos.y < crate_pos.y + BLK_SIZE &&
                                                        player_pos.y + player_pos.h > crate_pos.y) {
                                                // Collision detected, reset the player's position
                                                crate_pos.x += BLK_SIZE;
                                        }
                        	}

				total_counter++;
			}
		}

		SDL_UpdateRect(screen, 0, 0, 0, 0);
	}

	// TODO: Free all memory for all sprites
	SDL_FreeSurface(player_sprite);
	SDL_Quit();

	printf("Hello World!\n");
}
