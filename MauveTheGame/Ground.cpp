#include "Ground.h"



Ground::Ground(sf::Vector2f pPosition) : Object(false , false)
{
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("ground01"));
	mPosition = pPosition;
	mSprite.setPosition(pPosition);
}


Ground::~Ground()
{
}
