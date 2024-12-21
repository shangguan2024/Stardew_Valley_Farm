#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include "cocos2d.h"
#include "UI/CocosGUI.h"
#include "Texture.h"
#include "Constant.h"

// Entities
#include "Entities/Animal.h"
#include "Entities/Dog.h"
#include "Entities/NPC.h"

// Items
#include "Items/Item.h"
#include "Items/ItemManager.h"

// 负责统一加载素材文件，再分配矩形到各成分
class ResourceManager
{
public:

    static ResourceManager* getInstance();
    bool init();

    void loadResouces();
    void loadUIPath();

    cocos2d::Sprite* getItem(Item::ID id);
    inline cocos2d::Sprite* getItem(std::string name);
    cocos2d::Label* getLabel(const std::string& text, const int SystemFontSize = 24);
    cocos2d::ui::Button* getButton(ButtonType bfd);




private:
    static ResourceManager* instance;

    //enum class Texture {
    //	NIL,
    //	springobjects,
    //	crops,
    //	hoeDirt,
    //	tools,
    //};
    static cocos2d::Texture2D* Nil;
    static cocos2d::Texture2D* springobjects;
    static cocos2d::Texture2D* crops;
    static cocos2d::Texture2D* hoeDirt;
    static cocos2d::Texture2D* tools;


    static std::string inventory;

};


#endif // _RESOURCEMANAGER_H_
