#include "GameManager.h"
GameManager::GameManager() {
	Score = 0;
	Time = 30;
}

GameManager::~GameManager() {}

void GameManager::AddScore(int scoreToAdd) {
	Score += scoreToAdd;
}

void GameManager::AddTime(int timeToAdd) {
	Time += timeToAdd;
}

void GameManager::DrawGame(SDL_Renderer* ren, TTF_Font* font, SDL_Window* window) {

	SDL_Color white = { 255,255,255 }; // Set font color

	int windowWidth;
	SDL_GetWindowSize(window, &windowWidth, NULL);

	// DRAW TIMER ON SCREEN
	std::string timerText = "Time: ";
	timerText += std::to_string(Time);
	char const* pTimeChar = timerText.c_str();

	SDL_Surface* gameInfoSurface;

	gameInfoSurface = TTF_RenderText_Solid(font, pTimeChar, white); // Create surface

	SDL_Texture* gameInfoTexture = SDL_CreateTextureFromSurface(ren, gameInfoSurface);

	int timerW = 0;
	int timerH = 0;
	SDL_QueryTexture(gameInfoTexture, NULL, NULL, &timerW, &timerH);

	// Set timer position
	int timerX = windowWidth - timerW - 32;
	int timerY = 32;

	SDL_Rect dstRectTimer = { timerX,timerY,timerW,timerH };

	SDL_RenderCopy(ren, gameInfoTexture, NULL, &dstRectTimer);

	// DRAW SCORE ON SCREEN
	std::string scoreText = "Score: ";
	scoreText += std::to_string(Score);
	char const* pScoreChar = scoreText.c_str();

	SDL_Surface* scoreInfoSurface = TTF_RenderText_Solid(font, pScoreChar, white);
	SDL_Texture* scoreInfoTexture = SDL_CreateTextureFromSurface(ren, scoreInfoSurface);

	int scoreW = 0;
	int scoreH = 0;
	SDL_QueryTexture(scoreInfoTexture, NULL, NULL, &scoreW, &scoreH);

	// Set score position
	int scoreX = windowWidth - scoreW - 32;
	int scoreY = 32 + scoreH;

	SDL_Rect dstRectScore = { scoreX, scoreY, scoreW, scoreH };
	
	SDL_RenderCopy(ren, scoreInfoTexture, NULL, &dstRectScore);

	SDL_FreeSurface(gameInfoSurface);
	SDL_FreeSurface(scoreInfoSurface);
	SDL_DestroyTexture(gameInfoTexture);
	SDL_DestroyTexture(scoreInfoTexture);
}

void GameManager::DrawGameOver(SDL_Renderer* ren, TTF_Font* font, SDL_Window* window)
{
	SDL_Color white = { 255,255,255 }; // Set font color

	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	// DRAW GAME OVER TEXT
	SDL_Surface* gameInfoSurface = TTF_RenderText_Solid(font, "Game Over", white);

	SDL_Texture* gameInfoTexture = SDL_CreateTextureFromSurface(ren, gameInfoSurface);

	int timerW = 0;
	int timerH = 0;
	SDL_QueryTexture(gameInfoTexture, NULL, NULL, &timerW, &timerH);

	// Set timer position
	int timerX = (windowWidth / 2) - (timerW / 2);
	int timerY = (windowHeight / 2) - (timerH / 2);

	SDL_Rect dstRectTimer = { timerX,timerY,timerW,timerH };

	SDL_RenderCopy(ren, gameInfoTexture, NULL, &dstRectTimer);

	// DRAW SCORE ON SCREEN
	std::string scoreText = "Score: ";
	scoreText += std::to_string(Score);
	char const* pScoreChar = scoreText.c_str();

	SDL_Surface* scoreInfoSurface = TTF_RenderText_Solid(font, pScoreChar, white);
	SDL_Texture* scoreInfoTexture = SDL_CreateTextureFromSurface(ren, scoreInfoSurface);

	int scoreW = 0;
	int scoreH = 0;
	SDL_QueryTexture(scoreInfoTexture, NULL, NULL, &scoreW, &scoreH);

	// Set score position
	int scoreX = windowWidth - scoreW - 32;
	int scoreY = 32 + scoreH;

	SDL_Rect dstRectScore = { scoreX, scoreY, scoreW, scoreH };

	SDL_RenderCopy(ren, scoreInfoTexture, NULL, &dstRectScore);
	
	SDL_FreeSurface(gameInfoSurface);
	SDL_FreeSurface(scoreInfoSurface);
	SDL_DestroyTexture(gameInfoTexture);
	SDL_DestroyTexture(scoreInfoTexture);
}

Uint32 GameManager::ReduceTime(Uint32 interval, void* param) {
	GameManager* g = static_cast<GameManager* >(param);

	g->Time -= 1;

	if (g->Time == 0) {
		g->GameOver = true;
	}

	return interval;
}