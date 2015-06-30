#pragma once
#include "cocos2d.h"
#include "Enemy.h"
namespace Levels{

	class EnemyFactory
	{
	private:
		enum EnemyType  {
			LADYBUG = 257,
			SLIME_BLUE = 258,
			SLIME_PURPLE = 259,
			WORM_GREEN = 260,
			FROG = 262,
			MOUSE = 263,
			SLIME_GREEN = 264,
			SNAIL = 265,
			WORM_PINK = 266
		};

		static EnemyFactory* _instance;
		DISALLOW_COPY_AND_ASSIGN(EnemyFactory);
		EnemyFactory();
	public:
		static EnemyFactory* getInstance();
		Actors::Enemy* getEnemy(int tileGID);


	};
}

