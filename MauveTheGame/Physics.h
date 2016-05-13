#pragma once
#include "SFML\Graphics.hpp"
#include "Actor.h"
#define GRAVITY_STRENGTH .8
#define GRAVITY_FACTOR	 5.0

class Physics
{
public:
	static sf::Vector2f applyGravity(sf::Vector2f& v);
	static void	applyGravityToActor(Actor& Actor);

private:
	Physics();
	~Physics();
};

