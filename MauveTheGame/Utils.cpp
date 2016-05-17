#include "Utils.h"

sf::Vector2f Utils::unarizedVector(sf::Vector2f v) {
	sf::Vector2f ret_v;
	ret_v.x  = -((v.x) / (v.x));
	ret_v.y  = -((v.y) / (v.y));
	return ret_v;
}

void Utils::quickSort(std::vector<Object*>& v, int p, int q) {
	int r = 1;
	if (p < q) {
		r = quickSortPartition(v, p, q);
		quickSort(v, p, r);
		quickSort(v, r + 1, q);
	}
}

int Utils::quickSortPartition(std::vector<Object*>& v, int p, int q) {
	int x = (v.at(p))->getZ();
	int i = p;
	for (int j = p + 1; j < q; ++j) {
		if ((v.at(j)->getZ()) <= x) {
			i = i + 1;
			std::swap(v.at(i), v.at(j));
		}
	}
	std::swap(v.at(i), v.at(p));
	return i;
}


Utils::Utils()
{
}


Utils::~Utils()
{
}
