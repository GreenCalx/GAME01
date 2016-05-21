//#include "TileSetManager.h"
//
//#include "Map.h"
//
//
//#define validateRows(A) (A)%(TILE_SIZE)
//#define validateCols(A) (A)%(TILE_SIZE)
//
//int TileSetManager::splitTexture(TextureManager & tm)
//{
//	sf::Texture* t;
//	t = tm.getTexture(_map->getMapName());
//	// CHECK SIZE X,Y
//	int twidth = t->getSize().x;
//	int theight = t->getSize().y;
//
//	if (!validateCols(twidth) || !validateRows(theight)) return -2; // Invalid tileset format
//
//
//	int mapWidth	= _map->getWidth();
//	int mapHeight	= _map->getHeight();
//	int n_rowCells	= twidth / mapWidth;
//	int n_colCells	= theight / mapHeight;
//
//	int i = 0, j = 0;
//	for (i = 0; i < mapWidth; ++i) {
//		for (j = 0; j < mapHeight; ++j) {
//			Map::mapCell* c = _map->getPtrOnCell(i, j);
//			if (c == nullptr) return -3; // NULL CELL DETECTED
//			int coor_x = c->_x * TILE_SIZE, coor_y = c->_y * TILE_SIZE;
//			sf::IntRect splitter = sf::IntRect(coor_x, coor_y, coor_x + TILE_SIZE, coor_y + TILE_SIZE);
//			sf::Sprite *s = new Sprite(*t, splitter);
//			if (nullptr == s) return -1;
//			// ADD A BETTER MATRIX
//			//currentSprites->push_back(s);
//			c->setSprite(s);
//		} // EoL cols
//	} // EoL rows
//	
//	return 1;
//}
//
//sf::Sprite * TileSetManager::ping(TextureManager & tm)
//{
//	/* TODO : TO IMPLEMENT TO FINISH ANIMATION TILE */
//	return nullptr;
//}
//
//TileSetManager::TileSetManager(Map* map) : _map(map)
//{
//}
//
//
//TileSetManager::~TileSetManager()
//{
//
//}
