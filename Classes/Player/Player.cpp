#include "Player.h"
#include "UI/UIManager.h"

USING_NS_CC;

// 静态实例初始化
Player* Player::_instance = nullptr;

// 获取单例实例
Player* Player::getInstance()
{
	if (_instance == nullptr) {
		// 使用 no-throw 分配内存
		_instance = new (std::nothrow) Player();
		// 初始化失败则销毁实例
		if (!_instance || !_instance->init()) {
			CC_SAFE_DELETE(_instance);
		}
	}
	return _instance;
}

// 构造函数
Player::Player() :
	_currentAnimationHash(0),
	playerEnterType(PlayerEnterType::SPAWN),
	_direction(Vec2::ZERO),
	_speed(NOMAL_PLAYER_SPEED),
	_isFreeze(false),
	energy(PLAYER_MAX_STRENGTH)
{
}

// 析构函数
Player::~Player()
{
	// 清除人物移动动画缓存
	AnimationCache::getInstance()->removeAnimation("WALK_DOWN");
	AnimationCache::getInstance()->removeAnimation("WALK_RIGHT");
	AnimationCache::getInstance()->removeAnimation("WALK_UP");
	AnimationCache::getInstance()->removeAnimation("WALK_LEFT");

	// 调用父类的析构函数以释放 Sprite 资源
	Sprite::~Sprite();
}

// 初始化
bool Player::init()
{
	if (!Sprite::init()) {
		return false;
	}

	// 初始化动画缓存
	auto texture = Director::getInstance()->getTextureCache()->addImage("Player/Sandy.png");

	// 裁剪初始图像
	Rect rect(0, PLAYER_IMAGE_HEIGHT - PLAYER_FRAME_HEIGHT, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT);

	// 创建裁剪出来的精灵帧
	auto frame = SpriteFrame::createWithTexture(texture, rect);
	frame->setAnchorPoint(Vec2(0.5f, 0.1f));

	if (frame) {
		// 设置精灵的初始图像为裁剪出来的部分
		this->setSpriteFrame(frame);
	}
	else {
		CCLOG("Failed to create sprite from the specified rect");
		return false;
	}

	// 按方向创建动画
	for (int row = 0; row < PLAYER_DIRECTION_NUM; row++) {
		Vector<SpriteFrame*> frames;
		for (int col = 0; col < PLAYER_FRAME_RATE; col++) {
			int x = col * PLAYER_FRAME_WIDTH;
			int y = row * PLAYER_FRAME_HEIGHT;
			auto frame = SpriteFrame::createWithTexture(texture, Rect(x, y, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT));
			frames.pushBack(frame);
		}

		// 设置动画键
		std::string key;
		switch (row) {
		case 0:
			key = "WALK_DOWN";
			break;
		case 1:
			key = "WALK_RIGHT";
			break;
		case 2:
			key = "WALK_UP";
			break;
		case 3:
			key = "WALK_LEFT";
			break;
		}

		// 缓存动画
		auto animation = Animation::createWithSpriteFrames(frames, PLAYER_FRAME_DELAY);
		AnimationCache::getInstance()->addAnimation(animation, key);
	}

	return true;
}

// 设置方向
void Player::setDirection(const Vec2& direction)
{
	// 保证方向向量归一化
	_direction = direction.getNormalized();
}

// 获取方向
Vec2 Player::getDirection() const
{
	return _direction;
}

// 设置速度
void Player::setSpeed(const float speed)
{
	_speed = speed;
}

// 获取速度
float Player::getSpeed() const
{
	return _speed;
}

bool Player::isFreeze() const
{
	return _isFreeze;
}

void Player::freeze()
{
	_isFreeze = true;
	setDirection(Vec2::ZERO);
	InputManager::getInstance()->clearPollingStates();
}

void Player::unFreeze()
{
	_isFreeze = false;
}

void Player::setStrength(const int strength)
{
	energy = strength;
	HUD::getInstance()->updateStrengthBarHUD();
}

int Player::getEnergy() const
{
	return energy;
}

void Player::addEnergy(const int _energy)
{
	energy += _energy;
	energy = std::max(std::min(energy, PLAYER_MAX_STRENGTH), 0);
	HUD::getInstance()->updateStrengthBarHUD();
}

void Player::onEnter()
{
	Sprite::onEnter();

	this->scheduleUpdate();
}

void Player::onExit()
{
	Sprite::onExit();

	this->unscheduleUpdate();
}

// 每帧更新
void Player::update(float delta)
{
	// 如果没有方向输入，停止动画
	if (_direction.isZero()) {
		this->stopActionByTag(_currentAnimationHash); // 使用当前动画的哈希值来停止动画
		_currentAnimationHash = 0;
		return;
	}

	// 判断当前的方向并设置动画关键字
	std::string animationKey;
	if (_direction.x < 0) {
		animationKey = "WALK_LEFT"; // 向左
	}
	else if (_direction.x > 0) {
		animationKey = "WALK_RIGHT"; // 向右
	}
	else if (_direction.y > 0) {
		animationKey = "WALK_UP";   // 向上
	}
	else if (_direction.y < 0) {
		animationKey = "WALK_DOWN"; // 向下
	}

	// 获取动画的哈希值，用于判断是否重复播放
	size_t animationHash = std::hash<std::string>()(animationKey);

	// 如果当前正在播放目标动画，直接返回
	if (_currentAnimationHash == animationHash) {
		return;
	}

	// 停止当前动画
	this->stopActionByTag(_currentAnimationHash);
	auto animation = AnimationCache::getInstance()->getAnimation(animationKey);
	if (animation) {
		auto animate = Animate::create(animation);
		auto repeat = RepeatForever::create(animate);
		// 使用动画哈希值作为tag
		repeat->setTag(animationHash);
		this->runAction(repeat);
		// 更新当前动画哈希值
		_currentAnimationHash = animationHash;
	}
}

// 销毁实例
void Player::destroyInstance()
{
	InputManager::getInstance()->resetCurrentKeyControlMode("player");
	CC_SAFE_DELETE(_instance);
}

PlayerEnterType Player::enterType()
{
	return playerEnterType;
}

void Player::setEnterType(const PlayerEnterType& enterType)
{
	playerEnterType = enterType;
}
