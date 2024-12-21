#include "Player.h"
#include "UI/UIManager.h"

USING_NS_CC;

// ��̬ʵ����ʼ��
Player* Player::_instance = nullptr;

// ��ȡ����ʵ��
Player* Player::getInstance()
{
	if (_instance == nullptr) {
		// ʹ�� no-throw �����ڴ�
		_instance = new (std::nothrow) Player();
		// ��ʼ��ʧ��������ʵ��
		if (!_instance || !_instance->init()) {
			CC_SAFE_DELETE(_instance);
		}
	}
	return _instance;
}

// ���캯��
Player::Player() :
	_currentAnimationHash(0),
	playerEnterType(PlayerEnterType::SPAWN),
	_direction(Vec2::ZERO),
	_speed(NOMAL_PLAYER_SPEED),
	_isFreeze(false),
	energy(PLAYER_MAX_STRENGTH)
{
}

// ��������
Player::~Player()
{
	// ��������ƶ���������
	AnimationCache::getInstance()->removeAnimation("WALK_DOWN");
	AnimationCache::getInstance()->removeAnimation("WALK_RIGHT");
	AnimationCache::getInstance()->removeAnimation("WALK_UP");
	AnimationCache::getInstance()->removeAnimation("WALK_LEFT");

	// ���ø���������������ͷ� Sprite ��Դ
	Sprite::~Sprite();
}

// ��ʼ��
bool Player::init()
{
	if (!Sprite::init()) {
		return false;
	}

	// ��ʼ����������
	auto texture = Director::getInstance()->getTextureCache()->addImage("Player/Sandy.png");

	// �ü���ʼͼ��
	Rect rect(0, PLAYER_IMAGE_HEIGHT - PLAYER_FRAME_HEIGHT, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT);

	// �����ü������ľ���֡
	auto frame = SpriteFrame::createWithTexture(texture, rect);
	frame->setAnchorPoint(Vec2(0.5f, 0.1f));

	if (frame) {
		// ���þ���ĳ�ʼͼ��Ϊ�ü������Ĳ���
		this->setSpriteFrame(frame);
	}
	else {
		CCLOG("Failed to create sprite from the specified rect");
		return false;
	}

	// �����򴴽�����
	for (int row = 0; row < PLAYER_DIRECTION_NUM; row++) {
		Vector<SpriteFrame*> frames;
		for (int col = 0; col < PLAYER_FRAME_RATE; col++) {
			int x = col * PLAYER_FRAME_WIDTH;
			int y = row * PLAYER_FRAME_HEIGHT;
			auto frame = SpriteFrame::createWithTexture(texture, Rect(x, y, PLAYER_FRAME_WIDTH, PLAYER_FRAME_HEIGHT));
			frames.pushBack(frame);
		}

		// ���ö�����
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

		// ���涯��
		auto animation = Animation::createWithSpriteFrames(frames, PLAYER_FRAME_DELAY);
		AnimationCache::getInstance()->addAnimation(animation, key);
	}

	return true;
}

// ���÷���
void Player::setDirection(const Vec2& direction)
{
	// ��֤����������һ��
	_direction = direction.getNormalized();
}

// ��ȡ����
Vec2 Player::getDirection() const
{
	return _direction;
}

// �����ٶ�
void Player::setSpeed(const float speed)
{
	_speed = speed;
}

// ��ȡ�ٶ�
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

// ÿ֡����
void Player::update(float delta)
{
	// ���û�з������룬ֹͣ����
	if (_direction.isZero()) {
		this->stopActionByTag(_currentAnimationHash); // ʹ�õ�ǰ�����Ĺ�ϣֵ��ֹͣ����
		_currentAnimationHash = 0;
		return;
	}

	// �жϵ�ǰ�ķ������ö����ؼ���
	std::string animationKey;
	if (_direction.x < 0) {
		animationKey = "WALK_LEFT"; // ����
	}
	else if (_direction.x > 0) {
		animationKey = "WALK_RIGHT"; // ����
	}
	else if (_direction.y > 0) {
		animationKey = "WALK_UP";   // ����
	}
	else if (_direction.y < 0) {
		animationKey = "WALK_DOWN"; // ����
	}

	// ��ȡ�����Ĺ�ϣֵ�������ж��Ƿ��ظ�����
	size_t animationHash = std::hash<std::string>()(animationKey);

	// �����ǰ���ڲ���Ŀ�궯����ֱ�ӷ���
	if (_currentAnimationHash == animationHash) {
		return;
	}

	// ֹͣ��ǰ����
	this->stopActionByTag(_currentAnimationHash);
	auto animation = AnimationCache::getInstance()->getAnimation(animationKey);
	if (animation) {
		auto animate = Animate::create(animation);
		auto repeat = RepeatForever::create(animate);
		// ʹ�ö�����ϣֵ��Ϊtag
		repeat->setTag(animationHash);
		this->runAction(repeat);
		// ���µ�ǰ������ϣֵ
		_currentAnimationHash = animationHash;
	}
}

// ����ʵ��
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
