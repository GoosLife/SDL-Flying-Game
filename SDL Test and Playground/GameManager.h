#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string.h>

class GameManager
{
private:

public:
	GameManager();
	~GameManager();

	bool GameOver = false;

	int Score;
	int Time;

	void AddTime(int timeToAdd);
	void AddScore(int scoreToAdd);

	void DrawGame(SDL_Renderer* ren, TTF_Font* font, SDL_Window* window);
	void DrawGameOver(SDL_Renderer* ren, TTF_Font* font, SDL_Window* window);

	
	static Uint32 ReduceTime(Uint32 interval, void* param);
};