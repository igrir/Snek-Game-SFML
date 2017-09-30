#include "Tile.h"



Tile::Tile()
{
	// new karena dalam method ditaruh dalam array
	rect = new RectangleShape();
	rect->setFillColor(Color::Magenta);
	rect->setSize(size);
	rect->setPosition(Vector2<float>(position.x * size.x, position.y * size.y));

	isActive = true;
}

Tile::~Tile()
{
	delete(rect);
}

void Tile::draw(RenderWindow* renderer)
{
	if (isActive) 
	{
		rect->setFillColor(activeColor);
	}
	else
	{
		rect->setFillColor(Color::Blue);
	}
	renderer->draw(*this->rect);
}

void Tile::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	rect->setPosition(x*size.x, y*size.y);
}

void Tile::setWidth(int width)
{
	size.x = width;
	size.y = width;

	rect->setSize(size);
}

Vector2<float>* Tile::getPosition()
{
	return &position;
}

void Tile::setActiveColor(Color color) {
	this->activeColor = color;
}