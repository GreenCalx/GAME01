#pragma once
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"

#define MAX_TEXTURES 20

using namespace std;



class TextureManager
{
	typedef map<string, sf::Texture> TextureHashMap;
	
private: // methods
	TextureManager();
	~TextureManager();
	
public: // methods
	static TextureManager* Instance() {
		if (m_instance == 0) m_instance = new TextureManager();

		return m_instance;
	}
	void addFullTexture(string pLabel, string pFileName);
	sf::Texture* getTexture(string pLabel);

private : // variables
	static TextureManager* m_instance;
	TextureHashMap* mLoadedTextures;
	sf::Texture mErrorTexture;

public : //variables

};

#endif