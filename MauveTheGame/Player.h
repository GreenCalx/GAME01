#pragma once
#include "Actor.h"

class Player : public Actor
{
public : // misc
	


private : // methods

public: // methods
	Player();
	Player(sf::Vector2f pPosition);
	~Player();
	void updateSprite();
	void move(directions pDirection);
	sf::Vector2f getMoveStep(directions pDirection);
	void jump();

public : // mutators	
	void setCurrentDirection(sf::Vector2f pCurrentDirection) { mCurrentDirection = pCurrentDirection; }

private : // variables
	sf::Vector2f mCurrentDirection;
	sf::Vector2f mVelocity;	
	float mSpeed;

};

