#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};


class Sprite3DReskinTest : public cocos2d::Layer
{
public:
	CREATE_FUNC(Sprite3DReskinTest);
	Sprite3DReskinTest();

	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
	void addNewSpriteWithCoords(cocos2d::Vec2 p);

	void menuCallback_reSkin(cocos2d::Ref* sender);
	static bool isEixt(){ if (_sprite != nullptr) return true; return false; }
protected:
	void applyCurSkin();

	enum class SkinType
	{
		UPPER_BODY = 0,
		PANTS,
		SHOES,
		HAIR,
		FACE,
		HAND,
		GLASSES,
		MAX_TYPE,
	};

	std::vector<std::string> _skins[(int)SkinType::MAX_TYPE]; //all skins
	int                      _curSkin[(int)SkinType::MAX_TYPE]; //current skin index
	static cocos2d::Sprite3D* _sprite;
};

#endif // __HELLOWORLD_SCENE_H__
