#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Object.h"
#include <string.h>
#include <sstream>
#include "Map.h"
/* SCREEN SIZE */
static const float  __SCREEN_WIDTH = 800.0;
static const float	__SCREEN_HEIGHT = 600.0;

class Utils
{

public:

	static sf::Vector2f unarizedVector(sf::Vector2f v);
	static void quickSort(std::vector<Object*>& v, int p, int q);
	static void quickSort(std::vector<pair<int,int>>& v, int parToCompare, int p, int q);
	// PARSER
	static int mapParser(shared_ptr<Map>& ioMap, std::string _FILENAME_);
	static int fillTestMap(std::string _FILENAME_);

private:

	static int quickSortPartition(std::vector<Object*>& v, int p, int q);
	static int quickSortPartition(std::vector<pair<int, int>>& v, int parToCompare, int p, int q);

public:
	Utils();
	~Utils();
};	

