#pragma once

#include <SDL.h>
#include <fstream>
#include <string>

using namespace std;

class Map
{
private:

	SDL_Rect tabRectMap[13][15];
	int tblIntMap[13][15];

	int positionImageX;
	int positionImageY;
	int valeurMap;

	bool showTitle;

	ifstream entree;

	string map;

	SDL_Surface* indestructible;
	SDL_Surface* destructible;  // Bloc destructible
	SDL_Surface* titleScreen; // Écran titre

public:

	Map(); //Constructeur de la classe
	~Map();//Destructeur

	void jeuCommencer();
	void ecranTitre(SDL_Surface* background);
	void genererMap();
	void ouvrirFichier();
	void lireFichier();
	void reinitialisation();
	bool getShowTitle();

};
