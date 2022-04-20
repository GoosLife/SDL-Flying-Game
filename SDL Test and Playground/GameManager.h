#pragma once
#include <algorithm>
#include <list>
#include <SDL.h>
#include <SDL_ttf.h>
#include <sstream>
#include <string.h>
#include <vector>

#include "DeltaTime.h"
#include "Entity.h"
#include "Player.h"
#include "SpawnManager.h"

class GameManager
{
private:
	SpawnManager spawnManager;

public:
	GameManager();
	~GameManager();

	SDL_Renderer* Renderer;
	SDL_Window* Window;
	TTF_Font* GameFont;

	Player* Player;
	std::list<Entity>* Entities;


	bool GameOver = false;

	int Score;
	int Time;

	void AddTime(int timeToAdd);
	void AddScore(int scoreToAdd);

	void Update(float time);
	void Draw();

	void DrawGame();
	void DrawGameOver();

	
	static Uint32 ReduceTime(Uint32 interval, void* param);
};