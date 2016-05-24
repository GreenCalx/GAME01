#include "Player.h"


Player::Player() : Actor("Player")
{
	mSpeed.x = 0;
	mSpeed.y = 0;
	mCurrentSpeed.x = 0;
	mCurrentSpeed.y = 0;
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("player"));
	mPosition = mSprite.getPosition();
	updateBoundingBox();
}

Player::Player(sf::Vector2f pPosition) : Actor("Player") {
	mTextureManager = TextureManager::Instance();
	mSprite = sf::Sprite(*mTextureManager->getTexture("player"));
	mPosition = pPosition;
	mSprite.setPosition(pPosition);
	updateBoundingBox();
}

Player::~Player()
{
}

//sf::Vector2f Player::getMoveStep() {
//	return mCurrentSpeed;
//}

void Player::jump()
{
}

void Player::resetHorizontalSpeed() {
	mSpeed.x = 0;
	mCurrentSpeed.x = 0;
}

void Player::resetVerticalSpeed() {
	mSpeed.y = 0;
	mCurrentSpeed.y = 0;
}

void Player::decelerateOnIce()
{
	mSpeed.x -= mSpeed.x/10;
	mSpeed.y -= mSpeed.y/10;
}

void Player::decelerate()
{
	mSpeed.x -= mSpeed.x / 4;
	//mSpeed.y -= mSpeed.y / 4;
}

// TODO : backward jump should be slower...
void Player::updateSpeed()
{
	mCurrentSpeed = mAcceleration * mSpeed + (1 - mAcceleration) * mCurrentSpeed;
	if (fabs(mCurrentSpeed.x) < MINIMUM_SPEED_TO_MOVE) mCurrentSpeed.x = 0;
	if (fabs(mCurrentSpeed.y) < MINIMUM_SPEED_TO_MOVE) mCurrentSpeed.y = 0;
	mPosition.x += mCurrentSpeed.x;
	mPosition.y += mCurrentSpeed.y;

	mSprite.setPosition(mPosition);
}

void Player::updateSprite()
{
	
}

void Player::move(directions pDirection)
{
	switch (pDirection)
	{
	case Player::UP: // JUMP OR LADDER OR STAIRS
		if (authorizedDirections.at(Player::UP)) 
			mSpeed.y = - MAX_SPEED*4;
		break;
	case Player::LEFT: // LEFT..
		if (authorizedDirections.at(Player::LEFT))
			mSpeed.x = - MAX_SPEED;
		currentHorizontalDirection = LEFT;
		break;
	case Player::DOWN: // CROUCH OR SLIDES
		if (authorizedDirections.at(Player::DOWN))
			mSpeed.y = MAX_SPEED;
		break;
	case Player::RIGHT: // RIGHT..
		if (authorizedDirections.at(Player::RIGHT))
			mSpeed.x = MAX_SPEED;
		currentHorizontalDirection = RIGHT;
		break;
	default:
		break;
	}
	// Speed interpolation
}

void Player::updatePosition() {
	updateSpeed();
}

void Player::aggregateToCurrentVerticalSpeed(float value)
{
	if (mCurrentSpeed.y < MAX_SPEED) mSpeed.y += value;
	 
	//updateSpeed();
}

void Player::updateBoundingBox() {
	if ((_STATE_ == CROUCHING_LEFT) || (CROUCHING_RIGHT == _STATE_))
		__boundingBox = sf::IntRect(mPosition.x, mPosition.y, /*mPosition.x +*/ __CROUCH_BB_WIDTH, /*mPosition.y +*/ __CROUCH_BB_HEIGHT);
	else
		__boundingBox = sf::IntRect(mPosition.x, mPosition.y, /*mPosition.x +*/ __REGULAR_BB_WIDTH, /*mPosition.y + */__REGULAR_BB_HEIGHT);
}

char* Player::toString() {
	//char* cstr = "";
	//unsigned int cstr_size = sizeof(char*) * 20;
	//char* val1 = ""; 
	//sprintf_s(val1, cstr_size,"%f", (float)mCurrentSpeed.x, "\\init.scm");
	//char* val2 = ""; 
	//sprintf_s(val2, cstr_size, "%f", (float)mCurrentSpeed.y, "\\init.scm");

	//strcat_s(cstr, cstr_size, "Current Speed : (");
	//strcat_s(cstr, cstr_size, val1);
	//strcat_s(cstr, cstr_size, ";" );
	//strcat_s(cstr, cstr_size, val2);
	//strcat_s(cstr, cstr_size, ")" );

	return " ff ";
}