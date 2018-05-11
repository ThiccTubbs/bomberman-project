#include "Game.h"

Game::Game(SDL_Window* w, SDL_Surface* b) : bomb(new Bomb()), map(new Map()), bomberman(new Bomberman(w))
{
	window = w;
	background = b;
	gameOver = false;

	lastTime = 0.0f; // L'ancien temps obtenu
	lastTimeBomberman = 0.0f;
	currentTime = 0.0f; // Le temps actuel obtenu avec SDL_GetTicks()
	timeFrame = 0.0f; // Le nombre de secondes attendues	
	deltaTime = 0.0f; // La différence de temps entre lastTime et currentTime
}

void Game::start() {

	map->ouvrirFichier();	// Ouvrir le fichier dans lequel on veut lire

	map->lireFichier();	// Lire dans le fichier

	while (gameOver == false) {

		// Nettoyer l'écran
		SDL_FillRect(background, NULL, SDL_MapRGB(background->format, 50, 205, 50));

		currentTime = SDL_GetTicks(); // Obtenir le temps courant

		deltaTime = currentTime - lastTime; // Obtenir la différence de temps entre le dernier temps pris en compte et le temps actuel

		timeFrame += deltaTime; // Le temps entre l'ancien et le nouveau temps courant  

		SDL_Event evenement; // Lire les événements

		SDL_PumpEvents();
		const Uint8 * keys = SDL_GetKeyboardState(NULL);

		// Contient les événements
		while (SDL_PollEvent(&evenement) != 0)
		{
			if (evenement.type == SDL_QUIT || evenement.key.keysym.sym == SDLK_ESCAPE)
			{
				gameOver = true; // Le joueur veut quitter
			}
			if (evenement.type == SDL_KEYDOWN) // Quand le spacebar est down
			{
				if (evenement.key.keysym.sym == SDLK_SPACE)
				{
					if (bomb->montrerBombe()) // Est-ce qu'on montre la bombe
					{
						bomb->poserBombe();	// On pose la bombe
					}
				}
			}
		}

		map->generateMap(background); // Générer la map

		bomberman->changeDirection(keys, background, map->tblRectMap, map->tblIntMap); // Changement de position du bonhomme

		bomberman->walk(lastTimeBomberman, background); // Faire marcher le bonhomme

		bomb->initializePosBombe(bomberman->getDestination()); // Initialiser la position de la bombe à la position du personnage 

		bomb->initializePosExplosion(); // Initialiser la position de la bombe a la position du personnage

		bomb->animerBombe(timeFrame); // Animer la bombe

		bomb->animerExplosion(timeFrame, background); // Animer l'explosion

		map->destroyWalls(bomb->getPositionBomb(), bomb->getExplosion());

		bomb->faireApparaitreBombe(background);

		map->reinitialisation();

		lastTime = currentTime; // Devient le temps actuel avant d'en obtenir un nouveau

								// Mettre à jour la surface 
		SDL_UpdateWindowSurface(window);
	}
}


Game::~Game()
{
}
