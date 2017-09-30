#include "ScreenManager.h"
#include "Screen.h"


ScreenManager::ScreenManager()
{
}


ScreenManager::~ScreenManager()
{
}

void ScreenManager::switchScene(std::string sceneName) {
	currentScreen = Screens.find(sceneName)->second;
	currentScreen->Start();
}