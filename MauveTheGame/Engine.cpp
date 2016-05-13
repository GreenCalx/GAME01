#include "Engine.h"

/**

TODO :
	- better reset speed ( mb only reset x and y speed when its necessary ? )
		-> will give a better sensation overall.
	- Overall improve movement quality
*/

void Engine::initActors()
{
	// initialize textures
	tm->addFullTexture("player", "Resources/Sprites/Actors/TEST_CHAR.png");

	// initialize actor objects
	mPlayer = new Player();
	mPlayer->setTextureLabel("player");
	//Initialize Camera
	_camera = new Camera();
	_camera->attachToPlayer(mPlayer->getPosition());
	//Animation Manager
	ActorAnimationManager* am = new ActorAnimationManager(mPlayer, tm);
	_ActorAnimationMap.push_back(am);
}

void Engine::initMap() {

	mObjectMap = std::vector<Object>();

	// initialize textures
	tm->addFullTexture("wall01", "Resources/sprites/Walls/wall01.png");
	tm->addFullTexture("ground01", "Resources/sprites/Ground/ground01.png");
	tm->addFullTexture("background01", "Resources/sprites/BackGround/background01.png");

	// init used objects
	Object wall2   = Wall(sf::Vector2f(255.0f, 370.0f) );
	wall2.setTextureLabel("wall01");
	Object wall = Wall(sf::Vector2f(155.0f, 100.0f));
	wall.setTextureLabel("wall01");
	Object ground = Ground(sf::Vector2f(0.0f, 500.0f));
	ground.setTextureLabel("ground01");
	Object background = BackGround();
	background.setTextureLabel("background01");
	// fill the array
	mObjectMap.push_back(background);
	mObjectMap.push_back(wall);
	mObjectMap.push_back(wall2);
	mObjectMap.push_back(ground);

}

bool Engine::checkCollisionsForPlayer(Player::directions direction) {

	sf::Vector2f directionVector = mPlayer->getMoveStep();
	sf::Vector2f distanceToObject;
	sf::Vector2f acceptableDistance = sf::Vector2f(.5, .5);

	for each (Object o in mObjectMap)
	{
		if (o.isCrossable()) continue;
		//else if ( Collision::AABB(mPlayer->getSprite(), o.getSprite(), directionVector)) {
		else if (Collision::AABB(mPlayer->getBoundingBox(), o.getBoundingBox(), directionVector)) {
			// Collision
			if (Collision::getCollisionDirection(*mPlayer, o, direction)) {
				//distanceToObject = Collision::distanceToObject(mPlayer->getSprite(), o.getSprite(), *mPlayer);
				distanceToObject = Collision::distanceToObject(mPlayer->getBoundingBox(), o.getBoundingBox());
				if (
					(sqrt(pow(distanceToObject.x, 2) > pow(acceptableDistance.x, 2)))
					&&
					(sqrt(pow(distanceToObject.y, 2) > pow(acceptableDistance.y, 2)))
					) {
						mPlayer->setPosition( distanceToObject + mPlayer->getPosition() );
				}
					
				return true;
			}
			else {
				if (!mPlayer->getAuthorizedDirections().at(direction))
					return false;
			}
		}
	}
	return false;
}

void Engine::updatePlayerMovementFreedom()
{
	if (checkCollisionsForPlayer(Player::directions::UP)) {
		mPlayer->forbidDirection(Player::directions::UP);
		mPlayer->resetVerticalSpeed();
	} else {
		mPlayer->authorizeDirection(Player::directions::UP);
	} // UP

	if (checkCollisionsForPlayer(Player::directions::DOWN)) {
		if (mPlayer->isInAir()) {
			mPlayer->setInAir(false);
			mPlayer->resetVerticalSpeed();
		}
		mPlayer->forbidDirection(Player::directions::DOWN);

	} else {
		mPlayer->authorizeDirection(Player::directions::DOWN);
		mPlayer->setInAir(true);
	} // COLLIDE DOWN

	if (checkCollisionsForPlayer(Player::directions::LEFT)) {
		if (mPlayer->getAuthorizedDirections().at(Player::directions::LEFT)) {
			mPlayer->forbidDirection(Player::directions::LEFT);
			mPlayer->resetHorizontalSpeed();
		}
	} else {
		mPlayer->authorizeDirection(Player::directions::LEFT);
	} // LEFT

	if (checkCollisionsForPlayer(Player::directions::RIGHT)) {
		if (mPlayer->getAuthorizedDirections().at(Player::directions::RIGHT)) {
			mPlayer->forbidDirection(Player::directions::RIGHT);
			mPlayer->resetHorizontalSpeed();
		}
	} else {
		mPlayer->authorizeDirection(Player::directions::RIGHT);
	} // RIGHT

}

void Engine::updateInputs() {

	if ( mPlayer == NULL ) return;

	updatePlayerMovementFreedom();
	bool playerIsActive = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (mPlayer->isInAir()) return;
		mPlayer->move(Player::directions::UP);
		_keyEvents["UP"] = true;
		playerIsActive = true;
	}
	else {
		_keyEvents["UP"] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if ( mPlayer->isInAir() ) return; // Prevent multiple jumps
		mPlayer->move(Player::directions::UP);
		_keyEvents["UP"] = true;
		playerIsActive = true;
	}
	else {
		_keyEvents["UP"] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		mPlayer->move(Player::directions::LEFT);
		_keyEvents["LEFT"] = true;
		playerIsActive = true;
	}
	else {
		_keyEvents["LEFT"] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		mPlayer->move(Player::directions::DOWN);
		_keyEvents["DOWN"] = true;
		playerIsActive = true;
	}
	else {
		_keyEvents["DOWN"] = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		mPlayer->move(Player::directions::RIGHT);
		_keyEvents["RIGHT"] = true;
		playerIsActive = true;
	}
	else {
		_keyEvents["RIGHT"] = false;
	}

	if (!playerIsActive) {
		mCurrentPlayerStatus = PlayerStatuses::IDLE;
	}
	else {
		mCurrentPlayerStatus = PlayerStatuses::MOVING;
	}
		
}
void Engine::update() {

	_pLOG_->logActor(*mPlayer);
	mPlayer->updateBoundingBox();
	updatePlayerMovementFreedom(); // updateInputs would more appropriate
	
	mPlayer->updateBoundingBox();
	
	updatePhysics(); // Update physic of the game
	updateCamera(); // update the camera position
	
}

/**
 Should it be a rectangle ? Right now we offsetting the camera on the hero sprite
*/
void Engine::updateCamera() {
		sf::Vector2f offset = mPlayer->getMoveStep();
		_camera->updateView(offset);
}

void Engine::updateGraphics()
{
	// ANIMATE
	for (ActorAnimationManager* am : _ActorAnimationMap) {
		sf::Sprite* updatedSprite = am->ping(mPlayer->getSTATE(), *tm);
		if (updatedSprite == nullptr) continue;
		mPlayer->setSprite(*updatedSprite);
	}

}

void Engine::updatePhysics()
{
	if (mCurrentPlayerStatus == IDLE) {
		mPlayer->decelerate();
	}

	//updatePlayerMovementFreedom();

	sf::Vector2f newPosition = sf::Vector2f();
	for each (Object o in mObjectMap)
	{
		if (o.isSensibleToGravity())
		{
			newPosition = Physics::applyGravity(o.getPosition());
			o.setPosition(newPosition);
		}
	}

	if (  mPlayer->isInAir() ) {
		Physics::applyGravityToActor(*mPlayer);
	}

	mPlayer->updatePosition();
	mPlayer->updateState();
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
	_pLOG_ = new Log();
	tm = TextureManager::Instance();

	_keyEvents["UP"]   = false;
	_keyEvents["DOWN"] = false;
	_keyEvents["LEFT"] = false;
	_keyEvents["RIGH"] = false;

	initActors();
	initMap();
}


Engine::~Engine()
{
	delete _pLOG_;
	cout << " Stopping the Engine.... " << endl;
}