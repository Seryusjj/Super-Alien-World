#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#define GROUND_TAG 0
class Player;
class HelloWorld : public cocos2d::Layer
{
private:
	cocos2d::TMXTiledMap *map;
	Player * _player;

	cocos2d::Follow* _camera;
	cocos2d::Node* _cameraTarget;
public:

    static cocos2d::Scene* createScene();


    virtual bool init();
   
	void update(float dt);

    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
