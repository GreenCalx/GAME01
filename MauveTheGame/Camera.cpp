#include "Camera.h"


void Camera::updateView(sf::Vector2f offset) {
	_cameraView->move(offset);

	//_cameraViewZone.left += offset.x;
	//_cameraViewZone.top -= offset.y;
}


void Camera::attachToPlayer(sf::Vector2f newPos) {
	_cameraView = new sf::View(newPos, sf::Vector2f(__SCREEN_WIDTH, __SCREEN_HEIGHT));
}

Camera::Camera()
{
	_cameraView = new sf::View( sf::Vector2f(__SCREEN_WIDTH/2, __SCREEN_WIDTH/2), sf::Vector2f(__SCREEN_WIDTH, __SCREEN_HEIGHT) );
	_cameraView->setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

}


Camera::~Camera()
{
}
