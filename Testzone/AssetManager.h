#pragma once
#include "Framework.h"
#include <map>
#include <string>

class AssetManager
{
public:
	static AssetManager* Instance();
	static void			 Release();
	Sprite*				 GetSprite(std::string filename);

private:
	AssetManager();
	~AssetManager();

private:
	static AssetManager*		   assman;
	std::map<std::string, Sprite*> sprites;

};