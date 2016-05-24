#include "Collision.h"
#include "Utils.h"
#include "Map.h"

Collision::Collision() {
}

bool Collision::AABB(const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, sf::Vector2f moveToExecuteForSprite1) {

	sf::FloatRect boundingBox1 = pSprite1.getGlobalBounds();

	boundingBox1.left += moveToExecuteForSprite1.x;
	boundingBox1.top  += moveToExecuteForSprite1.y;
	boundingBox1.height += moveToExecuteForSprite1.y;
	boundingBox1.width += moveToExecuteForSprite1.x;

	sf::FloatRect boundingBox2 = pSprite2.getGlobalBounds();

	if (boundingBox1.intersects(boundingBox2)) {
		return true;
	}
	return false;
}

bool Collision::AABB(const sf::IntRect& bbo1, const sf::IntRect& bbo2, sf::Vector2f moveToExecuteForSprite1) {

	sf::IntRect boundingBox1 = bbo1;

	boundingBox1.left += moveToExecuteForSprite1.x;
	boundingBox1.top += moveToExecuteForSprite1.y;
	boundingBox1.height += moveToExecuteForSprite1.y;
	boundingBox1.width += moveToExecuteForSprite1.x;

	if (boundingBox1.intersects(bbo2)) {
		return true;
	}
	return false;
}

bool Collision::getCollisionDirection(Actor pMainActor, Object pCollidingObject, Player::directions direction)
{
	//assert objects are colliding.
	//float offset = 10;
	sf::FloatRect bbo = pCollidingObject.getSprite().getGlobalBounds();
	sf::FloatRect bba = pMainActor.getSprite().getGlobalBounds();
	sf::Vector2f vRelativePosition = pMainActor.getPosition() ;
	float vActorHead = pMainActor.getPosition().y;
	float vActorFeet = pMainActor.getPosition().y + bba.height;
	float vActorLeftArm = pMainActor.getPosition().x;
	float vActorRightArm = pMainActor.getPosition().x + bba.width;
	
	switch (direction) {
		case Player::directions::UP:
			vRelativePosition.y = vActorHead + (bbo.top - bbo.height);
			if (fabs(vRelativePosition.y) < COLLISION_ASSERTION) return true;
			break;
		case Player::directions::DOWN:
			vRelativePosition.y = bbo.top + vActorFeet;
			if (fabs(vRelativePosition.y) > COLLISION_ASSERTION) return true;
			break;
		case Player::directions::LEFT:
			vRelativePosition.x = vActorLeftArm - (bbo.left + bbo.width);
			if (fabs(vRelativePosition.x) < COLLISION_ASSERTION) return true;
			break;
		case Player::directions::RIGHT:
			vRelativePosition.x = bbo.left - vActorRightArm;
			if (fabs(vRelativePosition.x) < COLLISION_ASSERTION) return true;
			break;
		default :
			return true;
			break;
	}

	return false;
}

/**
Returns the maxium authorized movement to reach the second object.
We assume that the intersection is inevitable due to the Actor's speed.
**/
sf::Vector2f Collision::distanceToObject(const sf::Sprite& pSprite1, const sf::Sprite& pSprite2, Actor &pPlayer) {
	
	sf::FloatRect bbo1 = pSprite1.getGlobalBounds();
	sf::FloatRect bbo2 = pSprite2.getGlobalBounds();

	sf::Vector2f actorPosition = pPlayer.getPosition();
	sf::Vector2f distance;

	if (bbo1.left + bbo1.width > bbo2.left) // sprite1 left of sprite 2
		distance.x = bbo1.left + bbo1.width - bbo2.left ;
	else									// sprite1 right of sprite 2
		distance.x = bbo2.left + bbo2.width - bbo1.left;

	if (bbo1.top + bbo1.height < bbo2.top) // sprite1 top of sprite 2
		distance.y = bbo1.top + bbo1.height - bbo2.top;
	else									// sprite1 bottom of sprite 2
		distance.y = bbo2.top - ( bbo1.top + bbo1.height );

	if (distance.x < 0) {
		return sf::Vector2f();
	}
	if (distance.y < 0) {
		return sf::Vector2f();
	}

	//pPlayer.setPosition( actorPosition + distance );

	return distance;
}

sf::Vector2f Collision::distanceToObject(const sf::IntRect& bbo1, const sf::IntRect& bbo2) {
	sf::Vector2f distance;

	if (bbo1.left + bbo1.width > bbo2.left) // sprite1 left of sprite 2
		distance.x = bbo1.left + bbo1.width - bbo2.left;
	else									// sprite1 right of sprite 2
		distance.x = bbo2.left + bbo2.width - bbo1.left;

	if (bbo1.top + bbo1.height < bbo2.top) // sprite1 top of sprite 2
		distance.y = bbo1.top + bbo1.height - bbo2.top;
	else									// sprite1 bottom of sprite 2
		distance.y = bbo2.top - (bbo1.top + bbo1.height);

	if (distance.x < 0) {
		return sf::Vector2f();
	}
	if (distance.y < 0) {
		return sf::Vector2f();
	}

	return distance;
}

bool Collision::collideCameraViewZone(const sf::Rect<float> viewZone, const sf::Sprite& pSprite1, sf::Vector2f moveToExecute)
{
	sf::FloatRect bb1 = pSprite1.getGlobalBounds();

	bb1.left += moveToExecute.x;
	bb1.top += moveToExecute.y;
	bb1.height += moveToExecute.y;
	bb1.width += moveToExecute.x;

	if (bb1.left + bb1.width > viewZone.left) { // Left of viewzone
		return true;
	}
	else if (bb1.left + bb1.width > viewZone.left + viewZone.width) { // right of viewzone
		return true;
	}
	
	if (bb1.top + bb1.height < viewZone.top) { // Top of viewzone
		return true;
	}
	else if (bb1.top + bb1.height < viewZone.top + viewZone.height) {
		return true;
	}

	return false;
}

int Collision::ActorCollisionWithMapGrid(Map * iMap, Actor * iActor)
{
	// Init BBox values
	// ------------------
	sf::IntRect& actorBB = iActor->getBoundingBox();
	int actorWidth	= actorBB.width;
	int actorHeight	= actorBB.height;
	int leftBB		= actorBB.left;
	int rightBB		= leftBB + actorWidth;
	int topBB		= actorBB.top;
	int downBB		= topBB + actorHeight;

	// Get Actor movements
	// ---------------------
	int xActor = iActor->getMoveStep().x;
	int yActor = iActor->getMoveStep().y;
	int leftBBAfterMove		= xActor + leftBB;
	int rightBBAfterMove	= xActor + rightBB;
	int topBBAfterMove		= yActor + topBB;
	int downBBAfterMove		= yActor + downBB;

	// Handle X Movement first [ left / right ]
	// -------------------------
	sf::Vector2f playerMovement = iActor->getMoveStep();
	int retval = -1;
	Line edgeAfterMove	= Line();
	Line edgeBeforeMove = Line();
	vector<pair<int, int>> collidingTilesOnX = vector<pair<int, int>>();
	vector<pair<int, int>> collidingTilesOnY = vector<pair<int, int>>();

	Line collidingEdgeOnX = Line();
	Line collidingEdgeOnY = Line();

	if (xActor > 0) {
		// Moving Right
			// Retrieve Right Edge
		edgeAfterMove.setP1( rightBBAfterMove, topBBAfterMove);
		edgeAfterMove.setP2( rightBBAfterMove, downBBAfterMove);

		edgeBeforeMove.setP1(rightBB, topBB);
		edgeBeforeMove.setP2(rightBB, downBB);
		
		collidingTilesOnX = collisionBetweenXLineAndGrid(iMap, edgeBeforeMove, edgeAfterMove);
		
		if (collidingTilesOnX.size() > 0) {
			playerMovement.x = std::floor( rightBBAfterMove - collidingTilesOnX[0].first*iMap->TILE_SIZE);
			iActor->forbidDirection(Actor::RIGHT);
		}
	}
	else if ( xActor < 0 ) {
		// Moving Left
			// Retrieve Right Edge
		edgeAfterMove.setP1(leftBBAfterMove, topBBAfterMove);
		edgeAfterMove.setP2(leftBBAfterMove, downBBAfterMove);

		edgeBeforeMove.setP1(leftBB, topBB);
		edgeBeforeMove.setP2(leftBB, downBB);

		collidingTilesOnX = collisionBetweenXLineAndGrid( iMap, edgeBeforeMove, edgeAfterMove);
	
		// Treat colliding tiles in X axe
		if (collidingTilesOnX.size() > 0) {
			playerMovement.x = std::floor( leftBBAfterMove + collidingTilesOnX[0].first*iMap->TILE_SIZE);
			
		}
	}




	// Handle Y Movement first [ left / right ]
	// -------------------------
	if (yActor > 0) {
		// Moving Down
		// Retrieve Down Edge
		edgeAfterMove.setP1(leftBBAfterMove, downBBAfterMove);
		edgeAfterMove.setP2(rightBBAfterMove, downBBAfterMove);

		edgeBeforeMove.setP1(leftBB, downBB);
		edgeBeforeMove.setP2(rightBB, downBB);

		collidingTilesOnY = collisionBetweenYLineAndGrid(iMap, edgeBeforeMove, edgeAfterMove);

		if (collidingTilesOnY.size() > 0) {
			playerMovement.y = std::floor(downBBAfterMove - collidingTilesOnY[0].second*iMap->TILE_SIZE);
			iActor->forbidDirection(Actor::UP);
		}

	}
	else if (yActor < 0) {
		// Moving Up
		// Retrieve Down Edge
		edgeAfterMove.setP1(leftBBAfterMove, downBBAfterMove);
		edgeAfterMove.setP2(rightBBAfterMove, downBBAfterMove);

		edgeBeforeMove.setP1(leftBB, downBB);
		edgeBeforeMove.setP2(rightBB, downBB);

		collidingTilesOnY = collisionBetweenYLineAndGrid(iMap, edgeBeforeMove, edgeAfterMove);
	
		if (collidingTilesOnY.size() > 0) {
			playerMovement.y = std::floor(topBBAfterMove + collidingTilesOnY[0].second*iMap->TILE_SIZE);
			iActor->forbidDirection(Actor::DOWN);
		}

	}

	// Move the player if needed
	iActor->setCurrentMoveStep(playerMovement);

	// Return collision state
	return 0;
}

vector<pair<int, int>> Collision::collisionBetweenXLineAndGrid(Map* iMap, Line& iEdgeBeforeMove, Line& iEdgeAfterMove)
{
	// Get intersecting tiles
	// ------------------------------
	Line& ebm = iEdgeBeforeMove;
	Line& eam = iEdgeAfterMove;

	//Retrieve set of tiles around the actor
	vector<pair<int, int>>& neighborhoodTiles = iMap->getTilesAroundCoordinates(iEdgeAfterMove.p1.x, iEdgeAfterMove.p1.y, 2);
	vector<pair<int, int>> intersectingTiles = vector<pair<int, int>>();
	sf::IntRect tileRect = sf::IntRect();
	for (auto pair : neighborhoodTiles) {
		int tileX = pair.first * iMap->TILE_SIZE;
		int tileY = pair.second * iMap->TILE_SIZE;
		tileRect = sf::IntRect(tileX, tileY, tileX + iMap->TILE_SIZE, tileY + iMap->TILE_SIZE);
		if (eam.intersectsX(tileRect)) {
			intersectingTiles.push_back(pair);
			//cout << " Tile at : "<< pair.first << ":" << pair.second << endl;
		}
	}
	//if (!intersectingTiles.empty())
		//cout << " Intersecting " << intersectingTiles.size() << endl;

	
	// Scan along the row of the tile in the right propagation direction

	// When we collide, check if the tile's X is superior to the x after actor's movement
	vector<pair<int, int>>  collidingTiles;
	for (auto pair : intersectingTiles) {
		int cellId = iMap->getTileCellID(pair.first, pair.second);
		if (cellId < 0) continue;
		if (!iMap->cellExists(cellId)) continue;
		if (!iMap->getPtrOnCellFromCellID(cellId)->getIsCrossable()) {
			// COLLIDE
			//cout << " COLLIDE " << endl;
			collidingTiles.push_back(pair);
		}
	}
		// If so, no collision return 0
	if (0 == collidingTiles.size()) return collidingTiles;
		// If collision, then Compute minimal distance to the intersecting tile
			// Move the player accordingly
			// Reset X Speed


	// Get Closest collidingTiles
	vector<pair<int, int>> closestCollidingTiles = vector<pair<int, int>>();
	Utils::quickSort(collidingTiles, 0, 0, collidingTiles.size());
	int minX = collidingTiles[0].first;
	for (auto p : collidingTiles)
		if (p.first == minX)
			closestCollidingTiles.push_back(p);

	// 0 : NoCollide ; 1 : Collide
	return closestCollidingTiles;
}

vector<pair<int, int>> Collision::collisionBetweenYLineAndGrid(Map * iMap, Line& iEdgeBeforeMove, Line& iEdgeAfterMove)
{
	// Get intersecting tiles
	// ------------------------------
	Line& ebm = iEdgeBeforeMove;
	Line& eam = iEdgeAfterMove;

	//Retrieve set of tiles around the actor
	vector<pair<int, int>>& neighborhoodTiles = iMap->getTilesAroundCoordinates(iEdgeAfterMove.p1.x, iEdgeAfterMove.p1.y, 2);
	vector<pair<int, int>> intersectingTiles = vector<pair<int, int>>();
	sf::IntRect tileRect = sf::IntRect();
	for (auto pair : neighborhoodTiles) {
		int tileX = pair.first * iMap->TILE_SIZE;
		int tileY = pair.second * iMap->TILE_SIZE;
		tileRect = sf::IntRect(tileX, tileY, tileX + iMap->TILE_SIZE, tileY + iMap->TILE_SIZE);
		if (eam.intersectsX(tileRect)) {
			intersectingTiles.push_back(pair);
			//cout << " Tile at : " << pair.first << ":" << pair.second << endl;
		}
	}
	//if (!intersectingTiles.empty())
		//cout << " Intersecting " << intersectingTiles.size() << endl;
	
	
	// Scan along the col of the tile in the right propagation direction

	// When we collide, check if the tile's Y is superior to the x after actor's movement
	// If so, no collision return 0
	vector<pair<int, int>>  collidingTiles;
	for (auto pair : intersectingTiles) {
		int cellId = iMap->getTileCellID(pair.first, pair.second);
		if (!iMap->cellExists(cellId)) continue;
		if (!iMap->getPtrOnCellFromCellID(cellId)->getIsCrossable()) {
			// COLLIDE
			//cout << " COLLIDE " << endl;
			collidingTiles.push_back(pair);
		}
	}
	if (collidingTiles.size() == 0) return collidingTiles;

	// If collision, then Compute minimal distance to the intersecting tile
	// Move the player accordingly
	// Reset X Speed

	// Get Closest collidingTiles
	vector<pair<int,int>> closestCollidingTiles = vector<pair<int, int>>();
	Utils::quickSort(collidingTiles, 1, 0, collidingTiles.size());
	int minY = collidingTiles[0].second;
	for (auto p : collidingTiles)
		if (p.second == minY)
			closestCollidingTiles.push_back(p);

	// 0 : NoCollide ; 1 : Collide
	return closestCollidingTiles;
}


Collision::~Collision() {
}
