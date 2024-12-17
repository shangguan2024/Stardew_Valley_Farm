#include "InventoryUI.h"
#include "UI/UIManager.h"

InventoryUI::InventoryUI()
    : closeButton(nullptr)
{
}

InventoryUI::~InventoryUI()
{
}

InventoryUI* InventoryUI::create()
{
    InventoryUI* ret = new InventoryUI();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool InventoryUI::init()
{
    // ��ʼ������
    closeButton = cocos2d::ui::Button::create("Buttons/MenuSceneButtons/ExitButton.png");
    closeButton->setPosition(cocos2d::Vec2(400, 300));
    closeButton->addClickEventListener([this](Ref* sender) {
        UIManager::getInstance()->hideInventoryUI();  // ����ر�ʱ���ر���
        });

    this->addChild(closeButton);
    auto testbackground = cocos2d::Sprite::create("Buttons/MenuSceneButtons/CreateButton.png");
    testbackground->setPosition(cocos2d::Vec2(600, 500));
    this->addChild(testbackground);

    return true;
}

void InventoryUI::updateUI()
{
    // ���±������ݣ�������ʾ��Ʒ�б�
}
