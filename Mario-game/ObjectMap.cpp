#include "ObjectMap.h"
#include "Brick.h"

CObjectMap::CObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT>& coObjects)
{
	this->objectGroupElement = objectGroupElement;
	objectGroupElement->QueryIntAttribute("objectGroupId", &objectGroupId);
	name = objectGroupElement->Attribute("name");
	ImportData(coObjects);
}

void GetInfoElement(TiXmlElement* element, int& objectId, float& x, float& y, float& width, float& height)
{
	element->QueryIntAttribute("id", &objectId);
	element->QueryFloatAttribute("x", &x);
	element->QueryFloatAttribute("y", &y);
	element->QueryFloatAttribute("width", &width);
	element->QueryFloatAttribute("height", &height);
}

void CObjectMap::ImportData(vector<LPGAMEOBJECT>& coObjects)
{
	CGameObject* obj = NULL;
	int objectId;
	float x, y;
	float width, height;
	TiXmlElement* element = objectGroupElement->FirstChildElement();

	if (name.compare("Solid") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CPlatform(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	else if (name.compare("Coin") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CCoin(x, y);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	if (name.compare("Brick") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CBrick(x, y);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
}
