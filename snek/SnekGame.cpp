#include <SFML\Graphics.hpp>
#include "SnekGame.h"
#include <iostream>
#include <vector>
#include <random>
#include "ariblkfont.h"
#include "MainMenuScreen.h"
#include "GameScreen.h"


SnekGame::SnekGame()
{
	mainMenuScreen = new MainMenuScreen(this, &screenManager);
	gameScreen = new GameScreen(this, &screenManager);

	screenManager.Screens.insert(std::pair<std::string, Screen*>(MainMenuScreen::ID, dynamic_cast<Screen *>(mainMenuScreen)));
	screenManager.Screens.insert(std::pair<std::string, Screen*>(GameScreen::ID, dynamic_cast<Screen *>(gameScreen)));
}

void SnekGame::Init()
{
	screenManager.switchScene(MainMenuScreen::ID);

	window = new RenderWindow(VideoMode(640, 640), "Snek");

	

	Start();

	Clock clock;
	Time elapsed = clock.getElapsedTime();
	clock.restart();


	if (!font.loadFromMemory(&ariblkfont, ariblkfont_len))
	{
		std::cout << "Load font failed" << std::endl;
	}
	else
	{
		text.setFont(font);
		text.setString("SNEK - press L to start");
		text.setCharacterSize(24);
		text.setFillColor(Color::White);
	}

	while (window->isOpen())
	{
		elapsed = clock.getElapsedTime();
		// tick
		if (elapsed.asMilliseconds() > 100 && running)
		{
			clock.restart();

			Update();
		}

		Draw();

		UpdateInput();

	}
}

void SnekGame::Start()
{
	

	

}

void SnekGame::Update()
{

	if (screenManager.currentScreen != NULL)
	{
		screenManager.currentScreen->Update();
	}
}


void SnekGame::updateMenu()
{

}

void SnekGame::updatePlay()
{
	
	if (screenManager.currentScreen != NULL)
		screenManager.currentScreen->Update();

}

void SnekGame::Draw() {
	// drawing

	window->clear(Color::Black);

	if (screenManager.currentScreen != NULL)
	{
		screenManager.currentScreen->Draw(*window);
	}

	window->display();
}

void SnekGame::UpdateInput()
{
	Event e;
	while (window->pollEvent(e))
	{
		if (e.type == Event::Closed)
		{
			window->close();
		}


		if (screenManager.currentScreen != NULL)
		{
			screenManager.currentScreen->InputUpdate(e);
		}


	}
}
