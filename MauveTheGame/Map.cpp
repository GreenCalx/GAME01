#include "Map.h"

#define validateRows(A) (A)%(TILE_SIZE)
#define validateCols(A) (A)%(TILE_SIZE)

const int TILE_SIZE = 32;

Map::Map()
{
	_mapGrid = make_unique<vector<vector<int>>>();
}

Map::Map(int mapWidth, int mapHeight) 
{
	__mapWidth	= mapWidth;
	__mapHeight = mapHeight;
	_mapGrid = make_unique<vector<vector<int>>>();
}

void Map::initializeMap() {
	_tilesSprites.clear();
	_mapGrid->clear();

	_mapSize = __mapWidth * __mapHeight;
	//_tilesSprites.resize(_mapSize);
	_mapGrid->resize(__mapHeight);
	for (int i = 0; i < __mapHeight; ++i) {
		_mapGrid->at(i).resize(__mapWidth);
		_mapGrid->at(i).assign(__mapWidth, 0);
	}
}

void Map::buildMap(TextureManager& tm)
{
	int ret = splitTexture(tm);
	if (ret < 0) {
		cout << " BUILD MAP ERROR : " << ret << endl;
		return;
	}
	// Establish correspondence between map and tiles in memory
	int i = 0, j = 0, globalcpt = 0;
	for (i = 0; i < __mapWidth; ++i) {
		for (j = 0; j < __mapHeight; ++j) {

			// Retrieve associated cell
			MC* c = getPtrOnCellFromIndex( _mapGrid->at(j).at(i) );
			if (c == nullptr) continue; // NULL CELL DETECTED
			Sprite* s = c->getSprite();
			_tilesSprites.push_back(new Sprite(*s));
			_tilesSprites[globalcpt]->setPosition(i*TILE_SIZE, j*TILE_SIZE);
			if (nullptr == s) continue;
			globalcpt++;
		} // EoL cols
	} // EoL rows
	cout << " MAP BUILT. " << endl;
	notifyChange();
}

Map::MC* Map::getPtrOnCell(const int x, const int y) {
	int i_cell = (y*__mapWidth) + x;
	return _grid.at(i_cell).get(); // ERROR LOG
}

Map::MC* Map::getPtrOnCellFromIndex(const int i)
{
	return _grid.at(i).get();
}

//int Map::setCell(int xc, int yc, int tx, int ty)
//{
//	MC* c = getPtrOnCell(xc, yc);
//	c->_x = tx;
//	c->_y = ty;
//	return xc + yc;
//}


int Map::splitTexture(TextureManager & tm)
{
	sf::Texture* t;
	t = tm.getTexture(__mapName);
	// CHECK SIZE X,Y
	int twidth = t->getSize().x;
	int theight = t->getSize().y;

	if (!validateCols(twidth) || !validateRows(theight)) return -2; // Invalid tileset format

	int n_rowCells = twidth / TILE_SIZE;
	int n_colCells = theight / TILE_SIZE;
	
	// Load each tile in memory
	for (int i_rcell = 0; i_rcell < n_rowCells; ++i_rcell) {
		for (int i_ccell = 0; i_ccell < n_colCells; ++i_ccell) {
			_grid.push_back(make_unique<mapCell>(i_rcell+i_ccell));
			pMC& c = _grid.back();
			if (c == nullptr) return -3; // NULL CELL DETECTED
			int coor_x = i_rcell*TILE_SIZE, coor_y = i_ccell * TILE_SIZE;
			sf::IntRect splitter = sf::IntRect(coor_x, coor_y,  TILE_SIZE,  TILE_SIZE);
			sf::Sprite *s = new Sprite(*t, splitter);
			c->setSprite(s);
		} // col cell
	} // row cell
	return 1;
}


//void Map::attributeTile(int x, int y, int id)
//{
//	this->_mapGrid.at(y).at(x) = id;
//}

//void Map::DBG_printMapCells() {
//	//std::copy(_mapGrid.begin(), _mapGrid.end(), ostream_iterator<mapCell>(cout, " "));
//	for (int i = 0; i < _mapSize; ++i) {
//		std::cout << _grid.at(i).get()->_x << " ; " << _grid.at(i).get()->_y << endl;
//	}
//		
//}


Map::~Map()
{
}
