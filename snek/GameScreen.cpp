#include "GameScreen.h"
#include "SnekGame.h"
#include <iostream>
#include "MainMenuScreen.h"

#include "ariblkfont.h"

const std::string GameScreen::ID = "GameScreen";

GameScreen::GameScreen(SnekGame* game, ScreenManager* manager)
{
	this->game = game;
	this->manager = manager;


	speed.x = 1;
	speed.y = 0;

	startPos.x = 10;
	startPos.y = 20;

	createBoard();

	if (!font.loadFromMemory(&ariblkfont, ariblkfont_len))
	{
		std::cout << "Load font failed" << std::endl;
	}
	else
	{
		scoreText.setFont(font);
		scoreText.setString("0");
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(Color::White);

		pauseText.setFont(font);
		pauseText.setString("PAUSE");
		pauseText.setCharacterSize(180);
		pauseText.setFillColor(Color::Magenta);
		pauseText.setPosition(0, 150);

		gameOverText.setFont(font);
		gameOverText.setString("GAME OVER\npress L to back");
		gameOverText.setCharacterSize(80);
		gameOverText.setFillColor(Color::Magenta);
		gameOverText.setPosition(0, 150);;
	}

}


void GameScreen::Start()
{
	score = 0;
	running = true;
	pause = false;

	scoreText.setString(std::to_string(score));

	snakeList.clear();

	speed.x = 1;
	speed.y = 0;

	while (!digestingAppleQ.empty())
	{
		digestingAppleQ.pop();
	}

	// create some body
	for (int i = 0; i < 2; i++)
	{
		appendSnakeBody(startPos.x - i, startPos.y);
	}

	int snakeBodyIt = 0;
	for (auto it = snakeList.begin(); it != snakeList.end(); ++it)
	{
		it->x = startPos.x - snakeBodyIt;
		it->y = startPos.y;

		snakeBodyIt++;
	}
	spawnApple();
}

void GameScreen::Update()
{
	if (!running || pause)
		return;

	// move snake
	if (moveSnake()) {
		// check collision with head
		if (isCollideSelf()) {
			running = false;
		}

		checkCollideApple();
		digestApple();

	}
	else {
		running = false;
	}

}

bool GameScreen::moveSnake()
{
	int prevX = 0, prevY = 0;
	for (std::vector<Vector2<int>>::iterator it = snakeList.begin(); it != snakeList.end(); ++it) {
		if (it == snakeList.begin()) {
			prevX = it->x;
			prevY = it->y;

			int nextX = prevX + speed.x;
			int nextY = prevY + speed.y;

			// move head
			if (nextX >= 0 && nextX <= WIDTH - 1) {
				it->x = nextX;
			}
			else {
				std::cout << "hit wall!" << std::endl;
				gameOver();
				return false;
			}
			if (nextY >= 0 && nextY <= HEIGHT - 1) {
				it->y = nextY;
			}
			else {
				std::cout << "hit wall!" << std::endl;
				gameOver();
				return false;
			}

		}
		else
		{
			int tmpX = it->x;
			int tmpY = it->y;

			it->x = prevX;
			it->y = prevY;

			prevX = tmpX;
			prevY = tmpY;

		}
	}
	return true;
}

void GameScreen::InputUpdate(Event &e)
{
	if (e.type == Event::KeyPressed) {
		if (e.key.code == Keyboard::Key::W) {
			setSpeed(0, -1);
		}
		else if (e.key.code == Keyboard::Key::A) {
			setSpeed(-1, 0);
		}
		else if (e.key.code == Keyboard::Key::S) {
			setSpeed(0, 1);
		}
		else if (e.key.code == Keyboard::Key::D) {
			setSpeed(1, 0);
		}
		else if (e.key.code == Keyboard::Key::P) {
			pause = !pause;
		}
		else if (e.key.code == Keyboard::Key::L) {
			manager->switchScene(MainMenuScreen::ID);
		}
	}
}

void GameScreen::Draw(RenderWindow &window)
{
	// clear board
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			//window.draw(*shapeArr[i][j]);
			Tile* tile = tileArr[i][j];

			tile->isActive = false;

			tile->draw(&window);
		}
	}

	// draw snake
	for (std::vector<Vector2<int>>::iterator it = snakeList.begin(); it != snakeList.end(); ++it) {
		Tile* tile = tileArr[it->y][it->x];
		tile->isActive = true;
		tile->setActiveColor(Color::Green);
		tile->draw(&window);
	}

	// draw apple
	Tile* appleTile = tileArr[applePos.y][applePos.x];
	appleTile->isActive = true;
	appleTile->setActiveColor(Color::Red);
	appleTile->draw(&window);

	//draw score
	window.draw(scoreText);

	if (pause)
		window.draw(pauseText);

	if (!running)
		window.draw(gameOverText);
}

void GameScreen::End()
{

}


void GameScreen::createBoard()
{
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			Tile *tile;
			tile = new Tile();
			tile->setWidth(tileWidth);
			tile->setPosition(j, i);

			tileArr[i][j] = tile;
		}
	}
}

void GameScreen::setSpeed(int x, int y)
{

	if (speed.x == 0 && x != 0 ||
		speed.y == 0 && y != 0)
	{
		speed.x = x;
		speed.y = y;
	}

}


bool GameScreen::isCollideSelf()
{
	if (snakeList.empty())
		return false;

	Vector2<int> head = snakeList.front();
	auto it = snakeList.begin() + 1;
	bool collide = false;
	while (it != snakeList.end() && !collide) {

		if (it->x == head.x && it->y == head.y) {
			std::cout << "Collide self at:" << it->x << "," << it->y << std::endl;
			collide = true;
			gameOver();
		}
		else
			++it;
	}
	return collide;
}

void GameScreen::checkCollideApple()
{
	if (snakeList.empty())
		return;

	auto head = snakeList.begin() + 1;

	if (applePos.x == head->x && applePos.y == head->y)
	{
		Vector2<int> digestedApple(applePos.x, applePos.y);
		digestingAppleQ.push(digestedApple);

		updateScore();

		spawnApple();
	}

}

void GameScreen::appendSnakeBody(int x, int y)
{
	Vector2<int> body(x, y);
	snakeList.emplace_back(body);
}

void GameScreen::spawnApple()
{
	int x = rand() % WIDTH;
	int y = rand() % HEIGHT;

	applePos.x = x;
	applePos.y = y;

}

void GameScreen::digestApple()
{
	if (snakeList.empty())
		return;

	auto tail = snakeList.end() - 1;

	if (!digestingAppleQ.empty())
	{
		Vector2<int> apple = digestingAppleQ.front();
		if (tail->x == apple.x && tail->y == apple.y) {
			appendSnakeBody(apple.x, apple.y);

			digestingAppleQ.pop();
		}

	}

}

void GameScreen::updateScore()
{
	score++;
	scoreText.setString(std::to_string(score));
}

void GameScreen::gameOver()
{
	scoreText.setString(std::to_string(score));
}