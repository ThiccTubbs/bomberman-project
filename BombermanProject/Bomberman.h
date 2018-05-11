#pragma once
#include <SDL.h>

class Bomberman
{
public:
	Bomberman(SDL_Window* w);
	~Bomberman();

	// Méthodes

	void changeDirection(const Uint8 * keys, SDL_Surface* screenSurface, SDL_Rect tblRectMap[13][15], int tblIntMap[13][15]);

	/*
	Fonction pour faire marcher le bonhomme
	lastTime: la dernière fois que PollEvent a retourné 1 en millisecondes
	screenSurface: surface sur laquelle le bomberman est affiché
	*/
	void walk(float &lastTime, SDL_Surface* screenSurface);

	/*
	Fonction pour faire marcher le bonhomme
	dyingBomberman: tableau contenant les sprites d'animation de la mort du bomberman
	screenSurface: surface sur laquelle le bomberman est affiché
	destination: position à laquelle le bomberman se situe à sa mort et où l'animation doit se faire
	window: pour rafraîchir l'affichage dans la fenêtre
	*/
	void die(SDL_Rect dyingBomberman[8], SDL_Surface* screenSurface, SDL_Rect destination, SDL_Window* window);

	int getPositionX();
	int getPositionY();
	SDL_Rect getDestination();

	int getEndX();
	int getEndY();

	int startX;
	int startY;
	int endX;
	int endY;

private:
	// Constantes
	const int IDLE_SPRITE_ANIMATION_INDEX = 2;
	const char *WALKING_SPRITES_FILE = "bomberman.bmp";
	const char *DYING_SPRITES_FILE = "bombermandie.bmp";
	const float INITIAL_X_POSITION = 50.0f;
	const float INITIAL_Y_POSITION = 50.0f;
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

	// Coordonnées initiales du bonhomme
	float positionImageX;
	float positionImageY;

	// Position du walkingSprites dans la fenêtre
	SDL_Rect destination;

	// Direction à laquelle le bonhomme fait face (lignes)
	int dir;
	// Déplacements du bonhomme sur la spritesheet (colonnes)
	int dep;

	bool depLastSprite;
	bool animateWalk;

	// Table containing dying sprites from the sprite sheet
	SDL_Rect dyingBomberman[8];
	SDL_Rect walkingBomberman[4][5];

	// Méthodes 
	void initializeSprites(SDL_Rect walkingBomberman[4][5], SDL_Rect dyingBomberman[8]);
	void initializeWalkingSprites(SDL_Rect walkingBomberman[4][5]);
	void initializeDyingSprites(SDL_Rect dyingBomberman[8]);

};

