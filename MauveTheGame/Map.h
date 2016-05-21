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
		//int _x , _y ;
		int __ID;
		//vector<int> animatedTileCoordinates;
		//pair<int, int> animationCounter;
		sf::Sprite* tileSprite;
		sf::Sprite* getSprite() { return tileSprite;}
		void setSprite(sf::Sprite* s) { tileSprite = s; }
		mapCell(int id) : __ID(id) {  }
		/*mapCell(vector<pair<int, int>> pAnimatedTileCoordinates) 
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
		}*/
	} typedef MC;

	typedef unique_ptr<mapCell> pMC;

public:
	Map();
	Map(int mapWidth, int mapHeight);
	~Map();

	void buildMap(TextureManager& tm);
	MC* getPtrOnCell(const int x, const int y);
	MC* getPtrOnCellFromIndex(const int i);

	void initializeMap();

	void attributeTile(int x, int y, int id) {
		_mapGrid->at(y).at(x) = id;
	};
	int getTileCellID(int x, int y) {
		return _mapGrid->at(y).at(x);
	}

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
	vector<sf::Sprite*>& getTileSpriteSet(void) { return _tilesSprites; }

	//TileSetManager* getTileSetManager() { return __tileSetManager.get(); }
	int splitTexture(TextureManager & tm);

	bool getHasChanged(void) { return hasChanged; }
	void notifyChange(void) { hasChanged = true; }
	void hasBeenUpdated(void) { hasChanged = false; }
private:
	

	
private :
	String				_name;
	vector<Object>		_mapObjects;

	vector<pMC> _grid; // array of unique tiles
	unique_ptr<vector<vector<int>>>	_mapGrid; // actual map
	vector<sf::Sprite*>		_tilesSprites;
	int __mapHeight = 20;
	int __mapWidth = 20;
	int _mapSize = 400;
	string __mapName = "";
	
	string __mapSet  = "";
	string __mapSetPath = "";
	
	bool hasChanged = false;
//	unique_ptr<TileSetManager> __tileSetManager;
public :
	static const int TILE_SIZE		= 32;

};

