#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include <unordered_map>

/// 
/// ÿ�� Behaviour ���� Item ���ܵĸ������ԣ��������ڷ�����Ʒʱ���ǻ��Ҵ�
/// ���࣬��ȥ�ҷ�֧�ķ��ࡣe.g. ����Ҫ��ʾ Snapper �����ȷ��� Snapper 
/// ��һ���㣬�����е�������Ϸ�ֶ�ֻ���������ԣ���Ϊʳ�����Ϊ������Ϸ�Ľ�����
/// ������ʳ�����һ�ִ���࣬����������һ�ַ�֧���ࡣ����֮�⣬Snapper��
/// ������������Ϸ��û���κβ�ͬ���������ǲ��������¼̳���Ϊ Snapper�Ľṹ�壬
/// �����ڶ�����һ��Ʒʱ������Ϊ�����ı���
/// 
/// ��Ȼ���಻��Ψһ�ģ������������Ϸ�ֶ��м��������Ʒ�ȿ�����Ϊʳ��ֿ���
/// ��Ϊ��������ʱ�򲢲���Ҫ���ؼ̳У�����ֱ���� Item �����Ա���ͬʱ��������
/// �� Behaviour* ����
/// 
/// ��Щ�ṹ������ map ��Ϊ��Ա�����ģ�˵������һ������࣬map �� Key ��
/// enum class, Value ���������� Behaviour. ͨ���� Key ֵ���� switch
/// �����ҵ���Ӧ�� Behaviour �ṹ�塣
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
    
    // use -> ��С���ũ�������
};

struct FishingRod : public Tool
{
    using this_type = FishingRod;
    const BehaviourType type = BehaviourType::FishingRod;
    bool init();

    // use -> ���������Ϸ
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
