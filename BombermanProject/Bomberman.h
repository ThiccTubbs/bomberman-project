#pragma once
#include <SDL.h>

class Bomberman
{
public:
	Bomberman(SDL_Window* w);
	~Bomberman();

	// M�thodes

	void changeDirection(const Uint8 * keys, int tempsPrecedent, SDL_Surface* screenSurface);
	/*
	Fonction pour faire marcher le bonhomme
	dep: d�placement sur la spritesheet
	tempsPrecedent: la derni�re fois que PollEvent a retourn� 1 en millisecondes
	depLastSprite: true si on �tait � la fin de la spritesheet, false si on �tait au d�but
	*/
	void walk(int &tempsPrecedent, SDL_Surface* screenSurface);

	void die(SDL_Rect dyingBomberman[8], SDL_Surface* screenSurface, SDL_Rect destination, SDL_Window* window);

	int getPositionX();

	int getPositionY();

private:
	// Constantes
	const int IDLE_SPRITE_ANIMATION_INDEX = 2;
	const char *WALKING_SPRITES_FILE = "bomberman.bmp";
	const char *DYING_SPRITES_FILE = "bombermandie.bmp";
	const float INITIAL_X_POSITION = 0.0f;
	const float INITIAL_Y_POSITION = 0.0f;
	const int DYING_ANIMATION_FRAMES = 8;
	const int WALKING_DIRECTIONS_FRAMES = 4;
	const int WALKING_FRAMES = 5;


	// Attributs
	unsigned int vie;
	unsigned int bombes;
	unsigned int degatsBombe;

	SDL_Window* window;
	SDL_Surface* walkingSprites;
	SDL_Surface* dyingSprites;

	// Coordonn�es initiales du bonhomme
	float positionImageX;
	float positionImageY;

	// Position du walkingSprites dans la fen�tre
	SDL_Rect destination;

	// Direction � laquelle le bonhomme fait face (lignes)
	int dir;
	// D�placements du bonhomme sur la spritesheet (colonnes)
	int dep;

	bool depLastSprite;
	bool animateWalk;

	// Table containing dying sprites from the sprite sheet
	SDL_Rect dyingBomberman[8];
	SDL_Rect walkingBomberman[4][5];

	// M�thodes 
	void initializeSprites(SDL_Rect walkingBomberman[4][5], SDL_Rect dyingBomberman[8]);
	void initializeWalkingSprites(SDL_Rect walkingBomberman[4][5]);
	void initializeDyingSprites(SDL_Rect dyingBomberman[8]);

};

