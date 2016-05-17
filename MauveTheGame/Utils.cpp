#include "Utils.h"

sf::Vector2f Utils::unarizedVector(sf::Vector2f v) {
	sf::Vector2f ret_v;
	ret_v.x  = -((v.x) / (v.x));
	ret_v.y  = -((v.y) / (v.y));
	return ret_v;
}



Utils::Utils()
{
}


Utils::~Utils()
{
}
