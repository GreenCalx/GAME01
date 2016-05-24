#include "Map.h"

#define validateRows(A) (A)%(TILE_SIZE)
#define validateCols(A) (A)%(TILE_SIZE)

const int TILE_SIZE = 64;

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
	_tilesSprites.resize(_mapSize);
	_mapGrid->resize(__mapHeight);
	for (int i = 0; i < __mapHeight; ++i) {
		_mapGrid->at(i).resize(__mapWidth);
		_mapGrid->at(i).assign(__mapWidth, 0);
	}
}

void Map::setCellProperties(int id, bool isCrossable)
{
	MC* c = getPtrOnCellFromCellID(id);
	if (c == nullptr) return;
	c->setIsCrossable(isCrossable);
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
	for (j = 0; j < __mapHeight; ++j) {
		for (i = 0; i < __mapWidth; ++i) {

			// Retrieve associated cell
			MC* c = getPtrOnCellFromCellID( _mapGrid->at(j).at(i) );
			if (c == nullptr) continue; // NULL CELL DETECTED
			if (c->__ID == 0) continue; // Empty tile
			Sprite* s = c->getSprite();
			if (nullptr == s) continue;
			//_tilesSprites.push_back(new Sprite(*s));
			_tilesSprites[globalcpt] = new Sprite(*s);
			_tilesSprites[globalcpt]->setPosition(i*TILE_SIZE, j*TILE_SIZE);
			if (globalcpt == 200 || globalcpt == 220)
				cout << "HELLO" << endl;

			globalcpt++;
		} // EoL cols
	} // EoL rows
	if (globalcpt != _tilesSprites.size()) cout << " An issue occured while building the map " << endl;
	cout << " MAP BUILT. " << endl;
	notifyChange();
}

Map::MC* Map::getPtrOnCell(const int x, const int y) {
	int i_cell = (y*__mapWidth) + x;
	return _grid.at(i_cell).get(); // ERROR LOG
}

Map::MC* Map::getPtrOnCellFromIndex(const int i)
{
	MC* c = _grid[i].get();
	return c;
}

Map::MC* Map::getPtrOnCellFromCellID(const int id)
{
	MC* c = nullptr;
	for (unsigned int i_c = 0; i_c < _grid.size(); ++i_c) {
		if (id == _grid[i_c]->__ID) {
			c = _grid[i_c].get(); break;
		}
	}
	return c;
}

bool Map::cellExists(const int i)
{
	if (_grid.empty()) return false;

	for (int i_c = 0; i_c < _grid.size(); ++i_c) {
		if (_grid[i_c]->__ID == i) return true;
	}
	return false;
}

int Map::makeCell(int id)
{
	this->_grid.push_back( make_unique<mapCell>(id) );
	return 1;
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
			MC* c = getPtrOnCellFromIndex(i_rcell + i_ccell);
			if (c == nullptr) return -3; // NULL CELL DETECTED
			int coor_x = i_rcell*TILE_SIZE, coor_y = i_ccell * TILE_SIZE;
			sf::IntRect splitter = sf::IntRect(coor_x, coor_y,  TILE_SIZE,  TILE_SIZE);
			sf::Sprite *s = new Sprite(*t, splitter);
			c->setSprite(s);
		} // col cell
	} // row cell
	return 1;
}

vector<pair<int, int>> Map::getTilesAroundCoordinates(const int x, const int y, const int range)
{
	// Initialize values
	int adjustedX = x;
	int adjustedY = y;
	int offset = 0;

	vector<pair<int, int>> v = vector<pair<int, int>>();
	int vSize = 1;
	if ( range > 0 ) {
	for (int i_range = 1; i_range <= range ; ++i_range)
		vSize += std::pow(2, 2 + i_range);
	}
	v.resize(vSize);

	// Retrieve a fitting tile
	offset = x%TILE_SIZE;
	if (offset != 0) {
		// x is between tiles
		adjustedX -= offset;
	}

	offset = y%TILE_SIZE;
	if (offset != 0) {
		// y is between tiles
		adjustedY -= offset;
	}
	
	v.at(0) = pair<int, int>(adjustedX/TILE_SIZE, adjustedY/TILE_SIZE);

	if (range == 0) return v;
	int nLine = 2 * range;
	// Extend to range
	for (int j = 0; j <= nLine; ++j) {
		for (int i = 0; i <= nLine; ++i) {
			v.at(i + j) = pair<int, int>(adjustedX/TILE_SIZE + i, adjustedY/TILE_SIZE + j);
		}
	}
	return v;
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
