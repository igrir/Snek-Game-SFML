#pragma once
#ifndef _TILE_H
#define _TILE_H

#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;

class Tile
{
public:
	Tile();
	~Tile();

	void draw(RenderWindow* renderer);
	void setPosition(float x, float y);
	Vector2<float>* getPosition();

	bool isActive;

	void setWidth(int width);
	void setActiveColor(Color color);

private:
	Vector2<float> position;
	Vector2<float> size;
	RectangleShape *rect;
	Color activeColor;
};

#endif // !_TILE_H



