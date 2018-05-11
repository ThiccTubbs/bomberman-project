#pragma once
#include <SDL.h>
#include "Bomberman.h"
#include "Bomb.h"
#include "Map.h"

class Game {

public:
	Game(SDL_Window* w, SDL_Surface* b);
	~Game();

	void start();

private:

	// Attributs
	SDL_Window* window;
	SDL_Surface* background;

	Bomb* bomb;
	Map* map;
	Bomberman* bomberman;

	bool gameOver; // État de la partie
	float lastTime; // L'ancien temps obtenu
	float lastTimeBomberman;
	float currentTime; // Le temps actuel obtenu avec SDL_GetTicks()
	float timeFrame; // Le nombre de secondes attendues	
	float deltaTime; // La différence de temps entre lastTime et currentTime

};

