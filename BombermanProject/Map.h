#pragma once

#include <SDL.h>
#include <fstream>
#include <string>

using namespace std;

class Map
{
private:

	int positionImageX;
	int positionImageY;
	int valeurMap;

	bool showTitle;

	ifstream entree;

	string mapFile;

	SDL_Surface* indestructible;
	SDL_Surface* destructible;  // Bloc destructible
	SDL_Surface* titleScreen; // Écran titre

public:

	SDL_Rect tblRectMap[13][15];
	int tblIntMap[13][15];
	Map(); // Constructeur de la classe
	~Map();	// Destructeur


	void jeuCommencer();
	void ouvrirFichier();
	void lireFichier();
	void generateMap(SDL_Surface * background);
	void initialiserRectPosition(SDL_Rect tabRectMap[13][15]);
	void reinitialisation();

	void destroyWalls(SDL_Rect positionBombe, bool explosion);


};
