#include "Player.h"

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
		InputManager::getInstance()->setCurrentKeyControlMode(KeyControlMode::PLAYER_CONTROL);
	}
	return _instance;
}

// ���캯��
Player::Player() : _direction(Vec2::ZERO), _speed(NOMAL_PLAYER_SPEED), _currentAnimationHash(0) {}

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

	// ע�� update
	this->scheduleUpdate();

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

// ÿ֡����
void Player::update(float delta)
{
	// ���û�з������룬ֹͣ����
	updateDirection();
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

void Player::updateDirection()
{
	cocos2d::Vec2 dir = Vec2::ZERO;
	auto inputManager = InputManager::getInstance();

	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_W, KeyControlMode::PLAYER_CONTROL)) {
		dir.y += 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_A, KeyControlMode::PLAYER_CONTROL)) {
		dir.x -= 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_S, KeyControlMode::PLAYER_CONTROL)) {
		dir.y -= 1.0f;
	}
	if (inputManager->isKeyPressed(cocos2d::EventKeyboard::KeyCode::KEY_D, KeyControlMode::PLAYER_CONTROL)) {
		dir.x += 1.0f;
	}

	setDirection(dir);
}

// ����ʵ��
void Player::destroyInstance()
{
	InputManager::getInstance()->popCurrentKeyControlMode();
	CC_SAFE_DELETE(_instance);
}
