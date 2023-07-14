#pragma once
#include "fstream"
#include "Utils.h"
#include "tinyXML/tinyxml.h"
#include "GameObject.h"
#include "Coin.h"
#include "Platform.h"
#include "BigBox.h"
#include "Goomba.h"
#include "ParaGoomba.h"
#include "CameraBound.h"
#include "QuestionBrick.h"
#include "CoinBrick.h"
#include "Koopa.h"
#include "KoopaBound.h"
#include "Portal.h"
#include "VenusFireTrap.h"
#include "SuperMushroom.h"
#include "Leaf.h"
#include "OverworldBound.h"
#include "Piranha.h"
#include "Parakoopa.h"
#include "Tree.h"
#include "Three.h"
#include "Switch.h"
#include "Card.h"
#include "PortalPipe.h"
#include "HUD.h"

class CObjectMap
{
	vector<LPGAMEOBJECT> objects;
	TiXmlElement* objectGroupElement;
	int objectGroupId = 0;
	string name;
public:
	CObjectMap(TiXmlElement* objectGroupElement, vector<LPGAMEOBJECT>& coObjects);
	void ImportData(vector<LPGAMEOBJECT>& coObjects);
};

