#include "Collision.h"

Collision::Collision() {
}

bool Collision::AABB(const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, sf::Vector2f moveToExecuteForSprite1) {

	sf::FloatRect boundingBox1 = pSprite1.getGlobalBounds();

	boundingBox1.left += moveToExecuteForSprite1.x;
	boundingBox1.top  += moveToExecuteForSprite1.y;
	boundingBox1.height += moveToExecuteForSprite1.y;
	boundingBox1.width += moveToExecuteForSprite1.x;

	sf::FloatRect boundingBox2 = pSprite2.getGlobalBounds();

	if (boundingBox1.intersects(boundingBox2)) {
		return true;
	}
	return false;
}

bool Collision::AABB(const sf::IntRect& bbo1, const sf::IntRect& bbo2, sf::Vector2f moveToExecuteForSprite1) {

	sf::IntRect boundingBox1 = bbo1;

	boundingBox1.left += moveToExecuteForSprite1.x;
	boundingBox1.top += moveToExecuteForSprite1.y;
	boundingBox1.height += moveToExecuteForSprite1.y;
	boundingBox1.width += moveToExecuteForSprite1.x;

	if (boundingBox1.intersects(bbo2)) {
		return true;
	}
	return false;
}

bool Collision::getCollisionDirection(Actor pMainActor, Object pCollidingObject, Player::directions direction)
{
	//assert objects are colliding.
	//float offset = 10;
	sf::FloatRect bbo = pCollidingObject.getSprite().getGlobalBounds();
	sf::FloatRect bba = pMainActor.getSprite().getGlobalBounds();
	sf::Vector2f vRelativePosition = pMainActor.getPosition() ;
	float vActorHead = pMainActor.getPosition().y;
	float vActorFeet = pMainActor.getPosition().y + bba.height;
	float vActorLeftArm = pMainActor.getPosition().x;
	float vActorRightArm = pMainActor.getPosition().x + bba.width;
	
	switch (direction) {
		case Player::directions::UP:
			vRelativePosition.y = vActorHead + (bbo.top - bbo.height);
			if (fabs(vRelativePosition.y) < COLLISION_ASSERTION) return true;
			break;
		case Player::directions::DOWN:
			vRelativePosition.y = bbo.top + vActorFeet;
			if (fabs(vRelativePosition.y) > COLLISION_ASSERTION) return true;
			break;
		case Player::directions::LEFT:
			vRelativePosition.x = vActorLeftArm - (bbo.left + bbo.width);
			if (fabs(vRelativePosition.x) < COLLISION_ASSERTION) return true;
			break;
		case Player::directions::RIGHT:
			vRelativePosition.x = bbo.left - vActorRightArm;
			if (fabs(vRelativePosition.x) < COLLISION_ASSERTION) return true;
			break;
		default :
			return true;
			break;
	}

	return false;
}

/**
Returns the maxium authorized movement to reach the second object.
We assume that the intersection is inevitable due to the Actor's speed.
**/
sf::Vector2f Collision::distanceToObject(const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, Actor &pPlayer) {
	
	sf::FloatRect bbo1 = pSprite1.getGlobalBounds();
	sf::FloatRect bbo2 = pSprite2.getGlobalBounds();

	sf::Vector2f actorPosition = pPlayer.getPosition();
	sf::Vector2f distance;

	if (bbo1.left + bbo1.width > bbo2.left) // sprite1 left of sprite 2
		distance.x = bbo1.left + bbo1.width - bbo2.left ;
	else									// sprite1 right of sprite 2
		distance.x = bbo2.left + bbo2.width - bbo1.left;

	if (bbo1.top + bbo1.height < bbo2.top) // sprite1 top of sprite 2
		distance.y = bbo1.top + bbo1.height - bbo2.top;
	else									// sprite1 bottom of sprite 2
		distance.y = bbo2.top - ( bbo1.top + bbo1.height );

	if (distance.x < 0) {
		return sf::Vector2f();
	}
	if (distance.y < 0) {
		return sf::Vector2f();
	}

	//pPlayer.setPosition( actorPosition + distance );

	return distance;
}

sf::Vector2f Collision::distanceToObject(const sf::IntRect& bbo1, const sf::IntRect& bbo2) {
	sf::Vector2f distance;

	if (bbo1.left + bbo1.width > bbo2.left) // sprite1 left of sprite 2
		distance.x = bbo1.left + bbo1.width - bbo2.left;
	else									// sprite1 right of sprite 2
		distance.x = bbo2.left + bbo2.width - bbo1.left;

	if (bbo1.top + bbo1.height < bbo2.top) // sprite1 top of sprite 2
		distance.y = bbo1.top + bbo1.height - bbo2.top;
	else									// sprite1 bottom of sprite 2
		distance.y = bbo2.top - (bbo1.top + bbo1.height);

	if (distance.x < 0) {
		return sf::Vector2f();
	}
	if (distance.y < 0) {
		return sf::Vector2f();
	}

	return distance;
}

bool Collision::collideCameraViewZone(const sf::Rect<float> viewZone, const sf::Sprite& pSprite1, sf::Vector2f moveToExecute)
{
	sf::FloatRect bb1 = pSprite1.getGlobalBounds();

	bb1.left += moveToExecute.x;
	bb1.top += moveToExecute.y;
	bb1.height += moveToExecute.y;
	bb1.width += moveToExecute.x;

	if (bb1.left + bb1.width > viewZone.left) { // Left of viewzone
		return true;
	}
	else if (bb1.left + bb1.width > viewZone.left + viewZone.width) { // right of viewzone
		return true;
	}
	
	if (bb1.top + bb1.height < viewZone.top) { // Top of viewzone
		return true;
	}
	else if (bb1.top + bb1.height < viewZone.top + viewZone.height) {
		return true;
	}

	return false;
}


Collision::~Collision() {
}
