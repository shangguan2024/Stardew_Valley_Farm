#include "MapBase.h"
#include "MapManager.h"

USING_NS_CC;

void MapBase::update(float deltaTime)
{
	auto& tileData = MapManager::getInstacne()->getTileData(_mapName);
	for (auto& data : tileData) {
		if (MapManager::updateTileData(data)) {
			setTileState(data.position, data.tileType);
		}
	}
}

Size MapBase::getMapSize() const
{
	if (tileMap) {
		return tileMap->getMapSize();
	}
	return Size::ZERO;
}

TMXObjectGroup* MapBase::getObjectGroup(const std::string& objectGroup) const
{
	if (tileMap) {
		return tileMap->getObjectGroup(objectGroup);
	}
	return nullptr;
}

ValueMap MapBase::getObject(const std::string& objectGroup, const std::string& object) const
{
	if (tileMap) {
		return tileMap->getObjectGroup(objectGroup)->getObject(object); // not safe
	}
	return ValueMap();
}

TMXLayer* MapBase::getLayer(const std::string& layer) const
{
	if (tileMap) {
		return tileMap->getLayer(layer);
	}
	return nullptr;
}

Sprite* MapBase::getTileAt(const std::string& layer, const Vec2& position) const
{
	if (tileMap) {
		return tileMap->getLayer(layer)->getTileAt(position); // not safe
	}
	return nullptr;
}

void MapBase::setTileState(const Vec2& position, TileType tileType)
{
	switch (tileType) {
	case TileType::DrySoil:
		break;
	default:
		break;
	}
}

bool MapBase::init(MapName mapName)
{
	_mapName = mapName;
	auto& tileData = MapManager::getInstacne()->getTileData(_mapName);

	for (auto& data : tileData) {
		MapManager::updateTileData(data);
		setTileState(data.position, data.tileType);
	}

	return true;
}
