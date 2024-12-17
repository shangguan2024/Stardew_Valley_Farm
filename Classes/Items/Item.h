#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Block.h"

class Item : cocos2d::Sprite
{
public:
    using id = int;

    static const id NIL = 0;

    bool init()
    {
        idTable["Bream"] = 1;
        nameTable[1] = "Bream";
    }

public:
    static std::unordered_map<std::string, id> idTable;
    static std::unordered_map<id, std::string> nameTable;

};

#endif
