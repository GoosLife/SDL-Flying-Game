#define SDL_MAIN_HANDLED
#include <algorithm>
#include <list>
#include "SDL.h"
#include "SDL_ttf.h"
#include "DeltaTime.h"
#include "FlyingGame.h"

void DrawBackground(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, 135, 206, 235, 255);
	SDL_RenderClear(ren);
}

int main() {
	
	// Initialize components
	float frameRate = 6.9444f; // milliseconds per frame for a target framerate of 144 fps

	SDL_Window* window;	// Create window
	SDL_Renderer* ren; // Create renderer
	SDL_Event event{};	// Get SDL events 

	Player testPlayer;
	std::list<Entity> entities;

	DeltaTime deltaTime;
	GameManager gameManager;
	SpawnManager spawnManager;

	gameManager.Player = &testPlayer;
	gameManager.Entities = &entities;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // If SDL couldn't be initialized
		SDL_Log("Unable to initialize SDL."); 
		return 1; // Exit program
	}
	// Initialize TTF
	TTF_Init();

	// DO SDL STUFF HERE

	// Create window
	SDL_CreateWindowAndRenderer(640, 480, NULL, &window, &ren);

	// Add window and renderer to game manager
	gameManager.Window = window;
	gameManager.Renderer = ren;

	// Create font to write text on screen
	gameManager.GameFont = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 25);


	// Initialize objects
	testPlayer.Init(ren);

	SDL_TimerID timeLeft = SDL_AddTimer(1000, &GameManager::ReduceTime, &gameManager);

	while (!(event.type == SDL_QUIT)) {
		Uint64 start = SDL_GetPerformanceCounter();

		if (!gameManager.GameOver) {

			SDL_PollEvent(&event); // Get events

			// Get input
			if (event.type == SDL_KEYDOWN) {
				testPlayer.Fly(deltaTime.Time);
			}

			// Do physics
			deltaTime.UpdateDeltaTime();
			
			// Update game objects
			gameManager.Update(deltaTime.Time);

			// Draw

			DrawBackground(ren);
			gameManager.Draw();

			// Update screen
			SDL_RenderPresent(ren);
		}
		else if (gameManager.GameOver) {
			gameManager.DrawGameOver(); // Make sure game over screen gets drawn
			SDL_RenderPresent(ren); // Update screen
			SDL_PollEvent(&event); // Get events
		}

		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

		// Cap to 60 fps
		if (frameRate - elapsedMS > 0) {
			SDL_Delay(floor(frameRate - elapsedMS));
		}

	}

	// Exit program
	TTF_Quit();
	SDL_Quit();
	return 0;
}