#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>


class Texture
{
public:
    // Animals
    static const std::string BabyBrownChicken;
    static const std::string BabySheep;       
    static const std::string BabyWhiteChicken;
    static const std::string BrownChicken;    
    static const std::string Sheep;           
    static const std::string WhiteChicken;    

    // Characters & Portraits
    static const std::string EmilyCharacter; 
    static const std::string LewisCharacter; 
    static const std::string PierreCharacter;
    static const std::string RobinCharacter; 
    static const std::string EmilyPortrait;  
    static const std::string LewisPortrait;  
    static const std::string PierrePortrait; 
    static const std::string RobinPortrait;  

    // Fonts
    static const std::string BorderFont_BR;
    static const std::string Mojangles;

    // Items
    static const std::string Craftables;   
    static const std::string crops;        
    static const std::string hoeDirt;      
    static const std::string hoeDirtDark;  
    static const std::string rain;         
    static const std::string tools;        
    static const std::string weapons;      
    static const std::string springobjects;

    // Player
    static const std::string Dana;     
    static const std::string Sandy;    
    static const std::string emotes;   

    // Scenes
    static const std::string MenuScene;

    // UI
    static const std::string Billboard;      
    static const std::string Cursors;        
    static const std::string Inventory;      
    static const std::string letterBG;       
    static const std::string logo;           
    static const std::string TitleButtons;   
    // UI - Buttons
    static const std::string HideInventory;

    // World
    static const std::string bushes;         
    static const std::string tree1_fall;     
    static const std::string tree2_fall;     
    static const std::string tree3_fall;     
    static const std::string ElliottSeaTiles;
    static const std::string houses;          
    static const std::string Mill;            
    static const std::string Well;            
    static const std::string fall_outdoorsTileSheet;
    static const std::string fall_beach;            
    static const std::string fall_town;             
    
    // Tile Maps
    static const std::string FarmYardScene;
    static const std::string Beach;
};

#endif