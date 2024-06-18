#pragma once
#include "Player.hpp"
#include <string>


// make Singleton

class Game {
public:
	Game();
	void Start();
	void Close();
	std::optional<Direction> HandleMovementDir(const Uint8* keyboardState);
private:
	int InitGame();
	void Clear(SDL_Renderer* render);
	int LoadMedia();
	SDL_Texture* LoadTexture(std::string path);

	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	//Current displayed texture
	SDL_Texture* texture;
	
	bool quit = false;
};