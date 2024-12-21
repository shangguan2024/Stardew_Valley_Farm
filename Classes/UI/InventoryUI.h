#ifndef __INVENTORY_UI_H__
#define __INVENTORY_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Items/Inventory.h"
#include "ResourceManagement/ResourceManager.h"

class InventoryUI : public cocos2d::ui::Widget {
public:
    static InventoryUI* create();

    InventoryUI();
    ~InventoryUI();

    bool init();
    void updateUI();  // ����UI�����������Ʒ�б�
    void click(cocos2d::Vec2);
    void attach(cocos2d::Vec2 pos);
    void detach();

    // Convert displayer coord into row and col in inventory
    cocos2d::Vec2 convertXYToRC(const cocos2d::Vec2&);
    // Convert row and col in inventory into displayer coord
    cocos2d::Vec2 convertRCToXY(const cocos2d::Vec2&);


private:
    static Inventory* inventory;
    static ItemManager* im;
    static ResourceManager* rm;

    cocos2d::Layer* attached;
    // ��������Ʒ������ڸ�Layer�У����ڹ���
    cocos2d::Layer* itemLayer;
    // ����UIԪ�أ�������Ʒ���ӡ���ҳ��ť��
};

#endif // __INVENTORY_UI_H__
