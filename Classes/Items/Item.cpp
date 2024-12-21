#include "Item.h"

USING_NS_CC;

Item::Item()
    : Item(Item::NIL, "") {}

Item::Item(Item::ID new_id)
    : Item(new_id, "") {}

Item::Item(Item::ID new_id, std::string new_name)
    : id(new_id), 
    name(new_name),
    description(""),
    flag(ItemTag::Default),
    icon_path(nullptr),
    icon_frame()
{
}

Item::Item(Item&& other)
    : name(std::move(other.name)),
    description(std::move(other.description)),
    id(other.id),
    flag(other.flag),
    icon_path(std::move(other.icon_path)),
    icon_frame(other.icon_frame),
    behaviour_table(std::move(other.behaviour_table))
{
}

Item& Item::operator=(Item&& other)
{
    name = std::move(other.name);
    description = std::move(other.description);
    id = other.id;
    flag = other.flag;
    icon_path = std::move(other.icon_path);
    icon_frame = other.icon_frame;
    behaviour_table = std::move(other.behaviour_table);
    return *this;
}

void Item::clear()
{
    name = "";
    description = "";
    id = Item::NIL;
    flag = ItemTag::Default;
    icon_path = nullptr;
    icon_frame = TextureTile();
}
