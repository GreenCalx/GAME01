#pragma once
#include "SFML\Graphics.hpp"
#define GRAVITY_STRENGTH 1
#define GRAVITY_FACTOR	 5.0

class Physics
{
public:
	static sf::Vector2f applyGravity(sf::Vector2f& v);

private:
	Physics();
	~Physics();
};

