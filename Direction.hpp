#pragma once

#include <string>

enum class Direction {
	up, down, right, left, up_right, up_left, down_right, down_left
};

std::string GetDirName(Direction dir) {
	switch (dir) {
	case Direction::up:
		return "up";
	case Direction::down:
		return "down";
	case Direction::right:
		return "right";
	case Direction::left:
		return "left";
	case Direction::up_right:
		return "up_right";
	case Direction::up_left:
		return "up_left";
	case Direction::down_right:
		return "down_right";
	case Direction::down_left:
		return "down_left";
	}
}