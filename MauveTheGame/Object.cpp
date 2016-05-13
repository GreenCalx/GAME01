#include "Object.h"



Object::Object(bool isCrossable, bool isSensibleToGravity)
{
	mIsCrossable = isCrossable;
	mIsSensibleToGravity = isSensibleToGravity;
	currentState = IDLE;
}


Object::~Object()
{

}

sf::Vector2f Object::getPosition()
{
	return mPosition;
}

void Object::setPosition(sf::Vector2f pPosition)
{
	mPosition = pPosition;
}

void Object::setSprite(sf::Sprite pSprite)
{
	mSprite = pSprite;
}

sf::Sprite Object::getSprite()
{
	return mSprite;
}
