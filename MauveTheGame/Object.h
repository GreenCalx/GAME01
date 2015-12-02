#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
#include "TextureManager.h"

using namespace sf;

class Object
{
public:
	Object(bool isCrossable, bool isSensibleToGravity);
	~Object();
	virtual void behaviour() {};

public: // mutators
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pPosition);
	void setSprite(sf::Sprite pSprite);
	sf::Sprite getSprite();
	bool isCrossable() { return mIsCrossable; }
	bool isSensibleToGravity() { return mIsSensibleToGravity; }

private :
	bool mIsCrossable;
	bool mIsSensibleToGravity;
protected :
	sf::Vector2f mPosition;
	sf::Sprite mSprite;
	TextureManager* mTextureManager;
};

