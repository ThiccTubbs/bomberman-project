#include <SDL.h>
#include <iostream>
#include "Bomberman.h"
using namespace std;

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) == -1)	// Error case
	{
		cout << "Erreur lors de l'initialisation de la SDL", SDL_GetError();
		exit(EXIT_FAILURE);
	}

	int tempsPrecedent = 0;

	// The window we'll be rendering to 
	SDL_Window* window = NULL;
	// The surface contained by the window 
	SDL_Surface* screenSurface = NULL;

	// Taille de la fenêtre
	int windowWidth = 800;
	int windowHeight = 600;

	window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);

	// Get window surface 
	screenSurface = SDL_GetWindowSurface(window);


	// Création du personnage Bomberman
	Bomberman john(window);

	bool endGame = false;

	while (endGame == false) // Until user wants to close the window
	{
		// Nettoyer l'écran
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 32, 32, 0));

		// Lire l'événement
		SDL_Event event;

		SDL_PumpEvents();
		const Uint8 * keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) { // User requests quit 
			endGame = true;
		}

		john.changeDirection(keys, tempsPrecedent, screenSurface);
		
		john.walk(tempsPrecedent, screenSurface);

		SDL_UpdateWindowSurface(window); // Update the surface

	}
	
	SDL_DestroyWindow(window);
	window = NULL; //Quit SDL subsystems 
	SDL_Quit();
	return EXIT_SUCCESS;
}
