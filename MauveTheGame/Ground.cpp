#include "Ground.h"



Ground::Ground(sf::Vector2f pPosition) : Object(GROUND, false , false)
{
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("ground01"));
	mPosition = pPosition;
	mSprite.setPosition(pPosition);
	__REGULAR_BB_WIDTH = mSprite.getLocalBounds().width;
	__REGULAR_BB_HEIGHT =mSprite.getLocalBounds().height;
	updateBoundingBox();
	zLayer = 0;
}

void Ground::updateBoundingBox() {
	__boundingBox = sf::IntRect(mPosition.x, mPosition.y, /*mPosition.x +*/ __REGULAR_BB_WIDTH, /*mPosition.y +*/ __REGULAR_BB_HEIGHT);
}

sf::Vector2f Ground::onCollisionOnExternal(sf::Vector2f impactDirection)
{
	//sf::Vector2f v = Utils::unarizedVector(impactDirection);
	//v.x *= 0;
	//v.y *= 0;
	return impactDirection;
}

Ground::~Ground()
{
}
