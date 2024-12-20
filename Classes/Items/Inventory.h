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
    void click(int row, int col);    // �����Ʒ��λ������������Ʒ
    bool pick(Item::ID item, size_t num);    // ������Ʒ
    bool detach();    // ���������Ʒ����ԭλ��

private:
    Inventory();
    ~Inventory();

    static Inventory* instance;
    static Slot inventory[3][12];  // ������ƷID������
    Slot attached;

    int lastClickRow, lastClickCol;

};

#endif
