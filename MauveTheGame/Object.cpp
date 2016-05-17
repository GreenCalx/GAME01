#include "Object.h"



Object::Object(__TYPE type, bool isCrossable, bool isSensibleToGravity)
{
	mIsCrossable = isCrossable;
	mIsSensibleToGravity = isSensibleToGravity;
	mIsAttachedToCameraMovements = false;
	currentState = IDLE;
	selfType = type;
	zLayer = 0;
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
	mSprite.setPosition(mPosition);
	//updateBoundingBox();
}

void Object::offsetPosition(sf::Vector2f pOffset) {
	mPosition.x += pOffset.x ;
	mPosition.y += pOffset.y;
	mSprite.setPosition(mPosition);
	//updateBoundingBox();
}

void Object::setSprite(sf::Sprite pSprite)
{
	mSprite = pSprite;
}

sf::Sprite Object::getSprite()
{
	return mSprite;
}
