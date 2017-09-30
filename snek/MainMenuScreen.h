#pragma once
#ifndef _MAIN_MENU_SCREEN_H
#define _MAIN_MENU_SCREEN_H

#include "Screen.h"
#include "ScreenManager.h"
using namespace sf;

class SnekGame;

class MainMenuScreen : public Screen
{
public:

	const static std::string ID;

	MainMenuScreen(SnekGame *game, ScreenManager *manager);

	void Start() override;
	void Update() override;
	void InputUpdate(Event &e) override;
	void Draw(RenderWindow &window) override;
	void End() override;

	Font font;
	Text textCredit;

	Text textTitle;
	Text textHelp;
private:
	SnekGame* game;
	ScreenManager* manager;
};

#endif // !_MAIN_MENU_SCREEN_H
