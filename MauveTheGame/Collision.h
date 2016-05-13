
#pragma once
#ifndef _COLLISION_H
#define _COLLISION_H

#include <SFML/Graphics.hpp>
#include "Actor.h"
#include "Player.h"
#include "Object.h"

#ifndef PI
#define PI (3.14159265358979323846)
#endif
#define RADIANS_PER_DEGREE (PI/180.0)
#ifndef COLLISION_ASSERTION
#define COLLISION_ASSERTION 5.0f
#endif


class Collision {
public:

	virtual ~Collision();
	
	static bool AABB( const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, sf::Vector2f moveToExecuteForSprite1 );
	static bool getCollisionDirection(Actor pMainActor, Object pCollidingObject, Player::directions direction);
	static sf::Vector2f distanceToObject(const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, Actor &pPlayer);
	static bool collideCameraViewZone(const sf::Rect<float> viewZone, const sf::Sprite& pSprite1, sf::Vector2f moveToExecute);

	static sf::Vector2f distanceToObject(const sf::IntRect& bbo1, const sf::IntRect& bbo2);
	static bool AABB(const sf::IntRect& bbo1, const sf::IntRect& bbo2, sf::Vector2f moveToExecuteForSprite1);
private:

	Collision();
};

#endif  /* _COL	LISION_H */