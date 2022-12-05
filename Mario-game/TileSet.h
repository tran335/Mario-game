#pragma once
#include "fstream"
#include "Sprites.h"
#include "Utils.h"
#include "tinyXML/tinyxml.h"
#include "Textures.h"

class CTileSet
{
	string prefixPath;
	TiXmlElement* tileset;
	int textureId;
	D3DCOLOR transColor;

	int tileWidth;
	int tileHeight;
	int tileCount;
	int columns;
	int rows;
	LPCWSTR pathImage;
public:
	CTileSet(TiXmlElement* tileset, int id, string prefixPath);
	void SplitImageToTile();
};

