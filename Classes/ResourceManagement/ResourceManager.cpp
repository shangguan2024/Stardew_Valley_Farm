// ?

#include "ResourceManager.h"

USING_NS_CC;

ResourceManager* ResourceManager::instance	= nullptr;

Texture2D* ResourceManager::springobjects	= nullptr;
Texture2D* ResourceManager::crops			= nullptr;
Texture2D* ResourceManager::hoeDirt			= nullptr;
Texture2D* ResourceManager::tools			= nullptr;

std::string ResourceManager::inventory;

ResourceManager* ResourceManager::getInstance()
{
	if (instance)
		return instance;
	ResourceManager* ret = new ResourceManager();
	if (ret && ret->init()) {
		return instance = ret;
	}
	else {
		delete ret;
		return nullptr;
	}
}


bool ResourceManager::init()
{
	loadResouces();

	return true;
}


Texture2D* load(const std::string& filename) {
	return Director::getInstance()->getTextureCache()->addImage(filename);
}

void ResourceManager::loadResouces()
{
	//enum class Texture {
	//	NIL,
	//	springobjects,
	//	crops,
	//	hoeDirt,
	//	tools,
	//};

	springobjects = load("World/springobjects..png");
	tools = load("Items/tools..png");
}

void ResourceManager::loadUIPath()
{
	inventory = "UI/Inventory.png";
}

cocos2d::Sprite* ResourceManager::getItem(Item::ID id)
{
	auto texture = ItemManager::itemTable[id].icon_path;
	auto region = ItemManager::itemTable[id].icon_frame.toRect();

	//  * If the filename was not previously loaded, it will create a new Texture2D.
	auto spriteFrame = SpriteFrame::createWithTexture(load(*texture), region);
	auto itemSprite = Sprite::createWithSpriteFrame(spriteFrame);
	return itemSprite;
}

inline cocos2d::Sprite* ResourceManager::getItem(std::string name)
{
	return getItem(ItemManager::idTable[name]);
}

Label* ResourceManager::getLabel(const std::string& text, const int SystemFontSize)
{
	auto textLabel = Label::createWithTTF(text, Resources::Mojangles, SystemFontSize);
	textLabel->setTextColor(Color4B(112, 68, 23, 255)); // ÉîºÖÉ«
	return textLabel;
}

// parameter is button function's description
ui::Button* ResourceManager::getButton(ButtonType bfd)
{
	if (bfd == BUTTON_HIDE_INVENTORY) {
		return ui::Button::create(Resources::HideInventory);
	}
	return nullptr;
}

MapName ResourceManager::stringToMapNameEnum(const std::string& mapName)
{
	if (mapName == "FarmYard")
		return MapName::FarmYard;
	if (mapName == "Beach")
		return MapName::Beach;
	return MapName::Null;
	//MapName::FarmHouse;
}


