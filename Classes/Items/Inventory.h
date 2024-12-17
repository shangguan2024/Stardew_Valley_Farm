#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "cocos2d.h"
#include "Item.h"


class Inventory
{
public:
    Inventory();  // ���캯������

    Item::id getItemId(int row, int col);  // ��ȡ��ƷID����
    size_t getItemNum(int row, int col);  // ��ȡ��Ʒ��������

    void click(int row, int col);  // �����������

    static Inventory* getInstance();  // ��ȡʵ������

    bool init();  // ��ʼ������

private:
    static Item::id backpack[3][12];  // ������ƷID
    static size_t itemNum[3][12];  // ������Ʒ����
    Item::id suspended;  // ������ƷID
    size_t suspendedNum;  // ������Ʒ����
};

#endif
