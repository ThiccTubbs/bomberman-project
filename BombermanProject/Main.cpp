// BombermanProject.cpp: définit le point d'entrée pour l'application console.

#include <iostream>
#include <string>
#include <SDL.h>
#include "Game.h"

using namespace std;

int main(int argc, char* argv[]) {

	SDL_Window* window = NULL; // Fenêtre

	SDL_Surface* background = NULL; // Arrière-plan

	const int LARGEUR = 750; // Largeur de l'écran
	const int HAUTEUR = 650; // Hauteur de l'écran

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cout << "Erreur lors de l'initialisation de la SDL", SDL_GetError(); // S'il y a une erreur
		exit(EXIT_FAILURE);
	}

	// Créer la fenêtre
	window = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN);

	// Obtenir la surface de la fenêtre
	background = SDL_GetWindowSurface(window);

	Game* game = new Game(window, background);

	game->start();

	SDL_DestroyWindow(window); // Détruire la fenêtre

	SDL_Quit(); // Arrêt de SDL (libération de la mémoire)

	return EXIT_SUCCESS;
}
