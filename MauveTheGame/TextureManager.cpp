#include "TextureManager.h"

TextureManager* TextureManager::m_instance = 0;

TextureManager::TextureManager()
{
	this->mLoadedTextures = new TextureHashMap();
	if (!mErrorTexture.loadFromFile("Resources/Sprites/Actors/Error.png"))
	{
		// TODO : ERROR LOG
	}
}


void TextureManager::addFullTexture(string pLabel, string pFileName)
{
	if (mLoadedTextures->size() > MAX_TEXTURES) return;

	sf::Texture* texture;
	if (mLoadedTextures->find(pLabel) != mLoadedTextures->end()) { // test duplicate
		mLoadedTextures->erase(pLabel);
	}

	mLoadedTextures->insert(pair < string, sf::Texture>(pLabel, sf::Texture()));
	texture = &mLoadedTextures->at(pLabel);
	if (!texture->loadFromFile(pFileName.c_str()))
	{
		// TODO : ERROR LOG
		cout << "whatever dude " << endl;
	}
}

sf::Texture* TextureManager::getTexture(string pLabel)
{
	if (mLoadedTextures->empty()) return &mErrorTexture;
	if (mLoadedTextures->find(pLabel) != mLoadedTextures->end()) {
		return &mLoadedTextures->at(pLabel);
	}
	return &mErrorTexture;
}


TextureManager::~TextureManager()
{
}


