#include "Block.h"

USING_NS_CC;

std::unordered_map<std::string, Block::id> Block::idTable;
std::unordered_map<Block::id, std::string> Block::nameTable;