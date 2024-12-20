#ifndef __PLAYER_CONTROLLER_H__
#define __PLAYER_CONTROLLER_H__

#include "cocos2d.h"
#include "Player.h"
#include "Items/Inventory.h"

class PlayerController
{
public:
    static PlayerController* getInstance();

    void update();

    cocos2d::Vec2 enterPosition;

private:
    PlayerController();
    ~PlayerController();

    bool init();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode);

    void updateDirection();

    void toggleInventory();

    static PlayerController* instance;
    Player* player;
    Inventory* inventory;
};

#endif
