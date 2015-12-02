#include "BackGround.h"



BackGround::BackGround() : Object(true, false)
{
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("background01"));
}


BackGround::~BackGround()
{
}
