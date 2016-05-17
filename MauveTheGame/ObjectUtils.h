#pragma once
#include "Actor.h"
#include "Wall.h"
#include "Ground.h"

class ObjectUtils
{

public :
	static void onImpactBehaviour(Object* o, Actor& a, sf::Vector2f impactDirection);
	static void classicWall_onImpactBehaviour();
	static void classicGround_onImpactBehaviour();
public:
	ObjectUtils();
	~ObjectUtils();
};

