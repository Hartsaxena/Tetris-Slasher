#pragma once

#include "Render.hpp" // For Rect


class MainMenu {
public:
	bool startPressed = false;
	bool exitPressed = false;

	MainMenu(int height = 1000, int width = 1000);
	~MainMenu();

	void click(int x, int y);

	// Accessors
	Rect getTitle() const { return this->title; }
	Rect getStartButton() const { return this->startButton; }
	Rect getExitButton() const { return this->exitButton; }

private:

	Rect startButton;
	Rect exitButton;
	Rect title;

	bool insideButton(Rect button, int x, int y);

};