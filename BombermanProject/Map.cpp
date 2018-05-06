#include "Map.h"


Map::Map() //Constructeur
{
	positionImageX = 0;
	positionImageY = 0;
	valeurMap = 0;
	showTitle = true;
	map = "map1.txt";
	tabRectMap[13][15] = {};
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

void Map::jeuCommencer()
{
	showTitle = false;
}

void Map::ecranTitre(SDL_Surface* background)
{
	if (showTitle == true)
	{
		SDL_Rect posTitleScreen; //Rectangle contenant l'image titlescreen
		posTitleScreen.x = positionImageX;
		posTitleScreen.y = positionImageY;
		posTitleScreen.w = 750;
		posTitleScreen.h = 750;

		SDL_BlitSurface(titleScreen, NULL, background, &posTitleScreen); // Permet la génération du title screen

	}
}

void Map::genererMap()
{
	if (showTitle == false) // Si title est égale à true il reste sur l'écran titre
	{
		for (int i = 0; i < 13; i++) // Sert à faire afficher les blocs
		{
			for (int j = 0; j < 15; j++)
			{
				tabRectMap[i][j].x = j * 50;
				tabRectMap[i][j].y = i * 50;
				tabRectMap[i][j].w = 50;
				tabRectMap[i][j].h = 50;
			}
		}
	}
}

void Map::ouvrirFichier() //Ouvrir le fichier
{
	entree.open(map);
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

void Map::reinitialisation() //Réinitialise les valeurs de l'axe X et Y
{
	positionImageX = 0;
	positionImageY = 0;
}

bool Map::getShowTitle() //Renvoie la valeur de showTitle pour savoir si on démarre le jeu
{
	return showTitle;
}