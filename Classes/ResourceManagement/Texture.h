#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "cocos2d.h"


struct TextureTile
{
    int row;
    int col;
    int height;
    int width;

    TextureTile() : TextureTile(0, 0, 0, 0) {}
    TextureTile(int r, int c, int h, int w)
        : row(r), col(c), height(h), width(w) {}

    cocos2d::Rect toRect()
    {
        return cocos2d::Rect(col*16, row*16, width*16, height*16);
    }

    //TextureTile& operator=(const TextureTile& other)
    //{
    //    row = other.row;
    //    col = other.col;
    //    height = other.height;
    //    width = other.width;
    //    return *this;
    //}
};

enum class Texture {
    NIL,
    springobjects,
    crops,
    hoeDirt,
    tools,

};

#endif