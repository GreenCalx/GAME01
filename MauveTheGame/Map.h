#pragma once
#include "Object.h"
#include <memory>
#include <vector>
#include <iterator>
//#include "TileSetManager.h"

class Map
{
public:

	struct mapCell {
		int _x , _y ;
		vector<pair<int,int>> animatedTileCoordinates;
		pair<int, int> animationCounter;
		sf::Sprite* tileSprite;
		sf::Sprite* getSprite() { return tileSprite;}
		void setSprite(sf::Sprite* s) { tileSprite = s; }
		mapCell() { _x = -1; _y = -1; }
		mapCell(vector<pair<int, int>> pAnimatedTileCoordinates) 
		{
			_x = -1; 
			_y = -1; 
			animatedTileCoordinates = pAnimatedTileCoordinates; 
			animationCounter = make_pair(0, animatedTileCoordinates.size());
		}
		pair<int, int> getAnimationCounter() {
			return animationCounter;
		};
		bool updateAnimatedTileCoordinates() {
			int countValue = animationCounter.first;
			_x = animatedTileCoordinates.at(countValue).first;
			_y = animatedTileCoordinates.at(countValue).second;
			animationCounter.first = countValue + 1;
			if (countValue >= animationCounter.second) 
				animationCounter.first = 0;
		}
	} typedef MC;

	typedef unique_ptr<mapCell> pMC;
	mapCell makeMapCell() { return mapCell(); };

public:
	Map();
	Map(int mapWidth, int mapHeight);
	~Map();

	void buildMap(TextureManager& tm);
	MC* getPtrOnCell(const int x, const int y);
	MC* getPtrOnCellFromIndex(const int i);
	//MC&  getCell(const int x, const int y);
	void initializeMap();
	int setCell(int xc, int yc, int tx, int ty);

	void DBG_printMapCells();

	int getHeight(void) { return __mapHeight; }
	void setHeight(int height) { __mapHeight = height; }
	int getWidth(void) { return __mapWidth; }
	void setWidth(int width) { __mapWidth = width; }
	string getMapSet(void) { return __mapSet; }
	void setMapSet(string mapset) {
		__mapSet = mapset; __mapSetPath = "Resources/Sprites/TileSet/" + mapset + ".png" ;
	}
	string getMapName(void) { return __mapName; }
	void setMapName(string mapName) { __mapName = mapName; }
	string getMapSetPath(void) { return __mapSetPath; }

	//TileSetManager* getTileSetManager() { return __tileSetManager.get(); }
	int splitTexture(TextureManager & tm);
private:
	

	
private :
	String				_name;
	vector<Object>		_mapObjects;

	vector<pMC> _grid;
	vector<MC>	_mapGrid;
	int __mapHeight = 20;
	int __mapWidth = 20;
	int _mapSize = 400;
	string __mapName = "";
	
	string __mapSet  = "";
	string __mapSetPath = "";
	
//	unique_ptr<TileSetManager> __tileSetManager;
public :
	static const int TILE_SIZE		= 32;

};

