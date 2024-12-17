#ifndef __INVENTORY_UI_H__
#define __INVENTORY_UI_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InventoryUI : public cocos2d::ui::Widget {
public:
    static InventoryUI* create();

    InventoryUI();
    ~InventoryUI();

    bool init();

    void updateUI();  // ����UI�����������Ʒ�б�

private:
    cocos2d::ui::Button* closeButton;
    // ����UIԪ�أ�������Ʒ���ӡ���ҳ��ť��
};

#endif // __INVENTORY_UI_H__
