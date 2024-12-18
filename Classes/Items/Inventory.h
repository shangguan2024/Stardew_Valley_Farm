#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "cocos2d.h"
#include "Item.h"


class Inventory
{
public:
    struct Slot
    {
        Item::id id;
        size_t num;

        Slot(Item::id new_id, size_t new_num)
            : id(new_id), num(new_num) {}
        Slot() : Slot(Item::NIL, 0) {}

        inline bool operator==(Slot other) { return this->id == other.id; }
        inline bool operator!=(Slot other) { return this->id != other.id; }
        inline bool operator==(Item::id other_id) { return this->id == other_id; }
        inline bool operator!=(Item::id other_id) { return this->id != other_id; }
    };

    static Inventory* getInstance();

    Item::id getItemId(int row, int col);
    size_t getItemNum(int row, int col);
    Slot getSlot(int row, int col);


    void click(int row, int col);  // �����Ʒ��λ������������Ʒ
    void detach();    // ���������Ʒ����ԭλ��
    void merge(int row, int col, int num);
    bool pick(Item::id item, size_t num);

    bool init();

private:
    Inventory();
    ~Inventory();

    static Inventory* instance;
    static Slot inventory[3][12];  // ������ƷID������
    Slot attached;

    int lastClickRow, lastClickCol;

};

#endif
