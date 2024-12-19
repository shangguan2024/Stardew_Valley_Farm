

#include "ResourceManager.h"

USING_NS_CC;

ResourceManager* ResourceManager::instance = nullptr;


Rect ResourceManager::itemRect[1024];
Rect ResourceManager::blockRect[1024];
Texture2D* ResourceManager::itemRsc[1024] = {};
Texture2D* ResourceManager::blockRsc[1024] = {};
Texture2D* ResourceManager::springobjects = nullptr;
Texture2D* ResourceManager::blockTexture = nullptr;

std::string ResourceManager::inventory;

ResourceManager* ResourceManager::getInstance()
{   
    if (instance)
        return instance;

    ResourceManager* ret = new ResourceManager;
    if (ret && ret->init())
    {
        return instance = ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}


bool ResourceManager::init()
{
    loadResouces();
    updateRect();

    return true;
}

void ResourceManager::updateRect()
{
    itemRect[1] = Tile(5 , 12, 1, 1).toRect();    // Bream
    itemRsc[1] = springobjects;
    itemRect[2] = Tile(9 , 0 , 1, 1).toRect();    // Bread
    itemRsc[2] = springobjects;


}


void ResourceManager::loadResouces()
{
    springobjects = Director::getInstance()->getTextureCache()->addImage("World/springobjects..png");
}

void ResourceManager::loadUIPath()
{
    inventory = "UI/Inventory.png";
}

cocos2d::Sprite* ResourceManager::getItem(Item::id id)
{
    cocos2d::Texture2D* texture = itemRsc[id];
    const Rect region = itemRect[id];
    auto spriteFrame = SpriteFrame::createWithTexture(texture, region);
    auto itemSprite = Sprite::createWithSpriteFrame(spriteFrame);
    return itemSprite;
}

inline cocos2d::Sprite* ResourceManager::getItem(std::string name)
{
    return getBlock(Item::idTable[name]);
}

Sprite* ResourceManager::getBlock(Block::id id)
{
    Texture2D* texture = blockRsc[id];
    const Rect region = blockRect[id];
    auto spriteFrame = SpriteFrame::createWithTexture(texture, region);
    return Sprite::createWithSpriteFrame(spriteFrame);
}


inline Sprite* ResourceManager::getBlock(std::string name)
{
    return getBlock(Block::idTable[name]);
}

Label* ResourceManager::getLabel(const std::string& text)
{
    auto textLabel = Label::createWithTTF(text, Texture::Mojangles, 24);
    textLabel->setTextColor(Color4B(112, 68, 23, 255)); // ÉîºÖÉ«
    return textLabel;
}

// parameter is button function's description
ui::Button* ResourceManager::getButton(ButtonType bfd)
{
    if (bfd == BUTTON_HIDE_INVENTORY)
    {
        return ui::Button::create(Texture::HideInventory);
    }
}