#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include "ResourceManagement/Texture.h"
#include "Behaviour.h"


class Item/* : cocos2d::Sprite*/
{
public:
    using ID = int;
    static const ID NIL = 0;
    friend class ItemManager;
public:
    void use(); 
    size_t getFlag();

public:
    Item();
    Item(Item::ID);
    Item(Item::ID, std::string);
    Item(Item&&); // move constructor

    Item& operator=(Item&&);
    void clear();

public:

    std::string name;
    std::string description;
    ID id;
    ItemTag flag;

    const std::string* icon_path;
    TextureTile icon_frame;

    //std::string icon;
    std::unordered_map<BehaviourType, Behaviour*> behaviour_table;

};


#endif
