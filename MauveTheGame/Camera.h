#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Utils.h"
class Camera
{
public:
	Camera();
	~Camera();

	void updateView(sf::Vector2f updatePos);

	sf::View* getView() { return _cameraView; }
	void attachToPlayer(sf::Vector2f newPos);

private:

private:
	sf::View* _cameraView;
};

