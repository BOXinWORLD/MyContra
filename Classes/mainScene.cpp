#include "mainScene.h"
#include "SimpleAudioEngine.h"
#include "gameScene.h"

USING_NS_CC;

Scene* mainScene::createScene()
{
	return mainScene::create();
}

// on "init" you need to initialize your instance
bool mainScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	auto bg = Sprite::create("tex\\MainBG.jpg");
	bg->setAnchorPoint(Vec2(0, 0));
	//bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//Size size_back = bg->getContentSize();  //��ȡ�����С(����ͼƬ��ʱ�򣬾����СΪͼƬ��С)  
													 //����ʵ�ʿ�Ⱥ��ܿ�ȣ������������ű���  
	//float scaleX = (float)514/ (float)size_back.width;
	//float scaleY = (float)480 / (float)size_back.height;
	bg->setScale(1.6f, 1.6f);    //����  
	this->addChild(bg);
	//add KeyboardListener
	listenKeyboardEvent();
	//add label
	label = Label::createWithTTF("PRESS ENTER", "fonts/Marker Felt.ttf", 24);
	label ->setAnchorPoint(Vec2(0, 0));
	label ->setPosition(200,20);
	//keep blink
	Blink * blink = Blink::create(2.0f, 2);
	RepeatForever *rblink = RepeatForever::create(blink);
	label->runAction(rblink);
	this->addChild(label);
	

	return true;
}

void mainScene::listenKeyboardEvent()
{
	this->_eventDispatcher->removeAllEventListeners();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(mainScene::onKeyPressed2, this);
	listener->onKeyReleased = CC_CALLBACK_2(mainScene::onKeyReleased2, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void mainScene::onKeyPressed2(EventKeyboard::KeyCode code, Event * evt)
{
//	char txt[100] = {};
//	sprintf_s(txt, "%d is Pressed", (int)code);
//	label->setString(txt);

	if ((int)code == 164|| (int)code == 35)//enter
	{
		Director::getInstance()->replaceScene(TransitionSlideInR::create(1.0f, gameScene::createScene()));
	}

}

void mainScene::onKeyReleased2(EventKeyboard::KeyCode code, Event * evt)
{
}

