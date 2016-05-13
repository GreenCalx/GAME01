#pragma once
#include "TextureManager.h"
#include "SFML\Graphics.hpp"

#define _CRT_SECURE_NO_WARNINGS

#define MINIMUM_SPEED_TO_MOVE 1
#define NUMBER_OF_DIRECTIONS 4

/*
 * WARNING : ID is currently randomly generated
 */

using namespace sf;

class Actor
{
public : // misc
	enum directions {
		UP, LEFT, DOWN, RIGHT
	};

	enum __STATE {
		IDLE_LEFT		= 0,
		IDLE_RIGHT		= 1,
		MOVING_LEFT		= 2,
		MOVING_RIGHT	= 3,
		JUMPING_LEFT	= 4,
		JUMPING_RIGHT	= 5,
		FALLING_LEFT	= 6,
		FALLING_RIGHT	= 7,
		CROUCHING_LEFT	= 8, 
		CROUCHING_RIGHT	= 9,
		ATTACKING_LEFT	= 10,
		ATTACKING_RIGHT	= 11
	};

public:
	Actor(const char* name);
	virtual void move(directions pDirection) {};
	virtual void aggregateToCurrentVerticalSpeed(float gravity) {};
	virtual void updatePosition() {};
	virtual void updateBoundingBox() {};
	virtual char* toString() { return ""; };
	~Actor();

public : // mutators
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pPosition);
	void setSprite(sf::Sprite pSprite);
	void forbidDirection(directions toForbid);
	void authorizeDirection(directions toAuthorize);
	map<directions, bool> getAuthorizedDirections() { return authorizedDirections; };
	void updateState();
	
	
	sf::Sprite getSprite();
	string getTextureLabel() { return textureLabel; }
	void   setTextureLabel(string pLabel) {
		textureLabel = pLabel;
	}

	void setSTATE(__STATE newSTATE) { _STATE_ = newSTATE; }
	__STATE getSTATE(void) { return _STATE_; }

	const char* getNAME(void) { return _NAME_; }
	const int getID(void) { return _ID_; }

	sf::IntRect getBoundingBox() { return __boundingBox; }

	// MEMBERS
protected :
	map<directions, bool> authorizedDirections;
	sf::Sprite			  mSprite;
	sf::Vector2f		  mPosition;
	TextureManager*       mTextureManager;
	string			      textureLabel;
	directions			  currentHorizontalDirection;
	sf::IntRect			  __boundingBox;

	sf::Vector2f		mCurrentDirection;
	sf::Vector2f mVelocity;
	sf::Vector2f mCurrentSpeed;
	sf::Vector2f mSpeed;
	bool		 mIsInAir;
	bool		 mIsJumping;

	__STATE			_STATE_;
	const char*		_NAME_;
	const int		_ID_;

public:

};

