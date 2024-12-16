/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     NPC.h
 * File Function: NPC类的定义
 * Author:        张翔
 * Update Date:   2024/12/16
 ****************************************************************/

#ifndef _NPC_H_
#define _NPC_H_

#include "cocos2d.h"
#include "proj.win32/Constant.h"

class NPC :public cocos2d::Sprite
{
public:

	// 初始化
	bool init(const std::string& spriteFile, const NPCType& _npctype);

	// 创建NPC
	static NPC* create(const std::string& spriteFile, const NPCType& _npctype);

	std::string getDialog();

	// 推进到下一个对话
	void advanceDialog();

	// 跳转到指定的对话
	void jumpToDialog(int index);

private:

	NPC();    // 构造函数
	~NPC();   // 析构函数

	NPCType npctype;                  // NPC 的名称
	std::vector<std::string> dialog;  // NPC 的对话内容
	int dialogIndex = 0;              // 当前对话的索引

};

#endif // _NPC_H_
