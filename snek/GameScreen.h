#pragma once
#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "Screen.h"
#include "ScreenManager.h"
#include <queue>

using namespace sf;

class SnekGame;
class Tile;

class GameScreen : public Screen
{
public:

	const static std::string ID;

	GameScreen(SnekGame *game, ScreenManager *manager);

	void Start() override;
	void Update() override;
	void InputUpdate(Event &e) override;
	void Draw(RenderWindow &window) override;
	void End() override;

	Font font;
	Text scoreText;
	Text pauseText;
	Text gameOverText;
private:
	SnekGame* game;
	ScreenManager* manager;

	static const int WIDTH = 32;
	static const int HEIGHT = 32;

	int boardArr[HEIGHT][WIDTH];
	int tileWidth = 20;
	Tile* tileArr[32][48];
	Vector2<int> speed;
	std::vector<Vector2<int>> snakeList;
	std::queue<Vector2<int>> digestingAppleQ;

	Vector2<int> startPos;
	Vector2<int> applePos;

	void createBoard();
	void spawnApple();
	void setSpeed(int x, int y);
	bool isCollideSelf();
	void checkCollideApple();
	void appendSnakeBody(int x, int y);
	void digestApple();
	bool moveSnake();
	void updateScore();
	void gameOver();

	bool running;
	bool pause;

	int score;

};

#endif // !_GAME_SCREEN_H
