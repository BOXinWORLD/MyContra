#ifndef __Hero_H__
#define __Hero_H__
#include "cocos2d.h"
USING_NS_CC;

class Hero :public Sprite {
public:
	CREATE_FUNC(Hero);
	bool init();

	void update(float dt);

	void idle();//��ֹ
	void down();//ſ��
	void jump();//jump
	void runAnimation();//���ܶ���
	void runLeft(float dt);
	void runRight(float dt);

	bool isLeft;//�Ƿ�����
	bool isDown;
	bool isJump;
	bool keepLeft;
	bool keepRight;

	float vy;//�����ٶ�
	float g;//�������ٶ�
	float oy;//����y����

	Sprite* sp;
	Action* run;
	Action* jumpAction;

	//���̼���
	void listenKeyboardEvent();
	void onKeyPressed2(EventKeyboard::KeyCode code, Event* evt);
	void onKeyReleased2(EventKeyboard::KeyCode code, Event* evt);
};

#endif // __Hero_H__


