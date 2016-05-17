#include "ObjectUtils.h"



void ObjectUtils::onImpactBehaviour(Object* o, Actor& a, sf::Vector2f impactDirection)
{

	float vx = 0.;
	float vy = 0.;
	std::cout << vx << " " <<vy << std::endl;
	switch ( o->getType() ) {
	case (Object::__TYPE::WALL) :
		if (impactDirection.x != 0.)
			vx = (impactDirection.x / impactDirection.x);
		if (impactDirection.y != 0.)
			vy = (impactDirection.y / impactDirection.y);
		vx *= -1.0;
		vy *= 1.0;
		std::cout << vx << " " << vy << std::endl;
		a.setCurrentMoveStep(sf::Vector2f(vx, vy));
		break;
	case (Object::__TYPE::GROUND) :
		break;
	default:
		break;
	}
}

void ObjectUtils::classicWall_onImpactBehaviour()
{
}

void ObjectUtils::classicGround_onImpactBehaviour()
{
}

ObjectUtils::ObjectUtils()
{
}


ObjectUtils::~ObjectUtils()
{
}
