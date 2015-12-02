#include "Player.h"


Player::Player()
{
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("player"));
	mPosition = mSprite.getPosition();
}

Player::Player(sf::Vector2f pPosition) {
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("player"));
	mPosition = pPosition;
	mSprite.setPosition(pPosition);
}

Player::~Player()
{
}

sf::Vector2f Player::getMoveStep(directions pDirection) {
	switch (pDirection) {
	case Player::UP:
		mCurrentDirection.x = 0;
		mCurrentDirection.y = -5.0f;
		break;
	case Player::LEFT:
		mCurrentDirection.x = -5.0;
		mCurrentDirection.y = 0;
		break;
	case Player::DOWN:
		mCurrentDirection.x = 0;
		mCurrentDirection.y = 5.0;
		break;
	case Player::RIGHT:
		mCurrentDirection.x = 5.0;
		mCurrentDirection.y = 0;
		break;
	}
	return mCurrentDirection;
}

void Player::jump()
{
}

void Player::updateSprite()
{
	
}

void Player::move(directions pDirection)
{
	switch (pDirection)
	{
	case Player::UP:
		mPosition.y -= 5.0f;
		break;
	case Player::LEFT:
		mPosition.x -= 5.0f;
		break;
	case Player::DOWN:
		mPosition.y += 5.0f;
		break;
	case Player::RIGHT:
		mPosition.x += 5.0f;
		break;
	default:
		break;
	}
	mSprite.setPosition(mPosition);
}
