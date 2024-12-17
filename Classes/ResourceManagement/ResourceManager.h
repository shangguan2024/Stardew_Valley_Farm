#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "cocos2d.h"
#include <unordered_map>

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
    
    static ResourceManager* getInstance();
    bool init();

    void updateRect();
    void loadResouces();
    void loadUIPath();

    cocos2d::Sprite* getItem(Item::id id);
    inline cocos2d::Sprite* getItem(std::string name);
    cocos2d::Sprite* getBlock(Block::id id);
    inline cocos2d::Sprite* getBlock(std::string name);




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

    static std::string inventory;

};


#endif // _RESOURCEMANAGER_H_
