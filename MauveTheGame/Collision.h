
#pragma once
#ifndef _COLLISION_H
#define _COLLISION_H

#include <SFML/Graphics.hpp>
#include <math.h>
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

class Map;

class Collision {
public:

	struct Point {
		int x, y;
		Point() { x = 0; y = 0; }
	} typedef point_t;

	struct Line {
		point_t p1, p2;
		Line() { p1 = Point(); p2 = Point(); }
		void setP1(int x, int y) { p1.x = x; p1.y = y; }
		void setP2(int x, int y) { p2.x = x; p2.y = y; }
		bool intersectsX(sf::IntRect& rect) {
			int rectRight = rect.left + rect.width;

			bool intersectP1X = ((rect.left <= p1.x) && (rectRight >= p1.x));
			bool intersectP2X = ((rect.left <= p2.x) && (rectRight >= p2.x));

			return (intersectP1X && intersectP2X);
		}
		bool intersectsY(sf::IntRect& rect) {
			int rectDown = rect.top - rect.height;

			bool intersectP1Y = ((rect.top <= p1.y) && (rectDown >= p1.y));
			bool intersectP2Y = ((rect.top <= p2.y) && (rectDown >= p2.y));

			return (intersectP1Y && intersectP2Y);
		}
		bool intersects(sf::IntRect& rect) {
			return intersectsX(rect) && intersectsY(rect);
		}
	} typedef line_t;


	virtual ~Collision();
	
	static bool AABB( const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, sf::Vector2f moveToExecuteForSprite1 );
	static bool getCollisionDirection(Actor pMainActor, Object pCollidingObject, Player::directions direction);
	static sf::Vector2f distanceToObject(const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, Actor &pPlayer);
	static bool collideCameraViewZone(const sf::Rect<float> viewZone, const sf::Sprite& pSprite1, sf::Vector2f moveToExecute);

	// Map Collision Checkers
	static int ActorCollisionWithMapGrid(Map* iMap, Actor* iActor);
	static vector<pair<int, int>> collisionBetweenXLineAndGrid(Map * iMap, Line& iEdgeBeforeMove, Line& iEdgeAfterMove);
	static vector<pair<int, int>> collisionBetweenYLineAndGrid(Map * iMap, Line& iEdgeBeforeMove, Line& iEdgeAfterMove);


	static sf::Vector2f distanceToObject(const sf::IntRect& bbo1, const sf::IntRect& bbo2);
	static bool AABB(const sf::IntRect& bbo1, const sf::IntRect& bbo2, sf::Vector2f moveToExecuteForSprite1);
private:

	Collision();
};

#endif  /* _COL	LISION_H */ 