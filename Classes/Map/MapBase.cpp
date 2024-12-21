#include "MapBase.h"
#include "MapManager.h"

USING_NS_CC;

MapBase::MapBase() :
	mapName(MapName::Null),
	tileMapPath(),
	tileMap(nullptr)
{
}

void MapBase::update(float deltaTime)
{
	auto& tileData = MapManager::getInstacne()->getTileData(mapName);
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

Size MapBase::getTileSize() const
{
	if (tileMap) {
		return tileMap->getTileSize();
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

ValueMap MapBase::getPropertiesForGID(int GID) const
{
	if (tileMap) {
		return tileMap->getPropertiesForGID(GID).asValueMap();
	}
	return ValueMap();
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

// player using tool type : pass
void MapBase::interactTile(const Vec2& curPos, const Vec2& interactPos, EventMouse::MouseButton interactType)
{
	// int GID = tileMap->getLayer("Meta")->getTileGIDAt(interactPos);
	// if (!GID) {
	//	CCLOG("GID is NULL.");
	//	return;
	// }
	// float distance = curPos.distance(interactPos);
	// if (distance > 2) {
	//	CCLOG("Too far to interact");
	//	return;
	// }
	// auto properties = getPropertiesForGID(GID);
	// if (properties.size() > 1) {
	//	CCLOG("PASS");
	//	return;
	// }

	//pass
	//refs:
	// 计算玩家和鼠标之间的瓦片距离
	// float distance = sqrt(pow(currenttile.x - mousetile.x, 2) + pow(currenttile.y - mousetile.y, 2));
	// 判断距离是否小于交互范围（假设交互范围为 2）
	// if (distance > 2) {
	//	CCLOG("Too far to interact");
	// }
	// else {
	//	获取鼠标位置的瓦片 GID
	//	int mouseGID = tileLayer->getTileGIDAt(mousetile);
	//	如果 GID 不为空，表示该位置可以交互
	//	if (mouseGID) {
	//		获取瓦片属性
	//		auto properties = tileMap->getPropertiesForGID(mouseGID);
	//		if (!properties.empty()) {
	//			判断瓦片是否具有 "Plowable" 属性且为 true
	//			if (properties["Plowable"].asBool()) {
	//				执行交互操作
	//				auto Soil = Sprite::create("DrySoil.png");
	//				Soil->setAnchorPoint(Vec2(0, 0));
	//				this->addChild(Soil);
	//				Soil->setPosition(Vec2(mousetile.x * MAP_TILE_WIDTH, (FARMYARD_MAP_HEIGHT - mousetile.y) * MAP_TILE_HEIGHT));
	//				Soil->setCameraMask(unsigned short(CameraFlag::USER1));
	//				CCLOG("Interacting with plowable tile");
	//			}
	//		}
	//	}
	//	else {
	//		CCLOG("Nothing to interact");
	//	}
	// }
}

bool MapBase::init()
{
	initContants();
	tileMap = TMXTiledMap::create(tileMapPath);

	auto& tileData = MapManager::getInstacne()->getTileData(mapName);
	for (auto& data : tileData) {
		MapManager::updateTileData(data);
		setTileState(data.position, data.tileType);
	}

	return true;
}
