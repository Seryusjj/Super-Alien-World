#pragma once

#include "Enemy.h"

class EnemySnail : public Enemy
{
protected:
	virtual void setEnemyType() override;
public:
	virtual bool init() override;
	CREATE_FUNC(EnemySnail);
};
