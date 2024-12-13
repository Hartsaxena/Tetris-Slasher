#include "Menu.hpp"
#include <SDL.h>
#include "Colors.hpp"


MainMenu::MainMenu(int height, int width) : startPressed(false), exitPressed(false) {
    int centerX = width / 2;
    int centerY = height / 2;
	SDL_Rect titleRect = { centerX, centerY - 200, 200, 50 };
	SDL_Rect startRect = { centerX, centerY, 200, 50 };
	SDL_Rect exitRect = { centerX, centerY + 100, 200, 50 };
	this->title = { titleRect, TRANSPARENT};
	this->startButton = { startRect, TRANSPARENT };
	this->exitButton = { exitRect, TRANSPARENT };
}

MainMenu::~MainMenu() {}

void MainMenu::click(int x, int y) {
	bool start = insideButton(this->startButton, x, y);
	bool exit = insideButton(this->exitButton, x, y);
	if (start) {
		this->startPressed = true;
	}
	else if (exit) {
		this->exitPressed = true;
	}
}

bool MainMenu::insideButton(Rect button, int x, int y) {
	return x > button.x && x < button.x + button.w && y > button.y && y < button.y + button.h;
}