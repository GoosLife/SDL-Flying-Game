#include "GameManager.h"
GameManager::GameManager() {
	spawnManager = SpawnManager();

	Score = 0;
	Time = 30;
}

GameManager::~GameManager() {}

void GameManager::AddScore(int scoreToAdd) {
	Score += scoreToAdd;
}

void GameManager::Update(float time)
{
	// Game is over if player touches the top or bottom of the screen
	if (Player->PlayerModel.y <= 0 || Player->PlayerModel.y >= 480 - 32) {
		GameOver = true;
	}

	// Spawn new objects
	spawnManager.SpawnEntity(Window, Entities);

	// Update player
	Player->Update(time);
	
	// Update entities
	std::list<Entity>::iterator e;
	for (e = Entities->begin(); e != Entities->end(); ++e) {
		e->Update(time, Player->PlayerCollider);

		if (e->EntityCollider.HasCollided(&Player->PlayerCollider) == true) {
			e->EntityModel.h = 0;
			e->EntityModel.w = 0;

			switch (e->Type) {
				// Clock
			case 0:
				AddTime(10);
				break;
				// Enemies
			case 1:
			case 2:
				GameOver = true;
				break;
				// Score object
			case 3:
				AddScore(100);
			}
		}
	}

	// Remove entities off-screen
	Entities->remove_if(Entity::IsOffScreen);
}

void GameManager::Draw()
{
	// Draw player
	Player->Draw(Renderer);

	// Draw entities
	std::list<Entity>::iterator e;
	for (e = Entities->begin(); e != Entities->end(); ++e) {
		e->Draw(Renderer);
	}

	// Draw game info etc.
	DrawGame();
}

void GameManager::AddTime(int timeToAdd) {
	Time += timeToAdd;
}

void GameManager::DrawGame() {

	SDL_Color white = { 255,255,255 }; // Set font color

	int windowWidth;
	SDL_GetWindowSize(Window, &windowWidth, NULL);

	// DRAW TIMER ON SCREEN
	std::string timerText = "Time: ";
	timerText += std::to_string(Time);
	char const* pTimeChar = timerText.c_str();

	SDL_Surface* gameInfoSurface;

	gameInfoSurface = TTF_RenderText_Solid(GameFont, pTimeChar, white); // Create surface

	SDL_Texture* gameInfoTexture = SDL_CreateTextureFromSurface(Renderer, gameInfoSurface);

	int timerW = 0;
	int timerH = 0;
	SDL_QueryTexture(gameInfoTexture, NULL, NULL, &timerW, &timerH);

	// Set timer position
	int timerX = windowWidth - timerW - 32;
	int timerY = 32;

	SDL_Rect dstRectTimer = { timerX,timerY,timerW,timerH };

	SDL_RenderCopy(Renderer, gameInfoTexture, NULL, &dstRectTimer);

	// DRAW SCORE ON SCREEN
	std::string scoreText = "Score: ";
	scoreText += std::to_string(Score);
	char const* pScoreChar = scoreText.c_str();

	SDL_Surface* scoreInfoSurface = TTF_RenderText_Solid(GameFont, pScoreChar, white);
	SDL_Texture* scoreInfoTexture = SDL_CreateTextureFromSurface(Renderer, scoreInfoSurface);

	int scoreW = 0;
	int scoreH = 0;
	SDL_QueryTexture(scoreInfoTexture, NULL, NULL, &scoreW, &scoreH);

	// Set score position
	int scoreX = windowWidth - scoreW - 32;
	int scoreY = 32 + scoreH;

	SDL_Rect dstRectScore = { scoreX, scoreY, scoreW, scoreH };
	
	SDL_RenderCopy(Renderer, scoreInfoTexture, NULL, &dstRectScore);

	SDL_FreeSurface(gameInfoSurface);
	SDL_FreeSurface(scoreInfoSurface);
	SDL_DestroyTexture(gameInfoTexture);
	SDL_DestroyTexture(scoreInfoTexture);
}

void GameManager::DrawGameOver()
{
	SDL_Color white = { 255,255,255 }; // Set font color

	int windowWidth;
	int windowHeight;
	SDL_GetWindowSize(Window, &windowWidth, &windowHeight);

	// DRAW GAME OVER TEXT
	SDL_Surface* gameInfoSurface = TTF_RenderText_Solid(GameFont, "Game Over", white);

	SDL_Texture* gameInfoTexture = SDL_CreateTextureFromSurface(Renderer, gameInfoSurface);

	int timerW = 0;
	int timerH = 0;
	SDL_QueryTexture(gameInfoTexture, NULL, NULL, &timerW, &timerH);

	// Set timer position
	int timerX = (windowWidth / 2) - (timerW / 2);
	int timerY = (windowHeight / 2) - (timerH / 2);

	SDL_Rect dstRectTimer = { timerX,timerY,timerW,timerH };

	SDL_RenderCopy(Renderer, gameInfoTexture, NULL, &dstRectTimer);

	// DRAW SCORE ON SCREEN
	std::string scoreText = "Score: ";
	scoreText += std::to_string(Score);
	char const* pScoreChar = scoreText.c_str();

	SDL_Surface* scoreInfoSurface = TTF_RenderText_Solid(GameFont, pScoreChar, white);
	SDL_Texture* scoreInfoTexture = SDL_CreateTextureFromSurface(Renderer, scoreInfoSurface);

	int scoreW = 0;
	int scoreH = 0;
	SDL_QueryTexture(scoreInfoTexture, NULL, NULL, &scoreW, &scoreH);

	// Set score position
	int scoreX = windowWidth - scoreW - 32;
	int scoreY = 32 + scoreH;

	SDL_Rect dstRectScore = { scoreX, scoreY, scoreW, scoreH };

	SDL_RenderCopy(Renderer, scoreInfoTexture, NULL, &dstRectScore);
	
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