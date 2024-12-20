#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
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
    Item() = default;
    Item(Item::ID);
    Item(Item::ID, std::string);
    Item(Item&&); // move constructor

    Item& operator=(Item&&);

private:
    std::string name;
    std::string description;
    ID id;
    ItemTag flag;

    //std::string icon;
    std::unordered_map<BehaviourType, Behaviour*> behaviour_table;

};


#endif
