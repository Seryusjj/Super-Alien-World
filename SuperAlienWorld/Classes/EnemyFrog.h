#pragma once

#include "Enemy.h"

class EnemyFrog : public Enemy
{
protected:
	virtual void setEnemyType() override;
public:
	virtual bool init() override;
	CREATE_FUNC(EnemyFrog);
};

