// Classe Bomberman pour le personne principal du jeu

#include "Bomberman.h"


Bomberman::Bomberman(SDL_Window* w)
{
	window = w;

	dep = IDLE_SPRITE_ANIMATION_INDEX;
	dir = 0;
	depLastSprite = false;
	animateWalk = false;

	positionImageX = INITIAL_X_POSITION;
	positionImageY = INITIAL_Y_POSITION;

	walkingSprites = SDL_LoadBMP(WALKING_SPRITES_FILE);
	dyingSprites = SDL_LoadBMP(DYING_SPRITES_FILE);

	dyingBomberman[DYING_ANIMATION_FRAMES] = {};
	walkingBomberman[WALKING_DIRECTIONS_FRAMES][WALKING_FRAMES] = {};

	initializeSprites(walkingBomberman, dyingBomberman);

}

void Bomberman::initializeSprites(SDL_Rect walkingBomberman[4][5], SDL_Rect dyingBomberman[8]) {

	
	SDL_SetColorKey(walkingSprites, SDL_TRUE, SDL_MapRGB(walkingSprites->format, 255, 0, 0)); // Set transparency
		
	SDL_SetColorKey(dyingSprites, SDL_TRUE, SDL_MapRGB(dyingSprites->format, 255, 0, 0)); // Set transparency

	initializeWalkingSprites(walkingBomberman);
	initializeDyingSprites(dyingBomberman);
}

void Bomberman::initializeWalkingSprites(SDL_Rect walkingBomberman[4][5]) { // Initialize walking sprites

	float spriteWidth = 0.0f;
	float spriteHeight = 0.0f;

	for (int i = 0; i < 4; i++) {
		switch (i) {
		case 0:
			spriteWidth = 21.2f;
			spriteHeight = 35.0f;
			break;
		case 1:
			spriteWidth = 21.6f;
			spriteHeight = 34.0f;
			break;
		case 2:
			spriteWidth = 21.6f;
			spriteHeight = 33.0f;
			break;
		case 3:
			spriteWidth = 21.4f;
			spriteHeight = 32.0f;
			break;
		}
		for (int j = 0; j < 5; j++) { // 1ere ligne de la spritesheet
			walkingBomberman[i][j].x = (float)j * spriteWidth;
			walkingBomberman[i][j].y = (float)i*spriteHeight;
			walkingBomberman[i][j].w = spriteWidth;
			walkingBomberman[i][j].h = spriteHeight;
		}
	}
}

void Bomberman::initializeDyingSprites(SDL_Rect dyingBomberman[8]) { // Initialize death sprites

	float spriteWidth = 0.0f;
	float spriteWidthCompiled = 0.0f;
	for (int j = 0; j < 8; j++) {
		if (j == 6 || j == 0 || j == 1 || j == 7) {
			spriteWidth = 21.0f;
		}
		else if (j == 2 || j == 4) {
			spriteWidth = 25.0f;
		}
		else if (j == 5) {
			spriteWidth = 20.0f;
		}
		else if (j == 3) {
			spriteWidth = 30.0f;
		}

		dyingBomberman[j].x = spriteWidthCompiled;
		dyingBomberman[j].y = 0;
		dyingBomberman[j].w = spriteWidth;
		dyingBomberman[j].h = 35;

		spriteWidthCompiled += spriteWidth;
	}

}

void Bomberman::changeDirection(const Uint8 * keys, int tempsPrecedent, SDL_Surface* screenSurface) {

	if (keys[SDL_GetScancodeFromKey(SDLK_d)]) {
		dir = 1;
		positionImageX += 0.2f;
		animateWalk = true;
	}
	else if (keys[SDL_GetScancodeFromKey(SDLK_a)]) {
		dir = 3;
		positionImageX -= 0.2f;
		animateWalk = true;
	}
	else if (keys[SDL_GetScancodeFromKey(SDLK_w)]) {
		dir = 2;
		positionImageY -= 0.2f;
		animateWalk = true;
	}
	else if (keys[SDL_GetScancodeFromKey(SDLK_s)]) {
		dir = 0;
		positionImageY += 0.2f;
		animateWalk = true;
	}

	else {
		dep = 2;
		animateWalk = false;
	}

	destination.x = positionImageX;
	destination.y = positionImageY;
	destination.w = 100;
	destination.h = 100;


}

void Bomberman::walk(int &tempsPrecedent, SDL_Surface* screenSurface) {
	int tempsActuel = SDL_GetTicks(); // Temps actuel = le temps écoulé depuis l'exécution du programme en millisecondes

	if (animateWalk && (tempsActuel - tempsPrecedent) > 70) // Si 70 ms se sont écoulées
	{
		if (depLastSprite == true) {
			dep--;
			if (dep == -1) {
				depLastSprite = false;
				dep = 2;
			}
		}
		else if (depLastSprite == false) {
			dep++;
			if (dep == 5) {
				depLastSprite = true;
				dep = 2;
			}
		}

		tempsPrecedent = tempsActuel; // Le temps "actuel" devient le temps "precedent" pour nos futurs calculs

	}

	SDL_BlitSurface(walkingSprites, &walkingBomberman[dir][dep], screenSurface, &destination); // Affichage du walkingSprites

}

void Bomberman::die(SDL_Rect dyingBomberman[8], SDL_Surface * screenSurface, SDL_Rect destination, SDL_Window * window)
{
	int tempsActuel = SDL_GetTicks();

	for (int i = 0; i < 8; i++) {
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 32, 160, 0)); // Nettoyer l'écran
		SDL_BlitSurface(dyingSprites, &dyingBomberman[i], screenSurface, &destination); // Affichage du walkingSprites
		SDL_UpdateWindowSurface(window); // Update the surface 
		SDL_Delay(70);
	}
}


Bomberman::~Bomberman()
{
	SDL_FreeSurface(walkingSprites);
	walkingSprites = NULL; //Destroy window 
}


