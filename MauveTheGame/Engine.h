#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "Player.h"
#include "TextureManager.h"
#include "Object.h"
#include "Wall.h"
#include "Collision.h"
#include "Ground.h"
#include "BackGround.h"
#include "Physics.h"
class Engine
{
private : // methods
	void initActors();
	void initMap();
	bool checkCollisionsForPlayer(Player::directions direction);
public: // methods
	Engine();
	void update();
	void updateInputs();
	void updateGraphics();
	void updatePhysics();
	void drawScene(sf::RenderWindow &window);
	~Engine();
public : // mutators
	sf::Sprite getPlayerSprite() { return mPlayer->getSprite(); };
private : // variables
	Player* mPlayer;
	std::vector<Object> mObjectMap;
	TextureManager* tm;
};

