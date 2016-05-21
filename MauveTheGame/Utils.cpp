#include "Utils.h"
#include "Map.h"

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


int Utils::mapParser(unique_ptr<Map>& ioMap, std::string _FILENAME_)
{
	if (_FILENAME_.empty()) return -1;

	std::string fullPath = "Resources/World/" + _FILENAME_ ;
	string line;
	std::ifstream mapFile;
	mapFile.open(fullPath);
	if (mapFile.is_open()) {

		

		int startTileToken = 0;
		int x_cell = 0, y_cell = 0;
		int tx = 0, ty = 0;

		while (std::getline(mapFile, line)) {

			if (line.empty()) continue;
			// TODO : FINIR LE PARSER , line marche pas faut apsser par data

			if (!startTileToken) {

				// MAP DESCRIPTION
				istringstream data_label(line);
				string label = data_label.str();
				cout << label << endl;
				if (0 == label.compare("#-")) {
					cout << "startTileToken" << endl;
					startTileToken = 1;

					// Prepare the map to be loaded
					ioMap->initializeMap();
					continue;
				}
				getline(mapFile, line);
				if (line.empty()) return -3; // Empty content for a given label
				istringstream data_content(line);



				// Proceed to analyze map file content
				if (0==label.compare("#MAPNAME")) {
					string s;
					data_content >> s;
					ioMap->setMapName(s);
					cout << ioMap->getMapName() << endl;
				}
				else if (0 == label.compare("#MAPSET")) {
					string s;
					data_content >> s;
					ioMap->setMapSet(s);
					cout << ioMap->getMapSet() << endl;
				}
				else if (0 == label.compare("#MAPWIDTH")) {
					int width = 1;
					data_content >> width;
					ioMap->setWidth(width);
					cout << ioMap->getWidth() << endl;
				}
				else if (0 == label.compare("#MAPHEIGHT")) {
					int height = 1;
					data_content >> height;
					ioMap->setHeight(height);
					cout << ioMap->getHeight() << endl;
				}
			}
			else {


				// MAP TILE DETAILS
				if ((ioMap->getWidth() == 0) || (ioMap->getHeight() == 0)) return -1; // BAD WIDTH ; HEIGHT
				istringstream data_tx(line);
				data_tx >> tx;


				getline(mapFile, line);
				istringstream data_ty(line);
				data_ty >> ty;


				/* define x_cell, y_cell if needed here*/

				ioMap->attributeTile(x_cell, y_cell, (tx + ty) );

				// Check tile separator
				getline(mapFile, line);
				istringstream data_sep(line);
				string s;
				s = data_sep.str();
				if (0 != s.compare("#.")) {
					cout << s << endl;
					mapFile.close();
					return -2; // TILE LOADING TOKEN ERROR
				}

				// Update cell coordinates
				x_cell += 1;
				if ( x_cell >= ioMap->getWidth() ) {
					y_cell += 1; x_cell = 0;
				}			

			}
		} // EoL more Lines
	}
	else { mapFile.close(); return -1; }
	
	mapFile.close();
	return 1;
}

int Utils::fillTestMap(std::string _FILENAME_) 
{
	if (_FILENAME_.empty()) return -1;
	std::string fullPath = "Resources/World/" + _FILENAME_;
	std::ofstream mapFile;
	mapFile.open(fullPath);
	if (mapFile.is_open()) {
		mapFile << "#MAPNAME\n";
		mapFile << "TEST_MAP";
		mapFile << "\n#MAPSET\n";
		mapFile << "TEST_MAP";
		mapFile << "\n#MAPWIDTH\n";
		mapFile << "101";
		mapFile << "\n#MAPHEIGHT\n";
		mapFile << "101";
		mapFile << "\n#-\n";
		int i_cpt = 1;
		int width = 101, height = 101;
		int size = width * height;
		int x = 0, y = 0;
		for (int i = 0; i < size; ++i) 
		{
			//if (i < 200) { x = 0; y = 0; }
			//else { x = 1; y = 0; }
			x = ( i % 2 ) ? 0 : 1;
			mapFile << x << '\n';
			mapFile << y << '\n';
			mapFile << "#.\n";
		}
		
	}
	mapFile.close();
	return 1;

}

Utils::Utils()
{
}


Utils::~Utils()
{
}
