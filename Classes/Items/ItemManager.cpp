#include "ItemManager.h"

USING_NS_CC;


Item::ID ItemManager::lastID = Item::NIL;
ItemManager* ItemManager::instance = nullptr;
std::unordered_map<std::string, Item::ID> ItemManager::idTable;
std::unordered_map<Item::ID, Item> ItemManager::itemTable;

ItemManager* ItemManager::getInstance()
{
    if (instance)
        return instance;
    ItemManager* ret = new ItemManager;
    if (ret && ret->init()) {
        return instance = ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool ItemManager::init()
{
    loadRegisterTable();
    return true;
}

Item::ID ItemManager::registrate(std::string name, Item&& item)
{
    lastID++;
    item.id = lastID;
    idTable["name"] = lastID;
    itemTable[lastID] = std::move(item);
    return lastID;
}

void ItemManager::loadRegisterTable()
{
    Item popularity;
    // Edit the Item
    {
        Item& p = popularity;
        p.name = "Bread";
        p.description = "Something to eat.";
        p.flag = ItemTag::Food;
        p.icon_path = &Resources::springobjects;
        p.icon_frame = TextureTile(5, 12, 1, 1);
        p.behaviour_table[BehaviourType::Food];
        registrate(p.name, std::move(popularity));
    }

    {
        Item& p = popularity;
        p.name = "Blueberry";
        p.description = "I'm a blueberry fairy.";
        p.flag = ItemTag::Fruit;
        p.icon_path = &Resources::springobjects;
        p.icon_frame = TextureTile(10, 18, 1, 1);
        p.behaviour_table[BehaviourType::Fruit];
        registrate(p.name, std::move(popularity));
    }

    {
        Item& p = popularity;
        p.name = "Blueberry Seed";
        p.description = "Plant it.";
        p.flag = ItemTag::Seed;
        p.icon_path = &Resources::springobjects;
        p.icon_frame = TextureTile(20, 1, 1, 1);
        p.behaviour_table[BehaviourType::Seed];
        registrate(p.name, std::move(popularity));
    }

    {
        Item& p = popularity;
        p.name = "Hoe";
        p.description = "Don't touch me!";
        p.flag = ItemTag::Tool;
        p.icon_path = &Resources::tools;
        p.icon_frame = TextureTile(2, 5 + 14, 1, 1);
        p.behaviour_table[BehaviourType::Hoe];
        registrate(p.name, std::move(popularity));
    }

    {
        Item& p = popularity;
        p.name = "Watering Can";
        p.description = "What can?";
        p.flag = ItemTag::Tool;
        p.icon_path = &Resources::tools;
        p.icon_frame = TextureTile(14, 2 + 14, 1, 1);
        p.behaviour_table[BehaviourType::WateringCan];
        registrate(p.name, std::move(popularity));
    }

    {
        Item& p = popularity;
        p.name = "Salty Fish";
        p.description = "Do you have a dream?";
        p.flag = ItemTag::Fish;
        p.icon_path = &Resources::springobjects;
        p.icon_frame = TextureTile(5, 19, 1, 1);
        p.behaviour_table[BehaviourType::Fish];
        p.behaviour_table[BehaviourType::Weapon];
        registrate(p.name, std::move(popularity));
    }

}
