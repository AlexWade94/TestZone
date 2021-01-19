#include "AssetManager.h"

AssetManager* AssetManager::assman = nullptr;
AssetManager* AssetManager::Instance()
{
	if (assman == nullptr)
		assman = new AssetManager();
	return assman;
}

void AssetManager::Release()
{
	delete assman;
	assman = nullptr;
}

Sprite* AssetManager::GetSprite(std::string filename)
{
	std::string fullpath;
	fullpath=("assets/" + filename);
	if (sprites[fullpath] == nullptr)
	{
		sprites[fullpath] = createSprite(fullpath.c_str());
	}
	return sprites[fullpath];
}


AssetManager::AssetManager()
{

}

AssetManager::~AssetManager()
{
	for (auto& tex : sprites)
	{
		if (tex.second != nullptr)
		{
			destroySprite(tex.second);
		}
	}
	sprites.clear();
}
