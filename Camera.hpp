#pragma once
#include <optional>
#include <SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

struct Coords {
	double x_coord, y_coord;
};

class Camera {
public:
	Camera() {
		srcrect.x = 0;
		srcrect.y = 0;
		srcrect.w = SCREEN_WIDTH;
		srcrect.h = SCREEN_HEIGHT;
	}

	void Update(double player_x, double player_y) {
		srcrect.x = player_x - SCREEN_WIDTH / 2;
		srcrect.y = player_y - SCREEN_HEIGHT / 2;
	}
	
	SDL_Rect srcrect;
};
