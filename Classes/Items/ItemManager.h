#ifndef __ITEM_MANAGER_H__
#define __ITEM_MANAGER_H__

#include "cocos2d.h"
#include "Item.h"



//// 物品种类枚举
//enum class ItemTag {
//    Behaviour, // Default Type - NULL
//    Block, // Placeable
//    Food,
//    Tool,
//    Hoe,
//    Seed,
//    Fruit,
//    Fish,
//    Weapon,
//    SaltyFish // SaltyFish = Food + Weapon
//
//};

class ItemManager
{
public:
    using ID = Item::ID;
    static const Item::ID NIL = Item::NIL;

public:
    
    static ItemManager* getInstance();
    bool init();

    ID registrate(std::string name, Item&& item);
    void loadRegisterTable();

public:
    static ID lastID;
    static ItemManager* instance;
    static std::unordered_map<std::string, Item::ID> idTable;
    static std::unordered_map<ID, Item> itemTable;

};

#endif
