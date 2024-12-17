#include "Item.h"

USING_NS_CC;

std::unordered_map<std::string, Item::id> Item::idTable;
std::unordered_map<Item::id, std::string> Item::nameTable;