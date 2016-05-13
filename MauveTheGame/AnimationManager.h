#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Object.h"

/*
extern int get_rows(int a);
#define get_rows(a) ((a)%(ACTOR_ROW_SIZE))

extern int get_cols(int b);
#define get_cols(b) ((b)%(ACTOR_COL_SIZE))
*/
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
	int						positionCounter;
	std::vector<sf::Sprite*> *currentSprites;

};

