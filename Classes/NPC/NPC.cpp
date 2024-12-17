/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     NPC.cpp
 * File Function: NPC类的实现
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#include "NPC.h"

NPC::NPC() {}

NPC::~NPC() {}

bool NPC::init(const std::string& spriteFile, const NPCType& _npctype)
{
    if (!Sprite::initWithFile(spriteFile)) {
        return false;
    }

    npctype = _npctype;

    switch (npctype) {
        case NPCType::ALEX:
            dialog = NPC_ALEX_DIALOG;
            break;
        case NPCType::ABIGAIL:
            dialog = NPC_ABIGAIL_DIALOG;
            break;
        case NPCType::CAROLINE:
            dialog = NPC_CAROLINE_DIALOG;
            break;
        case NPCType::LEWIS:
            dialog = NPC_LEWIS_DIALOG;
            break;
        default:
            break;
    }

    return true;
}

NPC* NPC::create(const std::string& spriteFile, const NPCType& _npctype)
{
    NPC* npc = new(std::nothrow) NPC();
    if (npc && npc->init(spriteFile, _npctype)) {
        npc->autorelease();
        return npc;
    }
    else {
        delete npc;
        return nullptr;
    }
}

std::string NPC::getDialog()
{
	return dialog[dialogIndex];
}

void NPC::advanceDialog()
{
    if (dialogIndex < dialog.size() - 1) {
        dialogIndex++;
    }
    else {
        CCLOG("chat end");
    }
}

void NPC::jumpToDialog(int index)
{
    if (index >= 0 && index < dialog.size()) {
        dialogIndex = index;
    }
    else {
        CCLOG("invalid session index");
    }
}
