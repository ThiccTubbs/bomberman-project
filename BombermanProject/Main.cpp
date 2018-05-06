// Bomber_Man.cpp : définit le point d'entrée pour l'application console.
/*Nom:Karl Boutin
But du programme: Programmer la bombe pour le projet d'équipe sur le jeu Bomber Man
*/

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_timer.h>
#include "Bomberman.h"
#include "Bomb.h"
#include "Map.h"

using namespace std;

int main(int argc, char* argv[])
{
	Bombe		bomb;					//Création d'une bombe

	Map			map;					//Création de la map

	SDL_Window* window = NULL;			//Fenêtre

	SDL_Surface* background = NULL;		//Arrière-plan

	const int	LARGEUR = 1366;			//Largeur de l'écran
	const int	HAUTEUR = 768;			//Hauteur de l'écran

	float		lastTime = 0,			//L'ancien temps obtenu
		currentTime = 0,		//Le temps actuel obtenu avec SDL_GetTicks()
		timeFrame = 0,			//Le nombre de seconde attendu		
		deltaTime = 0;			//La différence de temps entre lastTime et currentTime

	int			tempsBonhomme = 0;		//Temps personnage pour le mouvement

	bool		gameOver = false;		//Partie terminé

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		cout << "Erreur lors de l'initialisation de la SDL", SDL_GetError(); //S'il y a une erreur
		exit(EXIT_FAILURE);
	}

	//Créer la fenêtre
	window = SDL_CreateWindow("BomberMan", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR, HAUTEUR, SDL_WINDOW_SHOWN);

	//Obtenir la surface de la fenêtre
	background = SDL_GetWindowSurface(window);

	Bomberman   bonhomme(window); //Création du personnage BomberMan

	map.ouvrirFichier();	//Ouvrir le fichier dans lequel on veut lire

	map.lireFichier();	//Lire dans le fichier

	while (gameOver == false)
	{
		//Nettoyer l'écran
		SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 50, 205, 50));


		currentTime = SDL_GetTicks(); //Obtiens le temps courant

		deltaTime = currentTime - lastTime; //Obtenir la différence de temps entre le dernier temps pris en compte et le temps actuel

		cout << timeFrame << endl;

		timeFrame += deltaTime; //Le temps entre l'ancien et le nouveau temps courant  
								//Savoir combien  de temps a passé

								//Lire les événements
		SDL_Event evenement;

		SDL_PumpEvents();
		const Uint8 * keys = SDL_GetKeyboardState(NULL);

		//Contient les événements
		while (SDL_PollEvent(&evenement) != 0)
		{
			if (evenement.type == SDL_QUIT)
			{
				gameOver = true; //Le joueur veut quitter
			}
			if (evenement.type == SDL_KEYDOWN) //Quand le spacebar est down
			{
				if (evenement.key.keysym.sym == SDLK_SPACE)
				{
					if (bomb.montrerBombe()) //Est-ce qu'on montre la bombe
					{
						bomb.poserBombe();	//On pose la bombe
					}
				}

				if (evenement.key.keysym.sym == SDLK_ESCAPE)
				{
					map.jeuCommencer();
				}

			}
		}

		map.ecranTitre(background); //Affiche l'ecran titre s'il doit etre afficher

		if (map.getShowTitle() == false)
		{
			map.genererMap(); //Générer la map

			bonhomme.changeDirection(keys, lastTime, background); //Changer la direction du bonhomme

			bonhomme.walk(tempsBonhomme, background); //Faire marcher le bonhomme

			bomb.initializePosBombe(bonhomme.getPositionX(), bonhomme.getPositionY()); //Initialize la position de la bombe à la position du personnage 

			bomb.initializePosExplosion(); //Initialize la position de la bombe a la position du personnage

			bomb.animerBombe(timeFrame); //Animer la bombe

			bomb.animerExplosion(timeFrame, background); //Animer l'explosion

			bomb.faireApparaitreBombe(background); //Faire apparaitre la bombe

			map.reinitialisation();
		}


		lastTime = currentTime;//Devient le temps actuel avant d'en obtenir un nouveau

							   //Mettre à jour la surface 
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window); //Détruire la fenêtre

	SDL_Quit(); //Arrêt de la SDL (libération de la mémoire)

	return EXIT_SUCCESS;
}

