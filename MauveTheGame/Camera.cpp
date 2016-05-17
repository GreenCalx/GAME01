#include "Camera.h"


void Camera::updateView(sf::Vector2f offset) {
	_cameraView->move(offset);
	float vx = _cameraView->getCenter().x;
	float vy = _cameraView->getCenter().y;
	_topLeftCornerPosition.x = vx - __SCREEN_WIDTH/2;
	_topLeftCornerPosition.y = vy - __SCREEN_HEIGHT/2;

}


void Camera::attachToPlayer(sf::Vector2f newPos) {
	_cameraView = new sf::View(newPos, sf::Vector2f(__SCREEN_WIDTH, __SCREEN_HEIGHT));
	_topLeftCornerPosition = newPos;
}

Camera::Camera()
{
	_cameraView = new sf::View( sf::Vector2f(__SCREEN_WIDTH/2, __SCREEN_WIDTH/2), sf::Vector2f(__SCREEN_WIDTH, __SCREEN_HEIGHT) );
	_cameraView->setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

}


Camera::~Camera()
{
}
