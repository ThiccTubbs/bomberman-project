#include "Bomb.h"

Bombe::Bombe() //Constructeur de la bombe
{
	nbBombeEnJeu = 0;
	nbBombeInventaire = 1;
	showBombe = false;
	showExplosion = false;
	explosionEnCours = false;

	bombe = SDL_LoadBMP("bombe.bmp");
	explosion = SDL_LoadBMP("explosion.bmp");

	bombeSpriteX = 0;
	bombeSpriteY = 0;
	explosionSpriteX = 0;
	explosionSpriteY = 0;

	frameBombe = 0;
	frameExplosion = 0;

	faireBombe();	//Faire la sprite sheet des bombes
	faireExplosion(); //Faire la sprite sheet des explosions

}

Bombe::~Bombe() //Déconstructeur
{
	SDL_FreeSurface(bombe);
	SDL_FreeSurface(explosion);
}

void Bombe::faireBombe() //Faire le sprite de la bombe
{
	int j = 0,	//Compteur de la boucle
		x = 0,	//Posiiton colonne sprite
		y = 0;	//Position ligne sprite

	for (int i = 0; i < 1; i++) //Ligne
	{
		for (j = 0; j < 3; j++) //Colonne
		{
			bombeSprite[i][j].x = x;
			bombeSprite[i][j].y = y;
			bombeSprite[i][j].h = 50;
			bombeSprite[i][j].w = 49;

			x += 50; //Change de colonne
		}

	}
}

void Bombe::faireExplosion() //Faire le sprite de l'explosion
{
	int j = 0,	//Compteur de la deuxième boucle
		x = 0,	//Position colonne
		y = 0;	//Position ligne

	for (int i = 0; i < 7; i++) //Ligne
	{
		for (j = 0; j < 4; j++) //Colonne
		{
			explosionSprite[i][j].x = x;
			explosionSprite[i][j].y = y;
			explosionSprite[i][j].h = 32;
			explosionSprite[i][j].w = 32;

			x += 32; //Change de colonne
		}
		y += 32; //Change de ligne
	}
}

void Bombe::animerBombe(float &timeFrame) //Animation de la bombe
{
	if (timeFrame > 100 && showBombe == true)//Si une seconde est passé
	{
		timeFrame = 0;	//Remettre le timeFrame a 0 pour attendre une nouvelle seconde
		bombeSpriteY++; //Augmenter la position dans le tableau de sprite
		frameBombe++;

		if (bombeSpriteY == 3) //Si on a atteint le maximum de sprite la bombe a explosé
		{
			completeAnimation++;
			bombeSpriteY = 0; //Réinitialise l'image de la bombe au premier sprite

			if (completeAnimation == 10) //Si 10 animations ont été completés
			{
				showBombe = false;		//On ne montre plus la bombe
				completeAnimation = 0;	//Réinitialise le nombre d'animations à 0
				showExplosion = true;  //La bombe explose
				nbBombeEnJeu -= 1;	//Avoir la bombe a nouveau
			}

		}
	}
}

bool Bombe::montrerBombe() //On vérifie s'il est possible de poser une bombe
{
	if (nbBombeEnJeu < nbBombeInventaire)
	{
		return true;
	}

	return false;
}

void Bombe::poserBombe() //On pose une bombe
{
	showBombe = true;
	nbBombeEnJeu += 1;
	explosionEnCours = true;
}

void Bombe::initializePosBombe(int posBonhommeX, int posBonhommeY)//Donner la position de la bombe
{
	if (nbBombeEnJeu < nbBombeInventaire)
	{
		posBombe.h = 100;
		posBombe.w = 100;
		posBombe.x = posBonhommeX - 10;
		posBombe.y = posBonhommeY - 10;
	}

}

void Bombe::initializePosExplosion() //Position fixe de l'explosion
{
	posExplosion.h = 100;
	posExplosion.w = 100;

	if (explosionEnCours == false)
	{
		posExplosion.x = posBombe.x + 10;
		posExplosion.y = posBombe.y + 10;
	}

}

void Bombe::animerExplosion(float timeFrame, SDL_Surface* background) //L'animation de l'explosion
{

	if (showExplosion == true)
	{
		if (timeFrame < 1000)
		{
			SDL_BlitSurface(explosion, &explosionSprite[0][0], background, &posExplosion); //Le centre de l'explosion

			posExplosion.x += 32;

			SDL_BlitSurface(explosion, &explosionSprite[0][5], background, &posExplosion); //L'explosion vers la droite

			posExplosion.x -= 32;
			posExplosion.y -= 32;

			SDL_BlitSurface(explosion, &explosionSprite[0][3], background, &posExplosion); //L'explosion vers le haut

			posExplosion.y += 32;
			posExplosion.x -= 32;

			SDL_BlitSurface(explosion, &explosionSprite[0][6], background, &posExplosion); //L'explosion vers la gauche

			posExplosion.y += 32;
			posExplosion.x += 32;

			SDL_BlitSurface(explosion, &explosionSprite[0][4], background, &posExplosion); //L'explosion vers le bas

			posExplosion.y -= 32;

		}
		else
		{
			showExplosion = false;
			explosionEnCours = false;
		}

		//NOTE: LE RECTANGLE DE LA BOMBE DOIT ETRE REPOSITIONER A LA POSITION DU BOMBER MAN
	}
}

void Bombe::faireApparaitreBombe(SDL_Surface* background) //Faire apparaitre la bombe sur la surface
{
	if (showBombe == true) //Si on peut montrer la bombe et si on peut montrer le sprite sans produire un rectangle invisible
	{
		SDL_BlitSurface(bombe, &bombeSprite[bombeSpriteX][bombeSpriteY], background, &posBombe); //Faire apparaitre la bombe si on peut la montrer
	}
}