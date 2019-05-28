#include"SingleGameScene.h"
USING_NS_CC;
Scene* SingleGame::createScene()
{
	return SingleGame::create();
}
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SingleGame::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto exitItem = MenuItemImage::create(
		"menu/singlegame/ExitNormal.png",
		"menu/singlegame/ExitSelected.png",
		CC_CALLBACK_1(SingleGame::menuItemExitCallback, this)
	);
	if (exitItem == nullptr ||
		exitItem->getContentSize().width <= 0 ||
		exitItem->getContentSize().height <= 0)
	{
		problemLoading("'menu/singlegame/ExitNormal.png' and 'menu/singlegame/ExitSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width-exitItem->getContentSize().width/2;
		float y = origin.y + exitItem->getContentSize().height/2;
		exitItem->setPosition(Vec2(x, y));
	}
	auto menu = Menu::create(exitItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	auto background = Sprite::create("background/map.png");
	if (background == nullptr)
	{
		problemLoading("'background/map.png'");
	}
	else
	{

		background->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2));

		this->addChild(background, 0);
	}
	Player=Sprite::create("character/orange.png");
	Player->setPosition(Vec2(origin.x + visibleSize.width*4/9, origin.y + Player->getContentSize().height / 2));
	addChild(Player, 2, 200);
	/*auto listener = EventListenerMouse::create();
	listener->onMouseMove = [](Event*event){
		EventMouse*e = (EventMouse*)event;
	    log("onMouseMove");
	};
	listener->onMouseDown = [=](Event*event) {
		EventMouse*e = (EventMouse*)event;
		auto sprite = this->getChildByTag(200);
		sprite->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
		log("onMouseDown");
	};
	EventDispatcher*eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getChildByTag(200));*/
	return true;
}
void SingleGame::menuItemExitCallback(Ref*pSender) {
	Director::getInstance()->popScene();
}
/*void SingleGame::onEnter() {
	log("SingleGameScene onEnter");
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SingleGame::touchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SingleGame::touchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SingleGame::touchEnded, this);
	EventDispatcher*eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, getChildByTag(200));
}*/
void SingleGame::onEnter() {
	Scene::onEnter();
	log("SingleGameScene onEnter");
	auto listener1 = EventListenerMouse::create();
	auto listener2 = EventListenerKeyboard::create();
	/*listener->onMouseMove = [](Event*event) {
		EventMouse*e = (EventMouse*)event;
		log("onMouseMove");
	};*/
	listener1->onMouseDown = [=](Event*event) {
		EventMouse*e = (EventMouse*)event;
		auto sprite = this->getChildByTag(200);
		double rx = e->getCursorX() - sprite->getPosition().x;
		double ry = e->getCursorY() - sprite->getPosition().y;
		//Vec2 spritePosition = sprite->getPosition();
		//Vec2 relativePostion = e->getDelta() - sprite->getPosition();
		if (abs(rx) > abs(ry)) {
			sprite->runAction(MoveBy::create(1, Vec2(40*rx /abs(rx), 0)));
			if (rx > 0) {
				sprite->runAction(RotateTo::create(0.1,90 ));
			}
			else if(rx < 0) {
				sprite->runAction(RotateTo::create(0.1, -90));
			}
		}
		if (abs(rx) < abs(ry)) {
			sprite->runAction(MoveBy::create(1, Vec2(0, 40*ry/abs(ry))));
			if (ry > 0) {
				sprite->runAction(RotateTo::create(0.1, 0));
			}
			else if (ry < 0) {
				sprite->runAction(RotateTo::create(0.1, 180));
			}
			
		}
    };
	listener2->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*event) {
		auto sprite= this->getChildByTag(200);
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			sprite->runAction(MoveBy::create(1,Vec2(40,0)));
			sprite->runAction(RotateTo::create(0.1, 90));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			sprite->runAction(MoveBy::create(1, Vec2(-40, 0)));
			sprite->runAction(RotateTo::create(0.1, -90));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			sprite->runAction(MoveBy::create(1, Vec2(0, 40)));
			sprite->runAction(RotateTo::create(0.1, 0));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			sprite->runAction(MoveBy::create(1, Vec2(0, -40)));
			sprite->runAction(RotateTo::create(0.1, 180));
		}
	};
	EventDispatcher*eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, getChildByTag(200));
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, getChildByTag(200));
}
/*bool SingleGame::touchBegan(Touch*touch, Event*event) {
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		target->runAction(ScaleBy::create(0.06f, 1.06f));
		return true;
	}
	return false;
}
void SingleGame::touchMoved(Touch*touch, Event*event) {
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	target->setPosition(target->getPosition() + touch->getDelta());

}
void SingleGame::touchEnded(Touch*touch, Event*event) {
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		target->runAction(ScaleTo::create(0.06f, 1.06f));
		
	}
}*/
/*void SingleGame::onExit() {
	Scene::onExit();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}*/
void SingleGame::onExit() {
	
	Scene::onExit();
	log("SingleGameScene onExit");
	//Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	auto target = this->getChildByTag(200);
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(target);
}
/*void SingleGame::MouseMove(Event*event) {
	EventMouse*e = (EventMouse*)event;
	log("onMouseMove");
}
void SingleGame::MouseDown(Event*event) {
	EventMouse*e = (EventMouse*)event;
	Player->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
	log("onMouseDown");
}*/