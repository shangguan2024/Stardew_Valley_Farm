#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "cocos2d.h"
#include "Item.h"


class Inventory
{
public:
    static Inventory* getInstance();  // ��ȡʵ������

    Item::id getItemId(int row, int col);  // ��ȡ��ƷID����
    size_t getItemNum(int row, int col);  // ��ȡ��Ʒ��������

    void click(int row, int col);  // �����������

    bool init();  // ��ʼ������

private:
    Inventory();
    ~Inventory();

    static Inventory* instance;

    static Item::id backpack[3][12];  // ������ƷID
    static size_t itemNum[3][12];  // ������Ʒ����

    Item::id suspended;  // ������ƷID
    size_t suspendedNum;  // ������Ʒ����
};

#endif
