#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
#include "TextureManager.h"

using namespace sf;

class Object
{
public :
	enum __STATE {
		IDLE, MOVING
	};


public:

	Object(bool isCrossable, bool isSensibleToGravity);
	~Object();
	virtual void behaviour() {};
	virtual void updateBoundingBox() {};

public: // mutators
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pPosition);
	void setSprite(sf::Sprite pSprite);
	sf::Sprite getSprite();
	bool isCrossable() { return mIsCrossable; }
	bool isSensibleToGravity() { return mIsSensibleToGravity; }
	string getTextureLabel() { return mTextureLabel; }
	void	setTextureLabel(string pLabel) {
		mTextureLabel = pLabel;
	}
	sf::IntRect getBoundingBox() { return __boundingBox; }
private :
	bool mIsCrossable;
	bool mIsSensibleToGravity;
protected :
	sf::Vector2f			mPosition;
	sf::Sprite				mSprite;
	TextureManager*			mTextureManager;
	string					mTextureLabel;
	sf::IntRect				__boundingBox;

	__STATE					currentState;
};

