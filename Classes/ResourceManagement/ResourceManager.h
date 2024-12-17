#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "cocos2d.h"
#include "unordered_map"

// Entities
#include "Entities/Animal.h"
#include "Entities/Dog.h"
#include "Entities/NPC.h"

// Items
#include "Items/Item.h"
#include "Items/Block.h"


USING_NS_CC;

class ResourceManager
{
public:
    
    static ResourceManager* getInstance()
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

    bool init()
    {
        updateRect();
        loadResouces();

        return true;
    }

    void updateRect()
    {
        itemRect[1] = Rect(5*16, 12*16, 16, 16);
    }

    void loadResouces()
    {
        springobjects = Director::getInstance()->getTextureCache()->addImage("Maps/springobjects..png");
    }

    cocos2d::Sprite* getItem(Item::id id)
    {
        cocos2d::Texture2D* texture = itemRsc[id];
        const Rect region = itemRect[id];
        auto spriteFrame = SpriteFrame::createWithTexture(texture, region);
        return Sprite::createWithSpriteFrame(spriteFrame);
    }

    inline cocos2d::Sprite* getItem(std::string name)
    {
        return getBlock(Item::idTable[name]);
    }

    cocos2d::Sprite* getBlock(Block::id id)
    {
        cocos2d::Texture2D* texture = blockRsc[id];
        const Rect region = blockRect[id];
        auto spriteFrame = SpriteFrame::createWithTexture(texture, region);
        return Sprite::createWithSpriteFrame(spriteFrame);
    }

    inline cocos2d::Sprite* getBlock(std::string name)
    {
        return getBlock(Block::idTable[name]);
    }




private:
    // A Rectangent region of some Texture in where the required item is
    // the index is id
    static Rect itemRect[1024];
    static Rect blockRect[1024];

    // Texture in where the required item is (Rsc : Resource)
    static cocos2d::Texture2D* itemRsc[1024];
    static cocos2d::Texture2D* blockRsc[1024];

    static cocos2d::Texture2D* springobjects;
    static cocos2d::Texture2D* blockTexture;

};


#endif // _RESOURCEMANAGER_H_
