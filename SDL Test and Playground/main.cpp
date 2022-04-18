#define SDL_MAIN_HANDLED
#include <iostream>
#include <list>
#include <algorithm>
#include "SDL.h"
#include "SDL_ttf.h"
#include "DeltaTime.h"
#include "FlyingGame.h"

// I was just testing drawing to the screen in SDL :)
///// <summary> 
///// Draws a chessboard
///// </summary>
///// <param name="ren"></param>
//void DrawBoard(SDL_Renderer* renderer) {
//	for (int i = 0; i < 8; i++) {
//		for (int j = 0; j < 8; j++) {
//
//			if ((j % 2 == 0 && i % 2 != 0) || (j % 2 != 0 && i % 2 == 0)) {
//				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//			}
//			else {
//				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
//			}
//
//			// Set up rectangle
//			SDL_Rect rect;
//
//			rect.x = j * 32;
//			rect.y = i * 32;
//			rect.w = 32;
//			rect.h = 32;
//
//			// Draw rectangle
//			SDL_RenderDrawRect(renderer, &rect);
//			SDL_RenderFillRect(renderer, &rect);
//		}
//	}
//
//	SDL_RenderPresent(renderer);
//}

void DrawBackground(SDL_Renderer* ren) {
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderClear(ren);
}

int main() {
	
	// Initialize components
	float frameRate = 6.9444f; // milliseconds per frame for a target framerate of 144 fps

	SDL_Window* window;	// Create window
	SDL_Renderer* ren; // Create renderer
	SDL_Event event{};	// Get SDL events 

	DeltaTime deltaTime;
	GameManager gameManager;
	SpawnManager spawnManager;

	Player testPlayer;
	std::list<Entity> entities;

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
	// Create font to write text on screen
	TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 25);


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

			// Spawn new objects
			if (entities.size() < 1) {
				spawnManager.SpawnEntity(window, &entities);
			}

			// Do physics
			deltaTime.UpdateDeltaTime();
			
			testPlayer.Update(deltaTime.Time);

			std::for_each(entities.begin(), entities.end(), [deltaTime, testPlayer](Entity& e) { e.Update(deltaTime.Time, testPlayer); });


			// Draw

			DrawBackground(ren);
			testPlayer.Draw(ren);

			std::for_each(entities.begin(), entities.end(), [ren](Entity& e) { e.Draw(ren); });

			gameManager.DrawGame(ren, font, window);

			// Remove entities off-screen
			entities.remove_if(SpawnManager::IsOffScreen);

			SDL_RenderPresent(ren); // Update screen
		}
		else if (gameManager.GameOver) {
			gameManager.DrawGameOver(ren, font, window); // Make sure game over screen gets drawn
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