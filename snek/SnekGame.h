#pragma once

#ifndef SNEK_GAME_H
#define SNEK_GAME_H

#include <iostream>
#include <vector>
#include <queue>
#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "ScreenManager.h"

class MainMenuScreen;
class GameScreen;

using namespace sf;

class SnekGame {
public:
	SnekGame();

	void Init();
	void Update();
	void UpdateInput();
	void Draw();
	void Start();

	bool running = true;

private:
	

	RenderWindow *window;

	

	Font font;
	Text text;

	int appleCountdown;

	

	void updatePlay();
	void updateMenu();


	MainMenuScreen *mainMenuScreen;
	GameScreen *gameScreen;

	ScreenManager screenManager;

};

#endif // !SNEK_GAME_H


