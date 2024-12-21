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
    
    ID registrate(std::string name, Item&& item)
    {
        lastID++;
        item.id = lastID;
        idTable["name"] = lastID;
        nameTable[lastID] = std::move(item);
    }

    void loadRegisterTable()
    {
        Item popularity[100];
        // Edit the Item
        {
            Item& p = popularity[lastID];
            p.name = "Bread";
            p.description = "Something to eat.";
            p.flag = ItemTag::Food;
            p.behaviour_table[BehaviourType::Food] = new Food;
            registrate(p.name, std::move(popularity[lastID]));
        }

        {
            Item& p = popularity[lastID];
            p.name = "Blueberry";
            p.description = "I'm a blueberry fairy.";
            p.flag = ItemTag::Fruit;
            p.behaviour_table[BehaviourType::Fruit] = new Fruit;
            registrate(p.name, std::move(popularity[lastID]));
        }

        {
            Item& p = popularity[lastID];
            p.name = "Blueberry Seed";
            p.description = "Plant it.";
            p.flag = ItemTag::Seed;
            p.behaviour_table[BehaviourType::Seed] = new Seed;
            registrate(p.name, std::move(popularity[lastID]));
        }

        {
            Item& p = popularity[lastID];
            p.name = "Hoe";
            p.description = "Don't touch me!";
            p.flag = ItemTag::Tool;
            p.behaviour_table[BehaviourType::Hoe] = new Hoe;
            registrate(p.name, std::move(popularity[lastID]));
        }

        {
            Item& p = popularity[lastID];
            p.name = "Watering Can";
            p.description = "What can?";
            p.flag = ItemTag::Tool;
            p.behaviour_table[BehaviourType::WateringCan] = new WateringCan;
            registrate(p.name, std::move(popularity[lastID]));
        }

        {
            Item& p = popularity[lastID];
            p.name = "Salty Fish";
            p.description = "Do you have a dream?";
            p.flag = ItemTag::Fish;
            p.behaviour_table[BehaviourType::Fish] = new Fish;
            p.behaviour_table[BehaviourType::Weapon] = new Weapon;
            registrate(p.name, std::move(popularity[lastID]));
        }




    }

    bool init()
    {


        return true;
    }
    bool getIntoInventory(Item::ID)
    {

    }

public:
    static ID lastID;
    static std::unordered_map<std::string, Item::ID> idTable;
    static std::unordered_map<ID, Item> nameTable;

};

#endif
