#include "Map.h"

#define validateRows(A) (A)%(TILE_SIZE)
#define validateCols(A) (A)%(TILE_SIZE)

const int TILE_SIZE = 32;

Map::Map()
{
	initializeMap();
}

Map::Map(int mapWidth, int mapHeight) 
{
	__mapWidth	= mapWidth;
	__mapHeight = mapHeight;
	initializeMap();
}

void Map::initializeMap() {
	_mapSize = __mapWidth * __mapHeight;
	for (int i = 0; i < _mapSize; ++i) {
		_grid.push_back(make_unique<mapCell>());
	}
	
}

void Map::buildMap(TextureManager& tm)
{
	//__tileSetManager = make_unique<TileSetManager>(this);
	//if (__tileSetManager == nullptr) cout << " __TileSetManager Issue" << endl;
	//int ret = __tileSetManager.get()->splitTexture(tm);
	int ret = splitTexture(tm);
	if (ret < 0) {
		cout << " BUILD MAP ERROR : " << ret << endl;
		return;
	}
}

Map::MC* Map::getPtrOnCell(const int x, const int y) {
	int i_cell = (y*__mapWidth) + x;
	return _grid.at(i_cell).get(); // ERROR LOG
}

Map::MC* Map::getPtrOnCellFromIndex(const int i)
{
	return _grid.at(i).get();
}

int Map::setCell(int xc, int yc, int tx, int ty)
{
	MC* c = getPtrOnCell(xc, yc);
	c->_x = tx;
	c->_y = ty;
	return xc+yc;
}


int Map::splitTexture(TextureManager & tm)
{
	sf::Texture* t;
	t = tm.getTexture(__mapName);
	// CHECK SIZE X,Y
	int twidth = t->getSize().x;
	int theight = t->getSize().y;

	if (!validateCols(twidth) || !validateRows(theight)) return -2; // Invalid tileset format

	int n_rowCells = twidth / __mapWidth;
	int n_colCells = theight / __mapHeight;

	int i = 0, j = 0;
	for (i = 0; i < __mapWidth; ++i) {
		for (j = 0; j < __mapHeight; ++j) {
			MC* c = getPtrOnCell(i, j);
			if (c == nullptr) return -3; // NULL CELL DETECTED
			int coor_x = c->_x * TILE_SIZE, coor_y = c->_y * TILE_SIZE;
			sf::IntRect splitter = sf::IntRect(coor_x, coor_y, coor_x + TILE_SIZE, coor_y + TILE_SIZE);
			sf::Sprite *s = new Sprite(*t, splitter);
			s->setPosition(i*TILE_SIZE, j*TILE_SIZE);
			if (nullptr == s) return -1;
			// ADD A BETTER MATRIX
			//currentSprites->push_back(s);
			c->setSprite(s);
		} // EoL cols
	} // EoL rows

	return 1;
}


void Map::DBG_printMapCells() {
	//std::copy(_mapGrid.begin(), _mapGrid.end(), ostream_iterator<mapCell>(cout, " "));
	for (int i = 0; i < _mapSize; ++i) {
		std::cout << _grid.at(i).get()->_x << " ; " << _grid.at(i).get()->_y << endl;
	}
		
}


Map::~Map()
{
}
