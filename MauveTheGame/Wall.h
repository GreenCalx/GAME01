#pragma once
#include "Object.h"
class Wall :
	public Object
{
public:
	Wall(sf::Vector2f pPosition);
	~Wall();
};

