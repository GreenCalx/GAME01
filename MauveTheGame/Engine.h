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
#include "Camera.h"
#include "Utils.h"
#include "Log.h"
#include "ActorAnimationManager.h"
#include "ObjectUtils.h"
#include "Map.h"
#include <memory>

/*
bool operator>(sf::Vector2f const &a, sf::Vector2f const& b) {
	return ( 
		( sqrt( pow(a.x, 2) > pow(b.x, 2) ) )
		&& 
		( sqrt( pow(a.y, 2) > pow(b.y, 2) ) )
		);
}
*/

class Engine
{
public:


	enum PlayerStatuses {
		IDLE, MOVING, FALLING
	};



private : // methods

	void initActors();
	void initMap();
	bool checkCollisionsForPlayer(Player::directions direction);
	void updatePlayerMovementFreedom();
	
public: // methods
	Engine();
	void update();
	void updateInputs();
	void updateGraphics();
	void updatePhysics();
	void updateCamera();
	void drawScene(sf::RenderWindow &window);
	void drawMap(sf::RenderWindow &window);
	Camera* getCamera() { return _camera; }
	map<string, bool> getKeyEvents() { return _keyEvents;  }
	map<string, bool> setKeyEvent(string key, bool state) { _keyEvents[key] = state; }
	template <typename T> int sgn(T val);
	~Engine();
public : // mutators
	sf::Sprite getPlayerSprite()					{ return mPlayer->getSprite();		};
	PlayerStatuses getPlayerStatus()				{ return mCurrentPlayerStatus;		};
	void setPlayerStatus(PlayerStatuses newStatus)  { mCurrentPlayerStatus = newStatus; };
private : // variables
	Player* mPlayer;
	std::vector<Object*> mObjectMap;
	TextureManager* tm;
	map<string, bool> _keyEvents;
	Camera* _camera;
	vector<ActorAnimationManager*> _ActorAnimationMap;
	
	PlayerStatuses mCurrentPlayerStatus;

	shared_ptr<Map> _map;

	Log *_pLOG_;
};

