#include "Collision.h"

Collision::Collision() {
}

bool Collision::AABB(const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, sf::Vector2f moveToExecuteForSprite1) {

	sf::FloatRect boundingBox1 = pSprite1.getGlobalBounds();
	boundingBox1.left += moveToExecuteForSprite1.x;
	boundingBox1.top  += moveToExecuteForSprite1.y;

	sf::FloatRect boundingBox2 = pSprite2.getGlobalBounds();

	if (boundingBox1.intersects(boundingBox2)) {
		return true;
	}
	return false;

}

Collision::~Collision() {
}
