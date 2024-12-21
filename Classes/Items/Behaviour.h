#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "cocos2d.h"
#include "ResourceManagement/Constant.h"
#include "ResourceManagement/Texture.h"

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

    bool stackable = true;
    bool disposable = true;
    //static std::unordered_map<BlockType, Block> behaviour_map;
    
};

struct Block : public Behaviour
{
    using this_type = Block;
    const BehaviourType type = BehaviourType::Block;
    bool init();


public:
    cocos2d::Size area = cocos2d::Size(0, 0); // measured in tile, (row, col)
    bool passable = false;

    Texture placed_icon_path;
    TextureTile placed_icon_frame;
    //static std::unordered_map<BlockType, Block> block_map;

};

struct Food : public Behaviour
{
    using this_type = Food;
    const BehaviourType type = BehaviourType::Food;
    bool init();

    int energy_supply = 0;
    //static std::unordered_map<FoodType, Food> food_map;
};

struct Tool : public Behaviour // Branch Struct
{
    using this_type = Tool;
    const BehaviourType type = BehaviourType::Tool;
    bool init()
    {
        stackable = false;
        disposable = false;
    }

    //int durability; // disabled
    Texture use_image; // store the anime assets when you use it
    TextureTile use_frame[5]; // 5 frames of anime, each frame has a texture frame...
    
    //static std::unordered_map<ToolType, Tool> tool_map;
};

struct Weapon : public Behaviour
{
    using this_type = Weapon;
    const BehaviourType type = BehaviourType::Weapon;
    bool init();

    int damage = 0;
    float knockback = 0.0f;
};

// Block
struct Seed : public Block
{
    using this_type = Seed;
    const BehaviourType type = BehaviourType::Seed;
    bool init()
    {
        area = cocos2d::Size(1, 1);
        passable = true;

        placed_icon_path = Texture::crops;
    }
};

// Food
struct Fruit : public Food
{
    using this_type = Fruit;
    const BehaviourType type = BehaviourType::Fruit;
    bool init();

};

struct Fish : public Food
{
    using this_type = Fruit;
    const BehaviourType type = BehaviourType::Fish;
    bool init();

};

// Tools
struct Hoe : public Tool
{
    enum TilledDirt // Please Don't change the order in it.
    {
        Single, UpLeft, FlatUp, UpRight,
        Up, FlatLeft, Center, FlatRight,
        Vertical, DownLeft, FlatDown, DownRight,
        Down, Left, Horizontal, Right,
    };

    using this_type = Hoe;
    const BehaviourType type = BehaviourType::Hoe;
    bool init()
    {
        use_image = Texture::tools;
        for (int i = 0; i < 5; ++i)
        {
            use_frame[i] = TextureTile(1, i + 14, 2, 1);    // +14 means steel
        }
        for (int i = 0; i < 16; ++i)
        {
            tilled_frame[i] = TextureTile(i / 4, i % 4, 1, 1);
        }
    }
    
    const Texture tilled_image = Texture::hoeDirt;
    TextureTile tilled_frame[15];
};

struct WateringCan : public Tool
{
    using WateredDirt = Hoe::TilledDirt;
    enum WaterDir {
        FrontFirst,
        FrontSecond,
        RightFirst,
        RightSecond,
        Back
    };

    using this_type = WateringCan;
    const BehaviourType type = BehaviourType::WateringCan;

    bool init()
    {
        use_image = Texture::tools;
        for (int i = 0; i < 5; ++i)
        {
            use_frame[i] = TextureTile(13, i + 14, 2, 1);    // +14 means steel
        }
        for (int i = 0; i < 16; ++i)
        {
            tilled_frame[i] = TextureTile(i / 4, i % 4, 1, 1);
        }
    }

    const Texture tilled_image = Texture::hoeDirt;
    TextureTile tilled_frame[15];
    int storage = 16;

};

// Not implemented.
struct Scythe : public Tool
{
    using this_type = Scythe;
    const BehaviourType type = BehaviourType::Scythe;
    bool init();
    
    // use -> ��С���ũ�������
};

// Not implemented.
struct FishingRod : public Tool
{
    using this_type = FishingRod;
    const BehaviourType type = BehaviourType::FishingRod;
    bool init();

    // use -> ���������Ϸ
};

#endif
