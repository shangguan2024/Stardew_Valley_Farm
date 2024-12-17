#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Item.h"

class Block : cocos2d::Sprite
{
public:
    static const size_t NIL = 0;

    using id = size_t;


public:
    static std::unordered_map<std::string, id> idTable;
    static std::unordered_map<id, std::string> nameTable;
};

#endif
