#pragma once
#include "Actor.h"
#include <math.h>

class Player : public Actor
{
public : // misc
	


private : // methods

public: // methods
	Player();
	Player(sf::Vector2f pPosition);
	~Player();
	void updateSprite();
	virtual void move(directions pDirection) override;
	virtual void aggregateToCurrentVerticalSpeed(float value) override;
	virtual void updatePosition() override;
	void updateBoundingBox() override;
	
	void jump();
	void decelerateOnIce();
	void decelerate();
	void updateSpeed();
	void resetHorizontalSpeed();
	void resetVerticalSpeed();
	char* toString() override;

public : // mutators	
	void setCurrentDirection(sf::Vector2f pCurrentDirection) { mCurrentDirection = pCurrentDirection; }
	bool isInAir() { return mIsInAir; }
	void setInAir(const bool b) { if (!b) this->resetVerticalSpeed(); mIsInAir = b; }
	bool isJumping() { return mIsJumping; }
	void setIsJumping(const bool b) { /*if (!b) this->resetVerticalSpeed();*/ mIsJumping = b; }

private : // variables
	
	const float MAX_SPEED     = 10.0f;
	const float mAcceleration = 0.2f;

	const int	__REGULAR_BB_WIDTH = 50;
	const int	__REGULAR_BB_HEIGHT = 100;
	const int	__CROUCH_BB_WIDTH = 50;
	const int	__CROUCH_BB_HEIGHT = 50;
};

