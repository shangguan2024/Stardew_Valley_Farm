#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include <unordered_map>

/// 
/// 每种 Behaviour 代表 Item 可能的附加属性，观念上在分类物品时总是会找大
/// 分类，再去找分支的分类。e.g. 我们要表示 Snapper ，首先发现 Snapper 
/// 是一种鱼，而所有的鱼在游戏种都只有两种属性：作为食物和作为钓鱼游戏的奖励，
/// 这其中食物就是一种大分类，而鱼类则是一种分支分类。除此之外，Snapper与
/// 其他鱼类在游戏中没有任何不同，所以我们不会再向下继承名为 Snapper的结构体，
/// 而是在定义这一物品时将其作为单独的变量
/// 
/// 当然分类不是唯一的，比如在许多游戏种都有鸡腿这件物品既可以作为食物，又可以
/// 作为武器，这时候并不需要多重继承，而是直接在 Item 的属性表中同时加上这两
/// 种 Behaviour* 即可
/// 
/// 这些结构体中有 map 作为成员变量的，说明其是一个大分类，map 的 Key 是
/// enum class, Value 则是他本身 Behaviour. 通过对 Key 值进行 switch
/// 可以找到对应的 Behaviour 结构体。
/// 

struct Behaviour;
// Inheritance Depth: 1
struct Block;
struct Food;
struct Tool;
struct Weapon;
// Block : Inheritance Depth: 2
struct Seed;
// Food : Inheritance Depth: 2
struct Fruit;
struct Fish;
// Tool : Inheritance Depth: 2
struct Hoe;
struct WateringCan;
struct FishingRod;
struct Scythe;
// Weapon & Fish : (max) Inheritance Depth: 3
struct SaltyFish;


struct Behaviour
{
    using this_type = Behaviour;
    const BehaviourType type = BehaviourType::Behaviour;
    const char depth = 0;

    //static std::unordered_map<BlockType, Block> behaviour_map;
    
};

struct Block : public Behaviour
{
    using this_type = Block;
    const BehaviourType type = BehaviourType::Block;
    bool init();

    const std::string& use() {
        return placedImage;
    }

public:
    cocos2d::Size area = cocos2d::Size(0, 0); // measured in tile, (row, col)
    bool passable = false;

    std::string placedImage;

    //static std::unordered_map<BlockType, Block> block_map;

};

struct Food : public Behaviour
{
    using this_type = Food;
    const BehaviourType type = BehaviourType::Food;
    bool init();

    void use(int& playerEnergy) {
        playerEnergy += energySupply;
    }

    int energySupply = 0;
    //static std::unordered_map<FoodType, Food> food_map;
};

struct Tool : public Behaviour // Branch Struct
{
    using this_type = Tool;
    const BehaviourType type = BehaviourType::Tool;
    bool init();

    //int durability; // disabled
    //static std::unordered_map<ToolType, Tool> tool_map;
};

struct Weapon : public Behaviour
{
    using this_type = Weapon;
    const BehaviourType type = BehaviourType::Weapon;
    bool init();

    int use() {
        return damage;
    }

    int damage = 0;
    float knockback = .0f;
};

// Block
struct Seed : public Block
{
    using this_type = Seed;
    const BehaviourType type = BehaviourType::Seed;
    bool init();

    cocos2d::Size Block::area = cocos2d::Size(1, 1);
    bool Block::passable = true;

    std::string Block::placedImage = "";
};

// Food
struct Fruit : public Food
{
    using this_type = Fruit;
    const BehaviourType type = BehaviourType::Fruit;
    bool init();

    using Food::use;
};

struct Fish : public Food
{
    using this_type = Fruit;
    const BehaviourType type = BehaviourType::Fish;
    bool init();

    using Food::use;
};

// Tools
struct Hoe : public Tool
{
    using this_type = Hoe;
    const BehaviourType type = BehaviourType::Hoe;
    bool init();

    const std::string& use() {
        return tilledImage;
    }

    const std::string tilledImage = "";
};

struct WateringCan : public Tool
{
    using this_type = WateringCan;
    const BehaviourType type = BehaviourType::WateringCan;
    bool init();

    const std::string& use() {
        return wateredImage;
    }

    const std::string wateredImage = "";

};

struct Scythe : public Tool
{
    using this_type = Scythe;
    const BehaviourType type = BehaviourType::Scythe;
    bool init();
    
    // use -> 收小麦等农作物、除草
};

struct FishingRod : public Tool
{
    using this_type = FishingRod;
    const BehaviourType type = BehaviourType::FishingRod;
    bool init();

    // use -> 进入钓鱼游戏
};

struct SaltyFish : virtual public Fish, virtual public Weapon
{
    using this_type = SaltyFish;
    const BehaviourType type = BehaviourType::SaltyFish;
    bool init();

    int useFish(int& player_energy) {
        Food::use(player_energy);
    }
    int useWeapon() {
        Weapon::use();
    }

    int Fish::energySupply = 12;
    int Weapon::damage = 6;
    int Weapon::knockback = 2; // measured in tile
};

#endif
