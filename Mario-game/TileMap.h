#pragma once
#include "Layer.h"
#include "TileSet.h"
#include "ObjectMap.h"

class CTileMap
{
	static CTileMap* __instance;
	vector<LPLAYER> layers;
	CTileSet* tileSet;
	CObjectMap *objectMap;
	Layer* foregroundLayer;

public:
	static CTileMap* GetInstance();
	void ReadXmlFile(const char* pathTmx, int id, vector<LPGAMEOBJECT>& objects, string prefixPath);
	void RenderBackground();
	void RenderForeground();
	CObjectMap *GetObjectMap() { return objectMap; }
	void Clear();
};

