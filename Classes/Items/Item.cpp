#include "Item.h"

USING_NS_CC;

Item::Item()
    : Item(Item::NIL, "") {}

Item::Item(Item::ID new_id)
    : Item(new_id, "") {}

Item::Item(Item::ID new_id, std::string new_name)
    : icon(nullptr),
    id(new_id), 
    name(new_name),
    description(""),
    flag(ItemTag::Behaviour)
{
}

Item::Item(Item&& other)
    : icon(icon),
    name(std::move(other.name)),
    description(std::move(other.description))
{
    id = other.id;
    flag = other.flag;
}

Item& Item::operator=(Item&& other)
{
    name = std::move(other.name);
    description = std::move(other.description);
    id = other.id;
    flag = other.flag;
    return *this;
}
