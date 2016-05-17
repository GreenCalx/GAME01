#include "BackGround.h"



BackGround::BackGround() : Object(BACKGROUND, false, false)
{
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("background01"));
}


BackGround::~BackGround()
{
}
