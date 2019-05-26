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
	return true;
}
void SingleGame::menuItemExitCallback(Ref*pSender) {
	Director::getInstance()->popScene();
}
