#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

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

class ResourceManager
{
public:
    struct Tile
    {
        int row;
        int col;
        int width;
        int height;

        Tile(int r, int c, int w, int h)
            : row(r), col(c), width(w), height(h) {}

        cocos2d::Rect toRect()
        {
            return cocos2d::Rect(col*16, row*16, width*16, height*16);
        }
    };

    static ResourceManager* getInstance();
    bool init();

    void updateRect();
    void loadResouces();
    void loadUIPath();

    cocos2d::Sprite* getItem(Item::ID id);
    inline cocos2d::Sprite* getItem(std::string name);
    cocos2d::Label* getLabel(const std::string& text, const int SystemFontSize = 24);
    cocos2d::ui::Button* getButton(ButtonType bfd);




private:
    static ResourceManager* instance;

    // A Rectangent region of some Texture in where the required item is
    // the index is ID
    static cocos2d::Rect itemRect[1024];
    static cocos2d::Rect blockRect[1024];

    // Texture in where the required item is (Rsc : Resource)
    static cocos2d::Texture2D* itemRsc[1024];
    static cocos2d::Texture2D* blockRsc[1024];

    static cocos2d::Texture2D* springobjects;
    static cocos2d::Texture2D* blockTexture;

    static std::string inventory;

};


#endif // _RESOURCEMANAGER_H_
