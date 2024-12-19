/****************************************************************
 * Project Name:  Stardew_Valley_Farm
 * File Name:     Constant.h
 * File Function: �������Ķ���
 * Author:        ����
 * Update Date:   2024/12/11
 ****************************************************************/

#ifndef _CONSTANT_H_
#define _CONSTANT_H_
#include <string>

constexpr int DESIGN_RESOLUTION_WIDTH = 1280;                                            // ��Ʒֱ��ʿ��
constexpr int DESIGN_RESOLUTION_HEIGHT = 720;                                            // ��Ʒֱ��ʸ߶�
constexpr int SMALL_RESOLUTION_WIDTH = 960;                                              // С�ֱ��ʿ��
constexpr int SMALL_RESOLUTION_HEIGHT = 540;                                             // С�ֱ��ʸ߶�
constexpr int MEDIUM_RESOLUTION_WIDTH = 1280;                                            // �зֱ��ʿ��
constexpr int MEDIUM_RESOLUTION_HEIGHT = 720;                                            // �зֱ��ʸ߶�
constexpr int LARGE_RESOLUTION_WIDTH = 1920;                                             // ��ֱ��ʿ��
constexpr int LARGE_RESOLUTION_HEIGHT = 1080;                                            // ��ֱ��ʸ߶�
constexpr float FRAME_RATE = 60.0f;                                                      // Ӧ�ó���֡��
const std::string APPLICATION_TITLE = u8"\u661F\u9732\u8C37\u7269\u8BED Stardew Valley"; // Ӧ�ó������

constexpr float SCENE_TRANSITION_DURATION = 0.3f; // ����ת��ʱ��

constexpr int MENU_SCENE_BUTTONS_OFFSET_Y = -200;         // �˵����水ťY��ƫ����
constexpr int MENU_SCENE_NEW_GAME_BUTTON_OFFSET_X = -400; // �˵����濪ʼ��ťX��ƫ����
constexpr int MENU_SCENE_LOAD_GAME_BUTTON_OFFSET_X = 0;   // �˵��������밴ťX��ƫ����
constexpr int MENU_SCENE_EXIT_GAME_BUTTON_OFFSET_X = 400; // �˵����������ťX��ƫ����

constexpr int DEFAULT_MUSIC_SIGN = -1;       // ȱʡ���ֱ�ʶ
constexpr float DEFAULT_MUSIC_VOLUMN = 0.5f; // ȱʡ������С

constexpr float NOMAL_PLAYER_SPEED = 100;                                       // ����Ĭ���ƶ��ٶ�
constexpr int PLAYER_IMAGE_WIDTH = 64;                                          // �����ƶ�ͼ�����
constexpr int PLAYER_IMAGE_HEIGHT = 128;                                        // �����ƶ�ͼ���߶�
constexpr int PLAYER_FRAME_RATE = 4;                                            // �����ƶ�֡��
constexpr int PLAYER_DIRECTION_NUM = 4;                                         // ������ƶ�������
constexpr int PLAYER_FRAME_WIDTH = PLAYER_IMAGE_WIDTH / PLAYER_FRAME_RATE;      // ÿ֡��ȣ�ͼƬ���/֡����
constexpr int PLAYER_FRAME_HEIGHT = PLAYER_IMAGE_HEIGHT / PLAYER_DIRECTION_NUM; // ÿ֡�߶ȣ�ͼƬ�߶�/������
constexpr float PLAYER_FRAME_DELAY = 0.1f;                                      // ÿ֡�����ӳ�

// ��ͼ
constexpr int MAP_TILE_WIDTH = 16; //
constexpr int MAP_TILE_HEIGHT = 16;
constexpr int FARMYARD_MAP_WIDTH = 100;
constexpr int FARMYARD_MAP_HEIGHT = 80;
constexpr int BEACH_MAP_WIDTH = 50;
constexpr int BEACH_MAP_HEIGHT = 50;

constexpr int DEFAULT_CAPACITY = 36; // Ĭ�ϱ�������
constexpr int DEFAULT_BAR = 12;      // Ĭ����Ʒ������

constexpr int PLAYER_MAX_STRENGTH = 100;

// �������״̬
enum class KeyControlMode
{
    PLAYER_CONTROL
};
enum class MouseControlMode
{
    INVENTORY_CONTROL,
    SCENE
};

// ��Ʒ����ö��
enum class ItemType
{
    SEED, // ����
    TOOL, // ����
    CROP  // ����
};

// ÿ����Ʒ�ľ�������
const std::string SEED_DESCRIPTION = " ";
const std::string TOOL_DESCRIPTION = " ";
const std::string CROP_DESCRIPTION = " ";

// ��������ö��
enum class ToolType
{
    HOE,          // ��ͷ
    WATERING_CAN, // ��ˮ��
    PICKAXE,      // ����
    AXE,          // ��ͷ
    SCYTHE,       // ����
    FISHING_ROD   // �����
};

// ÿ�ֹ��ܵľ�������
const std::string TOOL_HOE_DESCRIPTION = " ";
const std::string TOOL_WATERING_CAN_DESCRIPTION = " ";
const std::string TOOL_PICKAXE_DESCRIPTION = " ";
const std::string TOOL_AXE_DESCRIPTION = " ";
const std::string TOOL_SCYTHE_DESCRIPTION = " ";
const std::string TOOL_FISHING_ROD_DESCRIPTION = " ";

// ��������ö��
enum class SeedType
{
    RADISH_SEED,
    POTATO_SEED,
    WHRAT_SEED
};

// ÿ�����ӵľ�������
const std::string SEED_RADISH_DESCRIPTION = " ";
const std::string SEED_POTATO_DESCRIPTION = " ";
const std::string SEED_WHRAT_DESCRIPTION = " ";

// ��ͼ����ö��
enum class MapName {
    FarmYard,
    FarmHouse,
    Beach
};

// ��ͼ��Ƭ����
const std::string TILE_COLLIDABLE = "Collidable";

// ��ť��������
const enum ButtonType
{
    BUTTON_HIDE_INVENTORY
};

#endif // _CONSTANT_H_
