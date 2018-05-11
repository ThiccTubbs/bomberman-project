#include "Map.h"

Map::Map() // Constructeur
{
	positionImageX = 0;
	positionImageY = 0;
	valeurMap = 0;
	mapFile = "map1.txt";
	tblRectMap[13][15] = {};
	tblIntMap[13][15] = {};

	indestructible = SDL_LoadBMP("indestructible.bmp");
	destructible = SDL_LoadBMP("destructible.bmp");
	titleScreen = SDL_LoadBMP("titleScreen.bmp");
}

Map::~Map()
{
	SDL_FreeSurface(indestructible);
	SDL_FreeSurface(destructible);
	SDL_FreeSurface(titleScreen);
}

void Map::ouvrirFichier() // Ouvrir le fichier
{
	entree.open(mapFile);
}

void Map::lireFichier()
{
	for (int i = 0; i < 13; i++) // Sert à mettre les valeur de la map dans le tableau
	{
		for (int j = 0; j < 15; j++)
		{
			entree >> valeurMap;
			tblIntMap[i][j] = valeurMap;
		}
	}
}

void Map::generateMap(SDL_Surface* background) {

	initialiserRectPosition(tblRectMap);

	for (int i = 0; i < 13; i++) {

		for (int j = 0; j < 15; j++) {

			if (tblIntMap[i][j] == 1) {
				SDL_BlitSurface(destructible, NULL, background, &tblRectMap[i][j]); // Affiche les blocs destructibles
			}

			else if (tblIntMap[i][j] == 2) {
				SDL_BlitSurface(indestructible, NULL, background, &tblRectMap[i][j]); // Affiche les blocs indestructibles
			}
		}
	}
}

void Map::initialiserRectPosition(SDL_Rect tblRectMap[13][15]) // Initialiser les positions des rectangles sur la grille
{
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 15; j++) {
			tblRectMap[i][j].h = 50;
			tblRectMap[i][j].w = 50;
			tblRectMap[i][j].x = j * 50;
			tblRectMap[i][j].y = i * 50;
		}
	}
}

void Map::reinitialisation() // Réinitialise les valeurs de l'axe X et Y
{
	positionImageX = 0;
	positionImageY = 0;
}


void Map::destroyWalls(SDL_Rect positionBombe, bool explosion) {

	int posX = positionBombe.x / 50;
	int posY = positionBombe.y / 50;

	if (explosion == true) {
		if (tblIntMap[posY + 1][posX] == 1) {
			tblIntMap[posY + 1][posX] = 0;
		}
		else if (tblIntMap[posY - 1][posX] == 1) {
			tblIntMap[posY - 1][posX] = 0;
		}
		else if (tblIntMap[posY][posX + 1] == 1) {
			tblIntMap[posY][posX + 1] = 0;
		}
		else if (tblIntMap[posY][posX - 1] == 1) {
			tblIntMap[posY][posX - 1] = 0;
		}
	}
}