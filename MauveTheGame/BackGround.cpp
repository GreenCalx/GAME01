#include "BackGround.h"



BackGround::BackGround() : Object(BACKGROUND, false, false)
{
	mTextureManager = TextureManager::Instance();
	
	mSprite = sf::Sprite(*mTextureManager->getTexture("background01"));
	zLayer = -1;
}


void BackGround::setStatic(void) {
	mIsAttachedToCameraMovements = true;
	zLayer = -999;
}



BackGround::~BackGround()
{
}
