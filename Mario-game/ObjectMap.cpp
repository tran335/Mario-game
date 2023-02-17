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
	if (name.compare("Ghost") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CBigBox(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("Card") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CCard(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("CameraBound") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CCameraBound(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("BoundOverWorld") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new COverworldBound(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("AnimatedBG") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CTree(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}
	}
	if (name.compare("Three") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CThree(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("switch") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CSwitch(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("Portal") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CBigBox(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("QuestionBlocks") == 0) {
		while (element)
		{
			string typeName;
			int type;
			GetInfoElement(element, objectId, x, y, width, height);
			typeName = element->Attribute("name");
			element->QueryIntAttribute("type", &type);
			CQuestionBrick* questionbrick = new CQuestionBrick(x, y);
			if (typeName.compare("coin") == 0)
			{
				obj = new CCoinBrick();
			}
			else if (typeName.compare("powerup") == 0)
			{
				obj = new CSuperMushroom(x,y);
			}
			else if (typeName.compare("1upMushroom") == 0)
			{
				obj = new CCoinBrick();
			}
			
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			coObjects.push_back(questionbrick);
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("Enemy") == 0) {
		while (element)
		{
			string enemyName = element->Attribute("name");
			GetInfoElement(element, objectId, x, y, width, height);
			if (enemyName.compare("goomba") == 0) {
				string typeGoomba = element->Attribute("type");
					if (typeGoomba.compare("tan") == 0) {
						obj = new CGoomba(x, y);
						obj->SetPosition(x, y);
						coObjects.push_back(obj);
					}
					else if (typeGoomba.compare("para") == 0) {
						obj = new CParaGoomba(x, y);
						obj->SetPosition(x, y);
						coObjects.push_back(obj);
					}
			}
			if (enemyName.compare("koopa") == 0) {
				string typeKoopa = element->Attribute("type");
				if (typeKoopa.compare("red") == 0) {
					obj = new CKoopa(x, y, RED_KOOPA);
					obj->SetPosition(x, y);
					coObjects.push_back(obj);
				}
				else if (typeKoopa.compare("green") == 0) {
					obj = new CKoopa(x, y, GREEN_KOOPA);
					obj->SetPosition(x, y);
					coObjects.push_back(obj);
				}
				else if (typeKoopa.compare("para") == 0) {
					obj = new CParaKoopa(x, y);
					obj->SetPosition(x, y);	
					coObjects.push_back(obj);
				}
			}
			if (enemyName.compare("piranha") == 0) {
				obj = new CPiranha(x, y);
				obj->SetPosition(x, y);
				coObjects.push_back(obj);
			}
			if (enemyName.compare("venus") == 0) {
				string typeVenus = element->Attribute("type");
				if (typeVenus.compare("red") == 0) {
					obj = new CVenusFireTrap(x, y, RED_VENUS);
					obj->SetPosition(x, y);
					coObjects.push_back(obj);
				}
				else if (typeVenus.compare("green") == 0) {
					obj = new CVenusFireTrap(x, y, GREEN_VENUS);
					obj->SetPosition(x, y);
					coObjects.push_back(obj);
				}
			}
			element = element->NextSiblingElement();
		}

	}
	if (name.compare("KoopaBound") == 0) {
		while (element)
		{
			GetInfoElement(element, objectId, x, y, width, height);
			obj = new CKoopaBound(width, height);
			obj->SetPosition(x, y);
			coObjects.push_back(obj);
			element = element->NextSiblingElement();
		}

	}
}
