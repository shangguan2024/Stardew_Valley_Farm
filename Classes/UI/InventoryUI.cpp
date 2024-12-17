#include "InventoryUI.h"
#include "UI/UIManager.h"
#include "ResourceManagement/ResourceManager.h"

Inventory* InventoryUI::inventory = nullptr;

InventoryUI::InventoryUI() :
	closeButton(nullptr)
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

// 初始化界面
bool InventoryUI::init()
{
	inventory = Inventory::getInstance();

	auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto inventoryMainUI = cocos2d::Sprite::create("UI/Inventory.png");
	inventoryMainUI->setPosition(screenSize.width / 2, screenSize.height * 0.4);
	this->addChild(inventoryMainUI);

	closeButton = cocos2d::ui::Button::create("UI/Buttons/ExitButton.png");
	closeButton->setPosition(screenSize * 0.75);
	closeButton->addClickEventListener([this](Ref* sender) {
		UIManager::getInstance()->hideInventoryUI();  // 点击关闭时隐藏背包
		});
	this->addChild(closeButton);

	updateUI();

	return true;
}

// 更新背包内容，比如显示物品列表
void InventoryUI::updateUI()
{
	auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
	const auto rscManager = ResourceManager::getInstance();

	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 12; ++col) {
			auto itemId = inventory->getItemId(row, col);
			auto itemNum = inventory->getItemNum(row, col);
			if (itemId == Item::NIL)
				continue;

			auto itemSprite = rscManager->getItem(itemId);
			itemSprite->setAnchorPoint(Vec2(0, 0));
			itemSprite->setScale(4);
			int x = 256, y = 0;
			if (row == 0)
				y = 480;
			else if (row == 1)
				y = 400;
			else if (row == 2)
				y = 326;

			itemSprite->setPosition(x + col * 4 * 16, y);
			this->addChild(itemSprite);

		}
	}
}