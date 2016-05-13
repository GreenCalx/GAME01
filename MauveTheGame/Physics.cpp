#include "Physics.h"



sf::Vector2f Physics::applyGravity(sf::Vector2f & v)
{
	// We add because in SFML Y axis is inverted.
	v.y += GRAVITY_STRENGTH * GRAVITY_FACTOR;
	return v;
}

void Physics::applyGravityToActor(Actor & pActor)
{
	pActor.aggregateToCurrentVerticalSpeed(GRAVITY_STRENGTH * GRAVITY_FACTOR);
}

Physics::Physics()
{
}


Physics::~Physics()
{
}
