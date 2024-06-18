#pragma once

#include <optional>

#include <string>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include "Camera.hpp"
#include "Direction.hpp"


class Player {
public:
	void Render(SDL_Renderer* renderer, double x, double y) {
		SDL_Rect rect = { x, y, 30, 30 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &rect);
	}

	void RenderStatic(SDL_Renderer* renderer) {
		SDL_Rect rect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 30, 30 };
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(renderer, &rect);
	}

	void Move(Direction dir, double speed = 0.2) {
		switch (dir) {
		case (Direction::up):
			pos.y_coord -= speed;
			// printf("Player moved up\n");
			break;
		case (Direction::down):
			pos.y_coord += speed;
			// printf("Player moved down\n");
			break;
		case (Direction::left):
			pos.x_coord -= speed;
			// printf("Player moved left\n");
			break;
		case (Direction::right):
			pos.x_coord += speed;
			// printf("Player moved right\n");
			break;
		case (Direction::up_right):
			pos.x_coord += speed/sqrt(2);
			pos.y_coord -= speed/sqrt(2);
			// printf("Player moved up right\n");
			break;
		case (Direction::up_left):
			pos.x_coord -= speed / sqrt(2);
			pos.y_coord -= speed / sqrt(2);
			// printf("Player moved up left\n");
			break;
		case (Direction::down_left):
			pos.x_coord -= speed / sqrt(2);
			pos.y_coord += speed / sqrt(2);
			// printf("Player moved up left\n");
			break;
		case (Direction::down_right):
			pos.x_coord += speed / sqrt(2);
			pos.y_coord += speed / sqrt(2);
			// printf("Player moved down right\n");
			break;
		}
		camera.Update(pos.x_coord, pos.y_coord);
		// std::cout << "x: " << pos.x_coord << " " << "y: " << pos.y_coord << "\n";
	}


	std::optional<Direction> CheckCollision() {
		if (pos.x_coord <= SCREEN_WIDTH / 2) {
			if (pos.y_coord <= SCREEN_HEIGHT / 2) {
				//printf("Up left collision\n");
				return Direction::up_left;
			}
			else if (pos.y_coord >= 1280 - SCREEN_HEIGHT / 2) {
				//printf("Down left collision\n");
				return Direction::down_left;
			}
			else {
				//printf("Left collision\n");
				return Direction::left;
			}
		}
		else if (pos.x_coord >= 2048 - SCREEN_WIDTH / 2) {
			if (pos.y_coord <= SCREEN_HEIGHT / 2) {
				// printf("Up right collision\n");
				return Direction::up_right;
			}
			else if (pos.y_coord >= 1280 - SCREEN_HEIGHT / 2) {
				// printf("Down right collision\n");
				return Direction::down_right;
			}
			else {
				// printf("Right collision\n");
				return Direction::right;
			}
		}
		else if (pos.y_coord <= SCREEN_HEIGHT / 2) {
			// printf("Up collision\n");
			return Direction::up;
		}
		else if (pos.y_coord >= 1280 - SCREEN_HEIGHT / 2) {
			//printf("Down collision\n");
			return Direction::down;
		}

		return std::nullopt;
	}

	Camera camera;
	Coords pos = { 0, 0 };
};