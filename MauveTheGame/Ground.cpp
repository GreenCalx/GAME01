#include "Ground.h"



Ground::Ground(sf::Vector2f pPosition) : Object(false , false)
{
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("ground01"));
	mPosition = pPosition;
	mSprite.setPosition(pPosition);
	__REGULAR_BB_WIDTH = mSprite.getLocalBounds().width;
	__REGULAR_BB_HEIGHT =mSprite.getLocalBounds().height;
	updateBoundingBox();
}

void Ground::updateBoundingBox() {
	__boundingBox = sf::IntRect(mPosition.x, mPosition.y, /*mPosition.x +*/ __REGULAR_BB_WIDTH, /*mPosition.y +*/ __REGULAR_BB_HEIGHT);
}

Ground::~Ground()
{
}
