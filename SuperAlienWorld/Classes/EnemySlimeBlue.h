#pragma once


#include "Enemy.h"

class EnemySlimeBlue : public Enemy
{
protected:
	virtual void setEnemyType() override;
public:
	virtual bool init() override;
	CREATE_FUNC(EnemySlimeBlue);
};
