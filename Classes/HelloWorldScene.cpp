#include "HelloWorldScene.h"
#include "VisibleRect.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Director::getInstance()->end();
	if (Sprite3DReskinTest::isEixt())
		return;
	else
	{
		auto sprite3d = new Sprite3DReskinTest();
		this->addChild(sprite3d, 10);
	}


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

cocos2d::Sprite3D* Sprite3DReskinTest::_sprite = nullptr;

Sprite3DReskinTest::Sprite3DReskinTest()	
{
	auto s = Director::getInstance()->getWinSize();
	addNewSpriteWithCoords(Vec2(s.width / 2, s.height / 2));

	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesEnded = CC_CALLBACK_2(Sprite3DReskinTest::onTouchesEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	TTFConfig ttfConfig("fonts/arial.ttf", 20);
	auto label1 = Label::createWithTTF(ttfConfig, "Hair");
	auto item1 = MenuItemLabel::create(label1, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
	auto label2 = Label::createWithTTF(ttfConfig, "Glasses");
	auto item2 = MenuItemLabel::create(label2, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
	auto label3 = Label::createWithTTF(ttfConfig, "Coat");
	auto item3 = MenuItemLabel::create(label3, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
	auto label4 = Label::createWithTTF(ttfConfig, "Pants");
	auto item4 = MenuItemLabel::create(label4, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
	auto label5 = Label::createWithTTF(ttfConfig, "Shoes");
	auto item5 = MenuItemLabel::create(label5, CC_CALLBACK_1(Sprite3DReskinTest::menuCallback_reSkin, this));
	item1->setPosition(Vec2(VisibleRect::left().x + 50, VisibleRect::bottom().y + item1->getContentSize().height * 4));
	item2->setPosition(Vec2(VisibleRect::left().x + 50, VisibleRect::bottom().y + item1->getContentSize().height * 5));
	item3->setPosition(Vec2(VisibleRect::left().x + 50, VisibleRect::bottom().y + item1->getContentSize().height * 6));
	item4->setPosition(Vec2(VisibleRect::left().x + 50, VisibleRect::bottom().y + item1->getContentSize().height * 7));
	item5->setPosition(Vec2(VisibleRect::left().x + 50, VisibleRect::bottom().y + item1->getContentSize().height * 8));
	item1->setUserData((void*)SkinType::HAIR);
	item2->setUserData((void*)SkinType::GLASSES);
	item3->setUserData((void*)SkinType::UPPER_BODY);
	item4->setUserData((void*)SkinType::PANTS);
	item5->setUserData((void*)SkinType::SHOES);
	auto pMenu1 = CCMenu::create(item1, item2, item3, item4, item5, nullptr);
	pMenu1->setPosition(Vec2(0, 0));
	this->addChild(pMenu1, 10);

}
void Sprite3DReskinTest::menuCallback_reSkin(Ref* sender)
{
	long index = (long)(((MenuItemLabel*)sender)->getUserData());
	if (index < (int)SkinType::MAX_TYPE)
	{
		_curSkin[index] = (_curSkin[index] + 1) % _skins[index].size();
		applyCurSkin();

	}
}

void Sprite3DReskinTest::addNewSpriteWithCoords(Vec2 p)
{
	std::string fileName = "ReskinGirl.c3b";
	auto sprite = Sprite3D::create(fileName);
	sprite->setScale(4);
	sprite->setRotation3D(Vec3(0, 0, 0));
	addChild(sprite);
	sprite->setPosition(Vec2(p.x, p.y - 60));
	auto animation = Animation3D::create(fileName);
	if (animation)
	{
		auto animate = Animate3D::create(animation);

		sprite->runAction(RepeatForever::create(animate));
	}
	_sprite = sprite;

	auto& body = _skins[(int)SkinType::UPPER_BODY];
	body.push_back("Girl_UpperBody01");
	body.push_back("Girl_UpperBody02");

	auto& pants = _skins[(int)SkinType::PANTS];
	pants.push_back("Girl_LowerBody01");
	pants.push_back("Girl_LowerBody02");

	auto& shoes = _skins[(int)SkinType::SHOES];
	shoes.push_back("Girl_Shoes01");
	shoes.push_back("Girl_Shoes02");

	auto& hair = _skins[(int)SkinType::HAIR];
	hair.push_back("Girl_Hair01");
	hair.push_back("Girl_Hair02");

	auto& face = _skins[(int)SkinType::FACE];
	face.push_back("Girl_Face01");
	face.push_back("Girl_Face02");

	auto& hand = _skins[(int)SkinType::HAND];
	hand.push_back("Girl_Hand01");
	hand.push_back("Girl_Hand02");

	auto& glasses = _skins[(int)SkinType::GLASSES];
	glasses.push_back("");
	glasses.push_back("Girl_Glasses01");

	memset(_curSkin, 0, (int)SkinType::MAX_TYPE * sizeof(int));

	applyCurSkin();
}

void Sprite3DReskinTest::onTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
}

void Sprite3DReskinTest::applyCurSkin()
{
	for (ssize_t i = 0; i < _sprite->getMeshCount(); i++) {
		auto mesh = _sprite->getMeshByIndex(static_cast<int>(i));
		bool isVisible = false;
		for (int j = 0; j < (int)SkinType::MAX_TYPE; j++) {
			if (mesh->getName() == _skins[j].at(_curSkin[j]))
			{
				isVisible = true;
				break;
			}
		}
		_sprite->getMeshByIndex(static_cast<int>(i))->setVisible(isVisible);
	}
}