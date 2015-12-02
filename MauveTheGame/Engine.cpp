#include "Engine.h"



void Engine::initActors()
{
	// initialize textures
	tm->addFullTexture("player", "Resources/Sprites/Actors/Player2.png");

	// initialize actor objects
	mPlayer = new Player();
}

void Engine::initMap() {

	mObjectMap = std::vector<Object>();

	// initialize textures
	tm->addFullTexture("wall01", "Resources/sprites/Walls/wall01.png");
	tm->addFullTexture("ground01", "Resources/sprites/Ground/ground01.png");
	tm->addFullTexture("background01", "Resources/sprites/BackGround/background01.png");

	// init used objects
	Object wall   = Wall(sf::Vector2f(150.0f, 150.0f) );
	Object ground = Ground(sf::Vector2f(0.0f, 500.0f));
	Object background = BackGround();

	// fill the array
	mObjectMap.push_back(background);
	mObjectMap.push_back(wall);
	mObjectMap.push_back(ground);
}

bool Engine::checkCollisionsForPlayer(Player::directions direction) {
	sf::Vector2f directionVector = mPlayer->getMoveStep(direction);
	for each (Object o in mObjectMap)
	{
		if (o.isCrossable()) continue;
		else if (Collision::AABB(mPlayer->getSprite(), o.getSprite(), directionVector))
			return true;
	}
	return false;
}

void Engine::updateInputs() {

	if ( mPlayer == NULL ) return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (!checkCollisionsForPlayer(Player::directions::UP))
			mPlayer->jump();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if ( !checkCollisionsForPlayer(Player::directions::UP) )
			mPlayer->move(Player::directions::UP);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (!checkCollisionsForPlayer(Player::directions::LEFT))
			mPlayer->move(Player::directions::LEFT);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (!checkCollisionsForPlayer(Player::directions::DOWN))
			mPlayer->move(Player::directions::DOWN);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (!checkCollisionsForPlayer(Player::directions::RIGHT))
			mPlayer->move(Player::directions::RIGHT);
	}
}
void Engine::update() {
	updatePhysics();
	updateGraphics();
}
void Engine::updateGraphics()
{

}

void Engine::updatePhysics()
{
	sf::Vector2f newPosition = sf::Vector2f();
	for each (Object o in mObjectMap)
	{
		if (o.isSensibleToGravity())
		{
			newPosition = Physics::applyGravity(o.getPosition());
			o.setPosition(newPosition);
		}
	}
	if ( !checkCollisionsForPlayer(Player::directions::DOWN)) {
		newPosition = Physics::applyGravity(  mPlayer->getPosition() );
		mPlayer->setPosition(newPosition);
		cout << "Player position : " << to_string(mPlayer->getPosition().x) << " ; " << to_string(mPlayer->getPosition().y) << endl;
	}
}

void Engine::drawScene(sf::RenderWindow &window) {
	
	//draw map
	for each (Object o in mObjectMap)
	{
		window.draw( o.getSprite() );
	}

	//draw actors
	window.draw(mPlayer->getSprite());

}

Engine::Engine()
{
	tm = TextureManager::Instance();
	initActors();
	initMap();
}


Engine::~Engine()
{
}