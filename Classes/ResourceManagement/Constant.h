/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Constant.h
 * File Function: 常变量的定义
 * Author:        张翔
 * Update Date:   2024/12/11
 ****************************************************************/

#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include <string>

constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                                            // 设计分辨率宽度
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                                            // 设计分辨率高度
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                              // 小分辨率宽度
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                             // 小分辨率高度
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                                            // 中分辨率宽度
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                                            // 中分辨率高度
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                             // 大分辨率宽度
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                                            // 大分辨率高度
constexpr float FRAME_RATE = 60.0f;                                                      // 应用程序帧率
const std::string APPLICATION_TITLE = u8"\u661F\u9732\u8C37\u7269\u8BED Stardew Valley"; // 应用程序标题

constexpr float SCENE_TRANSITION_DURATION = 0.3f; // 场景转换时长

constexpr int MENU_SCENE_BUTTONS_OFFSET_Y = -200;         // 菜单界面按钮Y轴偏移量
constexpr int MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X = -400; // 菜单界面开始按钮X轴偏移量
constexpr int MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X = 0;   // 菜单界面载入按钮X轴偏移量
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X = 400; // 菜单界面结束按钮X轴偏移量

constexpr int DEFAULT_MUSIC_SIGN = -1;       // 缺省音乐标识
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f; // 缺省音量大小

constexpr float NOMAL_PLAYER_SPEED = 100;                                       // 人物默认移动速度
constexpr int PLAYER_IMAGE_WIDTH = 64;                                          // 人物移动图集宽度
constexpr int PLAYER_IMAGE_HEIGHT = 128;                                        // 人物移动图集高度
constexpr int PLAYER_FRAME_RATE = 4;                                            // 人物移动帧数
constexpr int PLAYER_DIRECTION_NUM = 4;                                         // 人物可移动方向数
constexpr int PLAYER_FRAME_WIDTH = PLAYER_IMAGE_WIDTH / PLAYER_FRAME_RATE;      // 每帧宽度（图片宽度/帧数）
constexpr int PLAYER_FRAME_HEIGHT = PLAYER_IMAGE_HEIGHT / PLAYER_DIRECTION_NUM; // 每帧高度（图片高度/行数）
constexpr float PLAYER_FRAME_DELAY = 0.1f;                                      // 每帧动画延迟

// 地图
constexpr int MAP_TILE_WIDTH = 16; //
constexpr int MAP_TILE_HEIGHT = 16;
constexpr int MAP_TILE_SIDE_LENGTH = 16; // if MAP_TILE_WIDTH == MAP_TILE_HEIGHT
constexpr int FARMYARD_MAP_WIDTH = 100;
constexpr int FARMYARD_MAP_HEIGHT = 80;
constexpr int BEACH_MAP_WIDTH = 50;
constexpr int BEACH_MAP_HEIGHT = 50;

constexpr int DEFAULT_CAPACITY = 36; // 默认背包容量
constexpr int DEFAULT_BAR = 12;      // 默认物品栏容量

constexpr int PLAYER_MAX_STRENGTH = 100;

// 键鼠控制状态
enum class KeyControlMode {
	PLAYER_CONTROL
};
enum class MouseControlMode {
	INVENTORY_CONTROL,
	SCENE
};

// 人物位置生成方式
enum class PlayerEnterType {
	SPAWN,
	FROM_PORTAL
};


// 物品种类枚举
enum class ItemTag {
	Behaviour, // Default Type - NULL
	Block, // Placeable
	Food,
	Tool,
	Weapon,

	Fruit,
	Seed,
	Fish

	//SaltyFish // SaltyFish = Food + Weapon

};

//// 每种物品的具体描述
//const std::string SEED_DESCRIPTION = " ";
//const std::string TOOL_DESCRIPTION = " ";
//const std::string CROP_DESCRIPTION = " ";
//
//// 工具类型枚举
//enum class ToolType {
//	Hoe,
//	Scythe,
//	WateringCan,
//	FishingRod
//	//HOE,          // 锄头
//	//WATERING_CAN, // 浇水壶
//	//PICKAXE,      // 镐子
//	//AXE,          // 斧头
//	//SCYTHE,       // 镰刀
//	//FISHING_ROD   // 钓鱼竿
//};

// 每种功能的具体描述
const std::string TOOL_HOE_DESCRIPTION = " ";
const std::string TOOL_WATERING_CAN_DESCRIPTION = " ";
const std::string TOOL_PICKAXE_DESCRIPTION = " ";
const std::string TOOL_AXE_DESCRIPTION = " ";
const std::string TOOL_SCYTHE_DESCRIPTION = " ";
const std::string TOOL_FISHING_ROD_DESCRIPTION = " ";

enum class BehaviourType {
	Behaviour,
	// Inheritance Depth: 1
	Block,
	Food,
	Tool,
	Weapon,
	// Block : Inheritance Depth: 2
	Seed,
	// Food : Inheritance Depth: 2
	Fruit,
	Fish,
	// Tool : Inheritance Depth: 2
	Hoe,
	WateringCan,
	FishingRod,
	Scythe,
	// Fish & Weapon : (max) Inheritance Depth: 3
	SaltyFish
};

// 种子类型枚举
enum class SeedType {
	RADISH_SEED,
	POTATO_SEED,
	WHRAT_SEED
};

// 每种种子的具体描述
const std::string SEED_RADISH_DESCRIPTION = " ";
const std::string SEED_POTATO_DESCRIPTION = " ";
const std::string SEED_WHRAT_DESCRIPTION = " ";

// 地图名称枚举
enum class MapName {
    Null,
    FarmYard,
    FarmHouse,
    Beach
};

// 地图瓦片属性
const std::string TILE_COLLIDABLE = "Collidable";

// 瓦片动态类型
enum class TileType {
	DrySoil,
	WetSoil
};

// 按钮功能描述
enum ButtonType {
	BUTTON_HIDE_INVENTORY
};

// 摄像机
constexpr float CAMERA_FOV = 60.0;
constexpr float CAMERA_Z = 128.0;

// 资源路径

namespace Resources
{
// Animals
const std::string BabyBrownChicken = "Entities/Animals/BabyBrown Chicken..png";
const std::string BabySheep = "Entities/Animals/BabySheep..png";
const std::string BabyWhiteChicken = "Entities/Animals/BabyWhite Chicken..png";
const std::string BrownChicken = "Entities/Animals/Brown Chicken..png";
const std::string Sheep = "Entities/Animals/Sheep..png";
const std::string WhiteChicken = "Entities/Animals/White Chicken..png";

// Characters & Po
const std::string EmilyCharacter = "Entities/Characters/Emily..png";
const std::string LewisCharacter = "Entities/Characters/Lewis..png";
const std::string PierreCharacter = "Entities/Characters/Pierre..png";
const std::string RobinCharacter = "Entities/Characters/Robin..png";
const std::string EmilyPortrait = "Entities/Portraits/Emily..png";
const std::string LewisPortrait = "Entities/Portraits/Lewis..png";
const std::string PierrePortrait = "Entities/Portraits/Pierre..png";
const std::string RobinPortrait = "Entities/Portraits/Robin..png";

// Fonts
const std::string BorderFont_BR = "Fonts/BorderFont.pt-BR.texture.png";
const std::string Mojangles = "Fonts/Mojangles.ttf";

// Items
const std::string Craftables = "Items/Craftables..png";
const std::string crops = "Items/crops..png";
const std::string hoeDirt = "Items/hoeDirt..png";
const std::string hoeDirtDark = "Items/hoeDirtDark..png";
const std::string rain = "Items/rain..png";
const std::string tools = "Items/tools..png";
const std::string weapons = "Items/weapons..png";
const std::string springobjects = "Items/springobjects..png";

// Player
const std::string Dana = "Player/Dana.png";
const std::string Sandy = "Player/Sandy.png";
const std::string emotes = "Player/emotes..png";

// Scenes
const std::string MenuScene = "Scenes/MenuScene.png";

// UI
const std::string Billboard = "UI/Billboard..png";
const std::string Cursors = "UI/Cursors..png";
const std::string Inventory = "UI/Inventory.png";
const std::string letterBG = "UI/letterBG..png";
const std::string logo = "UI/logo..png";
const std::string TitleButtons = "UI/TitleButtons..png";
// UI - Buttons
const std::string HideInventory = "UI/Buttons/HideInventory.png";

// World
const std::string bushes = "World/bushes..png";
const std::string tree1_fall = "World/tree1_fall..png";
const std::string tree2_fall = "World/tree2_fall..png";
const std::string tree3_fall = "World/tree3_fall..png";
const std::string ElliottSeaTiles = "World/ElliottSeaTiles..png";
const std::string houses = "World/houses..png";
const std::string Mill = "World/Mill..png";
const std::string Well = "World/Well..png";
const std::string fall_outdoorsTileSheet = "World/fall_outdoorsTileSheet..png";
const std::string fall_beach = "World/beach/fall_beach..png";
const std::string fall_town = "World/fall_town..png";

// Tile Maps
const std::string FarmYardMap= "World/FarmYard/FarmYardScene.tmx";
const std::string BeachMap = "World/Beach/fall_beach.tmx";


// Item Icon
const std::string NIL = "";
const std::string Bread = "";


}

#endif // _CONSTANT_H_
