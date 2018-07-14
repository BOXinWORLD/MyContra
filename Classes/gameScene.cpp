#include "gameScene.h"
#include "SimpleAudioEngine.h"
#include "bullet.h"
#include "bombMan.h"
#define PI 3.1415926

USING_NS_CC;

Scene* gameScene::createScene()
{
	return gameScene::create();
}

// on "init" you need to initialize your instance
bool gameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//����
	map = Sprite::create("tex\\bg.jpg");
	map->setAnchorPoint(Vec2(0, 0));
	this->addChild(map);
	//��ɫ
	hero = Hero::create();
	hero->setPosition(120, 190);
	map->addChild(hero);
	//��ʾ���°�������
	label = Label::createWithTTF("PRESS", "fonts/Marker Felt.ttf", 24);
	label->setAnchorPoint(Vec2(0, 0));
	label->setPosition(200, 20);
	addChild(label);

	//�ӵ����
	isFiring = false;
	count = 0;
	//�������
	maxBombman = 10;
	bombmanCount = 0;
	//��ͼ�߽�
	mapWidth = 1000;
	//���̼���
	listenKeyboardEvent();
	//��ѭ���߼�
	this->scheduleUpdate();

	return true;
}

void gameScene::update(float dt)
{
	count++;
	//Ӣ��
	hero->update(dt);
	//��ͼ����
	float heroX = hero->getPositionX();
	mapX = map->getPositionX();
	float d = dt * 200;
	if (mapX > 512 - mapWidth) {
		if (heroX + mapX >= 256 && hero->keepRight) {
			map->setPositionX(mapX - d);
			hero->setPositionX(256 - mapX);
		}
	}
	//�߽��ж�
	if (heroX + mapX < 10) {
		hero->setPositionX(10 - mapX);
	}
	if (heroX + mapX > 502) {
		hero->setPositionX(502 - mapX);
	}
	//���
	if (isFiring&& count % 8 == 0)fire();
	moveBullets(dt);
	//��������
	if (count % 90 == 0 && bombmanCount < maxBombman) newBmobman();
	moveBombman(dt);
	//��ɱ�ж�
	hitTest();
}
//�����ӵ�
void gameScene::fire()
{
	auto b = bullet::create();
	b->radian = hero->isLeft ? PI : 0;
	b->setPositionX(hero->getPositionX() + (hero->isLeft ? -29 : 29));
	b->setPositionY(hero->getPositionY() + (hero->isDown ? 15 : 36));
	map->addChild(b);
	bullets.pushBack(b);
}
//�ƶ��ӵ�
void gameScene::moveBullets(float dt)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		auto b = bullets.at(i);
		b->update(dt);
		if (outScreen(b)) {
			b->removeFromParent();
			bullets.eraseObject(b);
			i--;
		}
	}
}

//����
void gameScene::newBmobman()
{
	bombmanCount++;
	auto bm = bombMan::create();
	bm->setPosition(535, 190);
	bm->setAnchorPoint(Vec2(0.5f, 0.0f));
	map->addChild(bm);
	bombMen.pushBack(bm);

}

void gameScene::moveBombman(float dt)
{
	for (int j = 0; j < bombMen.size(); j++)
	{
		auto bm = bombMen.at(j);
		bm->update(dt);
		if (outScreen(bm)) {
			bm->removeFromParent();
			bombMen.eraseObject(bm);
			j--;
		}
	}
}

//��ɱ����
void gameScene::hitTest() {
	for (int i = 0; i < bullets.size(); i++)
	{
		auto b = bullets.at(i);
		auto bRect = Rect(b->getPositionX(), b->getPositionY(), 10, 10);
		for (int j = 0; j < bombMen.size(); j++)
		{
			auto bm = bombMen.at(j);
			auto bmRect = Rect(bm->getPositionX(), bm->getPositionY(), 35, 48);
			if (bRect.intersectsRect(bmRect))
			{
				b->removeFromParent();
				bullets.eraseObject(b);
				i--;
				bm->removeFromParent();
				bombMen.eraseObject(bm);
				j--;	
			}
		}
	}
}

void gameScene::listenKeyboardEvent()
{
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(gameScene::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(gameScene::onKeyReleased2, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void gameScene::onKeyPressed2(EventKeyboard::KeyCode code, Event * evt)
{
		char txt[100] = {};
		sprintf_s(txt, "%d is Pressed", (int)code);
		label->setString(txt);

		switch ((int)code)
		{
		case 59:
			isFiring = true;
			break;
		default:
			break;
		}

}

void gameScene::onKeyReleased2(EventKeyboard::KeyCode code, Event * evt)
{
	switch ((int)code)
	{
	case 59:
		isFiring = false;
		break;
	default:
		break;
	}
}
//�����ж�
bool gameScene::outScreen(Node * n)
{
	if (n->getPositionX() < -20-mapX || n->getPositionX() > 550-mapX ||
		n->getPositionY() < -20 || n->getPositionY() > 500 )
		return true;
	return false;
}

