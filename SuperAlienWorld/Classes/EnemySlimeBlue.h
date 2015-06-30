#pragma once


#include "Enemy.h"
namespace Actors{
	class EnemySlimeBlue : public Enemy
	{
	protected:
		virtual void setEnemyType() override;
	public:
		virtual bool init() override;
		CREATE_FUNC(EnemySlimeBlue);
	};
}

