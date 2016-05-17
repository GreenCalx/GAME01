#pragma once
#include <SFML/Graphics.hpp>
/* SCREEN SIZE */
static const float  __SCREEN_WIDTH = 800.0;
static const float	__SCREEN_HEIGHT = 600.0;

class Utils
{
public:
	static sf::Vector2f unarizedVector(sf::Vector2f v);
	
public:
	Utils();
	~Utils();
};

