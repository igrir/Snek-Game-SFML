#include <SFML\Graphics.hpp>
#include "MainMenuScreen.h"
#include "ariblkfont.h"
#include "SnekGame.h"
#include "GameScreen.h"

const std::string MainMenuScreen::ID = "MainMenuScreen";

MainMenuScreen::MainMenuScreen(SnekGame *game, ScreenManager* manager)
{
	this->game = game;
	this->manager = manager;


	if (!font.loadFromMemory(&ariblkfont, ariblkfont_len))
	{
		std::cout << "Load font failed" << std::endl;
	}
	else
	{
		textCredit.setFont(font);
		textCredit.setString("@igrir 2017\nhttp://prahasta.com");
		textCredit.setCharacterSize(17);
		textCredit.setFillColor(Color::White);

		textTitle.setFont(font);
		textTitle.setString("-SNEK-");
		textTitle.setCharacterSize(180);
		textTitle.setFillColor(Color::Magenta);
		textTitle.setPosition(0, 150);

		textHelp.setFont(font);
		textHelp.setString("press L to start/menu\npress P to pause");
		textHelp.setCharacterSize(20);
		textHelp.setFillColor(Color::Green);
		textHelp.setPosition(0, 330);

	}
}


void MainMenuScreen::Start()
{

}

void MainMenuScreen::Update()
{

}

void MainMenuScreen::InputUpdate(Event &e)
{
	if (e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Key::L) {
			manager->switchScene(GameScreen::ID);
		}
	}
}

void MainMenuScreen::Draw(RenderWindow& window)
{
	window.draw(textCredit);
	window.draw(textTitle);
	window.draw(textHelp);
}

void MainMenuScreen::End()
{
}
