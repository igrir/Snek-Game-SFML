#pragma once
#include <iostream>
#include <map>

class Screen;

class ScreenManager
{
public:
	ScreenManager();
	~ScreenManager();

	Screen* currentScreen;
	std::map<std::string, Screen*> Screens;

	void switchScene(std::string sceneId);

};

