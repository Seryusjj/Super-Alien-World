#include "BackGround3Parts.h"


using namespace cocos2d;
using namespace Menus;


BackGround3Parts::BackGround3Parts() :_speed(150), _initialiced(false){
	_screen = Director::getInstance()->getVisibleSize();
	//azul
	_bgPart1 = Sprite::createWithSpriteFrameName("fondoparte2");
	_bgPart1->retain();

	//nube
	_bgPart2 = Sprite::createWithSpriteFrameName("fondoparte1");
	_bgPart2->retain();

	//azul
	_bgPart3 = Sprite::createWithSpriteFrameName("fondoparte2");
	_bgPart3->retain();

	//nubes
	_bgPart4 = Sprite::createWithSpriteFrameName("fondoparte3");
	_bgPart4->retain();

	//azul
	_bgPart5 = Sprite::createWithSpriteFrameName("fondoparte2");
	_bgPart5->retain();

	_bgPart1->setPosition(_screen.width*0.5, _screen.height*0.5);
	_bgPart2->setPosition(_screen.width*0.5 - _screen.width + 1, _screen.height*0.5);
	_bgPart3->setPosition(_screen.width*0.5 - (_screen.width - 1) * 2, _screen.height*0.5);
	_bgPart4->setPosition(_screen.width*0.5 - (_screen.width - 1) * 3, _screen.height*0.5);
	_bgPart5->setPosition(_screen.width*0.5 - (_screen.width - 1) * 4, _screen.height*0.5);
}

void BackGround3Parts::setParent(Node* parent){
	if (!_initialiced){
		parent->addChild(_bgPart1);
		parent->addChild(_bgPart2);
		parent->addChild(_bgPart3);
		parent->addChild(_bgPart4);
		parent->addChild(_bgPart5);
		_initialiced = true;
	}

}



void BackGround3Parts::update(float dt){
	//move right
	_bgPart1->setPositionX(_bgPart1->getPositionX() + _speed*dt);
	_bgPart2->setPositionX(_bgPart2->getPositionX() + _speed*dt);
	_bgPart3->setPositionX(_bgPart3->getPositionX() + _speed*dt);
	_bgPart4->setPositionX(_bgPart4->getPositionX() + _speed*dt);
	_bgPart5->setPositionX(_bgPart5->getPositionX() + _speed*dt);

	if (_bgPart1->getPositionX() >= (_screen.width-1)*4 + _screen.width*0.5){
		_bgPart1->setPosition(_screen.width*0.5, _screen.height*0.5);
		_bgPart2->setPosition(_screen.width*0.5 - _screen.width + 1, _screen.height*0.5);
		_bgPart3->setPosition(_screen.width*0.5 - (_screen.width - 1) * 2, _screen.height*0.5);
		_bgPart4->setPosition(_screen.width*0.5 - (_screen.width - 1) * 3, _screen.height*0.5);
		_bgPart5->setPosition(_screen.width*0.5 - (_screen.width - 1) * 4, _screen.height*0.5);
	}
}

BackGround3Parts::~BackGround3Parts()
{
	_bgPart1->release();
	_bgPart2->release();
}
