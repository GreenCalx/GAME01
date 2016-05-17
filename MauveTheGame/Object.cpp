#include "Object.h"



Object::Object(__TYPE type, bool isCrossable, bool isSensibleToGravity)
{
	mIsCrossable = isCrossable;
	mIsSensibleToGravity = isSensibleToGravity;
	currentState = IDLE;
	selfType = type;
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
