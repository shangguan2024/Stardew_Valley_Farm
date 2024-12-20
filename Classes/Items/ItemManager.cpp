#include "ItemManager.h"

USING_NS_CC;

std::unordered_map<std::string, Item::ID> ItemManager::idTable;
std::unordered_map<Item::ID, Item> ItemManager::nameTable;