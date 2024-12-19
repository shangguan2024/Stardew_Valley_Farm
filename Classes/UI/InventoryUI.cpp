#include "InventoryUI.h"
#include "UI/UIManager.h"
#include "ResourceManagement/ResourceManager.h"

USING_NS_CC;

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

	itemLayer = Layer::create();
	itemLayer->setTag(1);

	auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto inventoryMainUI = cocos2d::Sprite::create(Texture::Inventory);
	inventoryMainUI->setPosition(screenSize.width / 2, screenSize.height * 0.4);

	closeButton = ResourceManager::getInstance()->getButton(BUTTON_HIDE_INVENTORY);
	closeButton->setScale(4);
	closeButton->setPosition(Vec2(screenSize * 0.8 + Size(64, 0)));
	closeButton->addClickEventListener([this](Ref* sender) {
		UIManager::getInstance()->hideInventoryUI();  // 点击关闭时隐藏背包
		});

	this->addChild(inventoryMainUI);
	this->addChild(closeButton);
	this->addChild(itemLayer);

	updateUI();

	return true;
}

// 更新背包内容，比如显示物品列表
void InventoryUI::updateUI()
{
	auto screenSize = cocos2d::Director::getInstance()->getVisibleSize();
	const auto rscManager = ResourceManager::getInstance();

	if (auto layer = this->getChildByTag(1)) { // itemLayer
		layer->removeAllChildrenWithCleanup(true); // Don't release
	}

	for (int row = 0; row < 3; ++row) {
		for (int col = 0; col < 12; ++col) {
			// 无物品则跳过
			auto itemId = inventory->getItemId(row, col);
			auto itemNum = inventory->getItemNum(row, col);
			if (itemId == Item::NIL)
				continue;

			// 物品图像显示
			auto itemSprite = rscManager->getItem(itemId);
			itemSprite->setAnchorPoint(cocos2d::Vec2(0, 0));
			itemSprite->setScale(3.5);
			itemSprite->setPosition(convertRCToXY(Vec2(row, col)));
			itemSprite->setTag(row * 12 + col);
			itemLayer->addChild(itemSprite);

			if (itemNum == 1)
				continue;

			// Turn a interger into string
			char buffer[8];
			snprintf(buffer, sizeof(buffer), "%d", itemNum);
			auto numLabel = ResourceManager::getInstance()->getLabel(buffer);
			numLabel->setAnchorPoint(Vec2(0,0));
			numLabel->setPosition(convertRCToXY(Vec2(row, col)) 
									+ Vec2(16*2.7, -4));
			itemLayer->addChild(numLabel);
		}
	}


}

void InventoryUI::click(Vec2 pos)
{
	auto RC = convertXYToRC(pos);
	Inventory::getInstance()->click(RC.x, RC.y);
	updateUI();
}

// Convert row and col in inventory into displayer coord
Vec2 InventoryUI::convertRCToXY(const Vec2& pos)
{
	const int row = pos.x, col = pos.y;
	float x = 256, y = 0;
	if (row == 0)
		y = 480;
	else if (row == 1)
		y = 400;
	else if (row == 2)
		y = 334;
	return Vec2(x + col * 4 * 16, y);
}

// Convert displayer coord into row and col in inventory
Vec2 InventoryUI::convertXYToRC(const Vec2& pos)
{
	const float x = pos.x, y = pos.y;
	int col = int((x - 256) / 4 / 16), row = -1;
	if (y > 480 && y < 480 + 3.5 * 16)
		row = 0;
	else if (y > 400 && y < 400 + 3.5 * 16)
		row = 1;
	else if (y > 334 && y < 334 + 3.5 * 16)
		row = 2;
	return Vec2(row, col);

}