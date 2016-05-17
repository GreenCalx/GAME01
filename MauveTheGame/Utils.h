#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

/* SCREEN SIZE */
static const float  __SCREEN_WIDTH = 800.0;
static const float	__SCREEN_HEIGHT = 600.0;

class Utils
{
public:
	static sf::Vector2f unarizedVector(sf::Vector2f v);
	static void quickSort(std::vector<Object*>& v, int p, int q);
private:
	static int quickSortPartition(std::vector<Object*>& v, int p, int q);
public:
	Utils();
	~Utils();
};

