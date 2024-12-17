
#include "ResourceManager.h"

Rect ResourceManager::itemRect[1024];
Rect ResourceManager::blockRect[1024];
cocos2d::Texture2D* ResourceManager::itemRsc[1024] = {};
cocos2d::Texture2D* ResourceManager::blockRsc[1024] = {};
cocos2d::Texture2D* ResourceManager::springobjects = nullptr;
cocos2d::Texture2D* ResourceManager::blockTexture = nullptr;

ResourceManager* ResourceManager::getInstance()
{
    ResourceManager* ret = new ResourceManager();
    if (ret && ret->init())
    {
        return ret;
    }
    else
    {
        delete ret;
        return nullptr;
    }
}


bool ResourceManager::init()
{
    updateRect();
    loadResouces();

    return true;
}

void ResourceManager::updateRect()
{
    itemRect[1] = Rect(5*16, 12*16, 16, 16);
}


void ResourceManager::loadResouces()
{
    springobjects = Director::getInstance()->getTextureCache()->addImage("World/springobjects..png");
}

void ResourceManager::loadUIPath()
{
    inventory = "Inventory.png";
}

cocos2d::Sprite* ResourceManager::getItem(Item::id id)
{
    cocos2d::Texture2D* texture = itemRsc[id];
    const Rect region = itemRect[id];
    auto spriteFrame = SpriteFrame::createWithTexture(texture, region);
    return Sprite::createWithSpriteFrame(spriteFrame);
}

inline cocos2d::Sprite* ResourceManager::getItem(std::string name)
{
    return getBlock(Item::idTable[name]);
}

cocos2d::Sprite* ResourceManager::getBlock(Block::id id)
{
    cocos2d::Texture2D* texture = blockRsc[id];
    const Rect region = blockRect[id];
    auto spriteFrame = SpriteFrame::createWithTexture(texture, region);
    return Sprite::createWithSpriteFrame(spriteFrame);
}


inline cocos2d::Sprite* ResourceManager::getBlock(std::string name)
{
    return getBlock(Block::idTable[name]);
}