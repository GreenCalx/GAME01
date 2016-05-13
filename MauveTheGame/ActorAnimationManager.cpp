#include "ActorAnimationManager.h"


const int ACTOR_ROW_SIZE = 100;
const int ACTOR_COL_SIZE = 50;
 
#define validateRows(A) (A)%(ACTOR_ROW_SIZE)
#define validateCols(A) (A)%(ACTOR_COL_SIZE)

ActorAnimationManager::ActorAnimationManager(Actor* actor, TextureManager* tm)
{
	attachedActor = actor;
	actorState = Actor::IDLE_RIGHT;
	n_rowSprites = 0;
	if (0 > splitTexture(*tm)) {
		std::cout << "E00A1 : Impossible to split the Texture in ActorAnimationManager." << std::endl;
	}
}


ActorAnimationManager::~ActorAnimationManager()
{
}

sf::Sprite* ActorAnimationManager::ping(Actor::__STATE pState, TextureManager& tm) {
	if (NULL == attachedActor) return nullptr;
	if (pState != actorState) {
		actorState = pState;
		positionCounter = 0;
		currentSprites->clear();
		int retcode = 0;
		if (0 > (retcode =splitTexture(tm))) {
			std::cout << "E00A1 : Impossible to split the Texture in ActorAnimationManager." << std::endl;
			if (retcode == -2) std::cout << "::DIMENSION ISSUES" << std::endl;
		}
	}
	else {
		if (++positionCounter >= n_colSprites)
			positionCounter = 0;
	}
	sf::Sprite* retSprite = currentSprites->at(positionCounter);
	if (nullptr == retSprite) return nullptr;
	return retSprite;
}
int ActorAnimationManager::splitTexture(TextureManager& tm) {
	sf::Texture* t;
	t = tm.getTexture(attachedActor->getTextureLabel());
	tm.getTexture(attachedActor->getTextureLabel());
	// CHECK SIZE X,Y
	int width  =	t->getSize().x;
	int height =	t->getSize().y;

	if (!validateCols(width) || !validateRows(height)) return -2;

	n_rowSprites = height / ACTOR_ROW_SIZE;
	n_colSprites = width / ACTOR_COL_SIZE;

	int row = static_cast<int>(actorState) ;
	int col = positionCounter;
	if ( row > n_rowSprites ) return -1;

	int coor_y = row* ACTOR_ROW_SIZE;
	for (int i_sprite = 0; i_sprite < n_colSprites; ++i_sprite) {
		int coor_x = ACTOR_COL_SIZE*i_sprite;
		sf::IntRect splitter = sf::IntRect(coor_x, coor_y, ACTOR_COL_SIZE,  ACTOR_ROW_SIZE);
		sf::Sprite *s = new Sprite(*t, splitter);
		if (nullptr == s) return -1;
		currentSprites->push_back(s);
	
	}

	return 1;
}