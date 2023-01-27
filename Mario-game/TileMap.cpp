#include "TileMap.h"
CTileMap* CTileMap::__instance = NULL;

CTileMap* CTileMap::GetInstance()
{
	if (__instance == NULL) __instance = new CTileMap();
	return __instance;
}

void CTileMap::ReadXmlFile(const char* pathTmx, int id, vector<LPGAMEOBJECT>& objects, string prefixPath)
{
	TiXmlDocument doc(pathTmx);
	if (!doc.LoadFile())
	{
		return;
	}
	TiXmlElement* root = doc.RootElement(); //map
	TiXmlElement* element = root->FirstChildElement();

	while (element)
	{
		string elementName;
		elementName = element->Value();
		if (elementName.compare("tileset") == 0)
		{
			tileSet = new CTileSet(element, id, prefixPath);

			
		}
		else if (elementName.compare("layer") == 0)
		{
			Layer* layer = new Layer(element);
			layers.push_back(layer);
			if (layer->GetName().compare("Foreground") == 0)
				foregroundLayer = layer;
		}
		else if (elementName.compare("objectgroup") == 0)
		{
			objectMap = new CObjectMap(element, objects);
		}
		element = element->NextSiblingElement();
	}
}

void CTileMap::RenderBackground()
{
	for (size_t i = 0; i < layers.size(); i++)
	{
		if (layers[i]->GetName().compare("Foreground") != 0) {
			layers[i]->Render();
		}
	}
}

void CTileMap::RenderForeground()
{
	foregroundLayer->Render();
}

void CTileMap::Clear()
{
	tileSet = NULL;
	objectMap = NULL;
	for (int i = 0; i < layers.size(); i++) {
		delete layers[i];
	}
	layers.clear();
}
