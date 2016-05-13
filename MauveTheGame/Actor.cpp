#include "Actor.h"

void Actor::setPosition(sf::Vector2f pPosition)
{
	mPosition = pPosition;
	mSprite.setPosition(pPosition);
}

sf::Vector2f Actor::getPosition()
{
	return mPosition;
}

void Actor::setSprite(sf::Sprite pSprite)
{
	mSprite = pSprite;
}

void Actor::forbidDirection(directions toForbid)
{
	authorizedDirections[toForbid] = false;
}

void Actor::authorizeDirection(directions toAuthorize)
{
	authorizedDirections[toAuthorize] = true;
}

sf::Sprite Actor::getSprite()
{
	return mSprite;
}

void Actor::updateState() {
	if (mCurrentSpeed.x == 0. && mCurrentSpeed.y == 0.) {
		if (currentHorizontalDirection == LEFT) {
			_STATE_ = IDLE_LEFT;
			return;
		}
		else {
			_STATE_ = IDLE_RIGHT;
			return;
		}
	}
	if (mCurrentSpeed.y == 0.) {
		if (currentHorizontalDirection == LEFT) {
			_STATE_ = MOVING_LEFT;
			return;
		}
		else {
			_STATE_ = MOVING_RIGHT;
			return;
		}
	}
	else if (mCurrentSpeed.y > 0.) {
		if (currentHorizontalDirection == LEFT) {
			_STATE_ = FALLING_LEFT;
			return;
		}
		else {
			_STATE_ = FALLING_RIGHT;
			return;
		}
	} // Y > 0
	else if (mCurrentSpeed.y < 0.) {
		if (currentHorizontalDirection == LEFT) {
			_STATE_ = JUMPING_LEFT;
			return;
		}
		else {
			_STATE_ = JUMPING_RIGHT;
			return;
		}
	}
}

Actor::Actor(const char* name) :_ID_(rand()), _NAME_(name), _STATE_(IDLE_RIGHT)
{
	//authorizedDirections = map<directions, bool>();
	authorizedDirections[directions::DOWN] = true;
	authorizedDirections[directions::UP] = true;
	authorizedDirections[directions::LEFT] = true;
	authorizedDirections[directions::RIGHT] = true;
}



Actor::~Actor()
{
}
