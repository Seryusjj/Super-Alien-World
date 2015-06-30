#pragma once

#include "Enemy.h"
namespace Actors{
	class EnemyFrog : public Enemy
	{
	protected:
		virtual void setEnemyType() override;
	public:
		virtual bool init() override;
		CREATE_FUNC(EnemyFrog);
	};
}

