#include "Wall.h"



Wall::Wall(sf::Vector2f pPosition) : Object(false, false)
{
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("wall01"));
	mPosition = pPosition;
	mSprite.setPosition(pPosition);
}

Wall::~Wall()
{
}
