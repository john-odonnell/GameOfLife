#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include "golboard.h"

const int SCREEN_HEIGHT = 600;
const int SCREEN_WIDTH = 600;
int CELL_HEIGHT;
int CELL_WIDTH;

SDL_Window* window = NULL;
// SDL_Surface* surface = NULL;
// SDL_Surface* board_surface = NULL;
SDL_Renderer* renderer = NULL;
// SDL_PixelFormat* format = NULL;

bool init(){
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		} else {
            //Get window renderer
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		}
	}

	return success;
}

void close() {
    // destory board surface
    // SDL_FreeSurface(board_surface);
    // board_surface = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

void output_render(GOLBoard &life) {
    // output to std out for testing purposes
    // std::cout << "gen: " << life.get_generation() << std::endl;
    // life.print_board();
    // std::cout << std::endl;

    // set background color and clear board
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // get board heigh and width from life object
    int height = life.get_height();
    int width = life.get_width();

    // iterate through board cell
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (life.get_cell(i, j)) {
                SDL_Rect rect;
                rect.x = i * CELL_WIDTH;
                rect.y = j * CELL_HEIGHT;
                rect.h = CELL_HEIGHT;
                rect.w = CELL_WIDTH;

                // draw cell
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
    // render board on window
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    int height, width;
    
    // take input from std in
    std::cin >> height >> width;

    // fits the board to the const window size
    CELL_HEIGHT = SCREEN_HEIGHT / height;
    CELL_WIDTH = SCREEN_WIDTH / width;

    bool* board;
    board = new bool[height*width];
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            std::cin >> board[(j * width) + i];
        }
    }

    // give input board to life object
    GOLBoard life = GOLBoard(height, width, board);

    // initialize SDL
    init();
    output_render(life);

    // input loop
    // holding down any key updates generations continuously
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                // update board and render onto window
                life.update();
                output_render(life);
            }
        }
    }

    // destruct
    delete[] board;
    life.~GOLBoard();

    return 0;
}