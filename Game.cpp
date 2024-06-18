//#include "Game.hpp"
//#include <SDL_image.h>
//#include "Perlin.hpp"
//#include "Direction.hpp"
//#include <cmath>
//#include <SDL.h>
//// Initialize game
//
//
//Game::Game() {
//	if (InitGame()) {
//		printf("Failed to initialize! Error: %d\n", InitGame());
//	} 
//	else {
//		if (LoadMedia()) {
//			printf("Failed to load media!\n");
//		}
//	}
//}
//
//// To-do: USE EXCEPTIONS HERE
//
//int Game::InitGame() {
//	// Initialize SDL
//	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//		printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
//		return 1;
//	}
//	else {
//		//Set texture filtering to linear
//		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
//			printf("Warning: Linear texture filtering not enabled!");
//		}
//
//		// Create window
//		window = SDL_CreateWindow("FarmUltimate", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//		
//
//		// screenSurface = SDL_GetWindowSurface(window);
//
//		if (window == NULL) {
//			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
//			return 2;
//		}
//		else
//		{
//			// Create renderer
//			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//			if (renderer == NULL)
//			{
//				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
//				return 3;
//			}
//
//			else
//			{
//				//Initialize renderer color
//				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//
//				//Initialize PNG loading
//				int imgFlags = IMG_INIT_PNG;
//				if (!(IMG_Init(imgFlags) & imgFlags))
//				{
//					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
//					return 4;
//				}
//			}
//		}
//
//		SDL_PixelFormat* formatPix = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
//
//		SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);
//
//		int xOrg = 100000;
//		int yOrg = 100000;
//		float freq = 0.4f;
//		int depth = 10;
//		int scale = 10;
//
//		Uint32* pixels = new Uint32[WIN_WIDTH * WIN_HEIGHT]; // Allocate pixels array on the heap
//
//		for (int y = 0; y < WIN_HEIGHT; y++) {
//			for (int x = 0; x < WIN_WIDTH; x++) {
//				float xCoord = xOrg + x / ((float)WIN_WIDTH) * scale;
//				float yCoord = yOrg + y / ((float)WIN_HEIGHT) * scale;
//				float value1 = perlin2d(yCoord, xCoord, freq, depth, 12);
//				SDL_Color col = pickColor((int)(value1 * 16) % 7);
//				pixels[y * WIN_WIDTH + x] = SDL_MapRGBA(formatPix, col.r, col.g, col.b, 255);
//			}
//		}
//
//		SDL_UpdateTexture(texture, NULL, pixels, sizeof(Uint32) * WIN_WIDTH);
//		SDL_FreeFormat(formatPix);
//
//	}
//	return 0;
//}
//
//
//int Game::LoadMedia() {
//	//Load PNG texture
//	texture = LoadTexture("images/forest.jpg");
//	if (texture == NULL)
//	{
//		printf("Failed to load texture image!\n");
//		return 1;
//	}
//	return 0;
//}
//
//void Game::Close() {
//	//Free loaded image
//	SDL_DestroyTexture(texture);
//	texture = NULL;
//
//	//Destroy window	
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	window = NULL;
//	renderer = NULL;
//
//	//Quit SDL subsystems
//	IMG_Quit();
//	SDL_Quit();
//}
//
//
//SDL_Texture* Game::LoadTexture(std::string path) {
//	//The final texture
//	SDL_Texture* newTexture = NULL;
//
//	//Load image at specified path
//	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//	if (loadedSurface == NULL)
//	{
//		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//	}
//	else
//	{
//		//Create texture from surface pixels
//		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
//		if (newTexture == NULL)
//		{
//			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//		}
//
//		//Get rid of old loaded surface
//		SDL_FreeSurface(loadedSurface);
//	}
//
//	return newTexture;
//}
//
//void Game::Clear(SDL_Renderer* render) {
//	SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
//	SDL_RenderClear(render);
//}
//
//std::optional<Direction> Game::HandleMovementDir(const Uint8* keyboardState) {
//	if (keyboardState[SDL_SCANCODE_W]) {
//		if (keyboardState[SDL_SCANCODE_D])
//			return Direction::up_right;
//		else if (keyboardState[SDL_SCANCODE_A])
//			return Direction::up_left;
//		else
//			return Direction::up;
//	}
//	else if (keyboardState[SDL_SCANCODE_S]) {
//		if (keyboardState[SDL_SCANCODE_D])
//			return Direction::down_right;
//		else if (keyboardState[SDL_SCANCODE_A])
//			return Direction::down_left;
//		else
//			return Direction::down;
//	}
//	else if (keyboardState[SDL_SCANCODE_D])
//		return Direction::right;
//	else if (keyboardState[SDL_SCANCODE_A])
//		return Direction::left;
//
//	return std::nullopt;
//}
//
//const Uint8* keyboardState;
//
//void Game::Start() {
//	
//	Player p;
//	Camera c;
//
//	while (!quit) {
//		SDL_Event e;
//		SDL_PollEvent(&e);  // Poll events to prevent queue from getting full
//
//		const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
//
//		std::optional<Direction> movementDir, collisionDir = std::nullopt;
//
//		if (keyboardState[SDL_SCANCODE_W]) {
//			if (keyboardState[SDL_SCANCODE_D])
//				movementDir = Direction::up_right;
//			else if (keyboardState[SDL_SCANCODE_A])
//				movementDir = Direction::up_left;
//			else
//				movementDir = Direction::up;
//		}
//		else if (keyboardState[SDL_SCANCODE_S]) {
//			if (keyboardState[SDL_SCANCODE_D])
//				movementDir = Direction::down_right;
//			else if (keyboardState[SDL_SCANCODE_A])
//				movementDir = Direction::down_left;
//			else
//				movementDir = Direction::down;
//		}
//		else if (keyboardState[SDL_SCANCODE_D]) {
//			movementDir = Direction::right;
//		}
//		else if (keyboardState[SDL_SCANCODE_A]) {
//			movementDir = Direction::left;
//		}
//
//		if (movementDir.has_value()) {
//			// printf("x: %f, y: %f\n", p.pos.x_coord, p.pos.y_coord);
//			collisionDir = p.CheckCollision();
//			p.Move(movementDir.value());
//		}
//
//		if (e.type == SDL_QUIT) {
//			quit = true;
//		}
//
//
//
//		Clear(renderer);
//
//
//		SDL_Rect dstrect;
//
//		dstrect.x = 0;
//		dstrect.y = 0;
//		dstrect.w = SCREEN_WIDTH;
//		dstrect.h = SCREEN_HEIGHT;
//
//		collisionDir = p.CheckCollision();
//
//		// Hideous code, rewrite
//
//		SDL_RenderCopy(renderer, texture, &p.camera.srcrect, &dstrect);
//		p.Render(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
//		SDL_RenderPresent(renderer);
//	}
//	Close();
//}