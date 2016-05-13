#pragma once
#include "Object.h"
class Ground : public Object
{
public:
	Ground(sf::Vector2f pPosition);
	void updateBoundingBox() override;
	~Ground();
private:
	int __REGULAR_BB_WIDTH;
	int __REGULAR_BB_HEIGHT;
};

