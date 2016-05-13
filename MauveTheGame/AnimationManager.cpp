#include "AnimationManager.h"


AnimationManager::AnimationManager()
	: positionCounter(0)
{
	currentSprites = new std::vector<sf::Sprite*>();
	//currentSprites = new std::vector<sf::Sprite>();
}


AnimationManager::~AnimationManager() {

	currentSprites->clear();
	delete currentSprites;
	currentSprites = nullptr;

}
