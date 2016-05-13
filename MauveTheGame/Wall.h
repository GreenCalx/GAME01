#pragma once
#include "Object.h"
class Wall :
	public Object
{
public:
	Wall(sf::Vector2f pPosition);
	void updateBoundingBox() override;
	~Wall();
private:
	int __REGULAR_BB_WIDTH ;
	int __REGULAR_BB_HEIGHT;
};

