#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Object.h"

class AnimationManager
{
	// CharSet Line Initialized by ACTOR.STATE
	// CHARSET COL INITIALIZED AT 0:positionCounter

public:

	AnimationManager();

	~AnimationManager();

private:
	virtual int splitTexture(TextureManager& tm) { return 1; };

	// Returns current texture value
	//virtual sf::Sprite* ping(Actor::__STATE  pState, const TextureManager& tm);
	//virtual sf::Sprite* ping(Object::__STATE pState, const TextureManager& tm);

protected:
	int							positionCounter;
	std::vector<sf::Sprite*>	*currentSprites;

};

