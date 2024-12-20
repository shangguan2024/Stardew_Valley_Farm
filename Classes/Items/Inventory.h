#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "cocos2d.h"
#include "Item.h"


class Inventory
{
public:
    struct Slot
    {
        Item::ID id;
        size_t num;

        Slot(Item::ID new_id, size_t new_num)
            : id(new_id), num(new_num) {}
        Slot() : Slot(Item::NIL, 0) {}

        inline bool operator==(Slot other) { return this->id == other.id; }
        inline bool operator!=(Slot other) { return this->id != other.id; }
        inline bool operator==(Item::ID other_id) { return this->id == other_id; }
        inline bool operator!=(Item::ID other_id) { return this->id != other_id; }
    };

    // Initialization
    static Inventory* getInstance();
    bool init();

    // Getters
    Item::ID getItemId(int row, int col);
    size_t getItemNum(int row, int col);
    Slot getSlot(int row, int col);

    // Helper Functions
    void merge(int row, int col, int num);
    Slot getAttached();
    //cocos2d::Vec2 getFirstEmptySlot();
    
    // Interface
    void click(int row, int col);    // 点击物品槽位，更新悬挂物品
    bool pick(Item::ID item, size_t num);    // 捡起物品
    bool detach();    // 解除悬挂物品，还原位置

private:
    Inventory();
    ~Inventory();

    static Inventory* instance;
    static Slot inventory[3][12];  // 背包物品ID和数量
    Slot attached;

    int lastClickRow, lastClickCol;

};

#endif
