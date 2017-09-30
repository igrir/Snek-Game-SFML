#pragma once
#include <SFML\Graphics.hpp>
using namespace sf;

class Screen
{
public:
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void InputUpdate(Event &e) = 0;
	virtual void Draw(RenderWindow &window) = 0;
	virtual void End() = 0;
};

