#pragma once
#include "Object.h"

class Map
{
public:
	Map();
	~Map();

	void buildMap();

private :
	String				_name;
	vector<Object>		_mapObjects;

};

