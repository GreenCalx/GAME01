#include "Actor.h"

void Actor::setPosition(sf::Vector2f pPosition)
{
	mPosition = pPosition;
	mSprite.setPosition(pPosition) ;
}

sf::Vector2f Actor::getPosition()
{
	return mPosition;
}

void Actor::setSprite(sf::Sprite pSprite)
{
	mSprite = pSprite;
}

sf::Sprite Actor::getSprite()
{
	return mSprite;
}

Actor::Actor()
{
}

Actor::~Actor()
{
}
