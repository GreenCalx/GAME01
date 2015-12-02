#pragma once
#include "TextureManager.h"
#include "SFML\Graphics.hpp"

using namespace sf;

class Actor
{
public : // misc
	enum directions {
		UP, LEFT, DOWN, RIGHT
	};

public:
	Actor();
	virtual void move(directions pDirection) {};
	~Actor();

public : // mutators
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f pPosition);
	void setSprite(sf::Sprite pSprite);
	sf::Sprite getSprite();

protected :
	sf::Sprite mSprite;
	sf::Vector2f mPosition;
	TextureManager* mTextureManager;
};

