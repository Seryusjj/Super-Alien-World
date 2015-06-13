
#ifndef __SELECTMENULAYER_H__
#define __SELECTMENULAYER_H__

#define NUM_LEVELS 3

#include "MainMenuLayer.h"
#include "ui/CocosGUI.h"


class SelectMenuLayer : public MainMenuLayer
{
private:	
	std::ostringstream _ostr;
	void actionButtonBack();
	void initButtons(cocos2d::Vector<cocos2d::ui::Button*>& vector, std::vector<std::function<void(Ref*)>>& functions);

public:
	virtual bool init();
	static cocos2d::Scene* createScene();
	CREATE_FUNC(SelectMenuLayer);
};

#endif //__MAINMENULAYER_H__