#include"SingleGameScene.h"
#include"SelectRoleScene.h"
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
	tileMap = TMXTiledMap::create("tileMap.tmx");
	scale = visibleSize.height / tileMap->getContentSize().height;
	tileMap->setScale(scale);
	tileMap->setAnchorPoint(Vec2::ZERO);
	tileMap->setPosition(Vec2::ZERO);
	this->addChild(tileMap, -1);
	log("MapWidth:%f ;MapHeight:%f ;TileWidth:%f ;TileHeight:%f ;", 
		tileMap->getMapSize().width, tileMap->getMapSize().height, tileMap->getTileSize().width, tileMap->getTileSize().height);
	auto players = tileMap->getObjectGroup("players");
	ValueMap p = players->getObject("player1");
	ValueMap o1 = players->getObject("player2");
	ValueMap o2 = players->getObject("player3");
	ValueMap o3 = players->getObject("player4");
	
	float x = p["x"].asFloat();
	float y = p["y"].asFloat();
	
	if (name == "orange.png")
	{
		Player = Sprite::create("character/orange.png");
		PlayerShow = Sprite::create("character/orange.png");
		PlayerShow->setScale(0.5f);
		Fruits[0].used = true;
		Fruits[0].index = 0;
		for (int i = 0; i < 5; i++) {
			Pop[i].newCharacter = Orange[i];
		}
		Pop[5].weaponShoot = "weapon/orangearrow.png";
	}
	else if (name == "litchi.png")
	{
		Player = Sprite::create("character/litchi.png");
		PlayerShow = Sprite::create("character/litchi.png");
		PlayerShow->setScale(0.5f);
		Fruits[1].used = true;
		Fruits[1].index = 0;
		for (int i = 0; i < 5; i++) {
			Pop[i].newCharacter = Litchi[i];
		}
		Pop[5].weaponShoot = "weapon/litchiarrow.png";
	}
	else if (name == "avocado.png")
	{
		Player = Sprite::create("character/avocado.png");
		PlayerShow = Sprite::create("character/avocado.png");
		PlayerShow->setScale(0.5f);
		Fruits[2].used = true;
		Fruits[2].index = 0;
		for (int i = 0; i < 5; i++) {
			Pop[i].newCharacter = Avocado[i];
		}
		Pop[5].weaponShoot = "weapon/avocadoarrow.png";
	}
	else if (name == "pineapple.png")
	{
		Player = Sprite::create("character/pineapple.png");
		PlayerShow = Sprite::create("character/pineapple.png");
		PlayerShow->setScale(0.5f);
		Fruits[3].used =true;
		Fruits[3].index = 0;
		for (int i = 0; i < 5; i++) {
			Pop[i].newCharacter = Pineapple[i];
		}
		Pop[5].weaponShoot = "weapon/pineapplearrow.png";
	}
	else if (name == "mulberry.png")
	{
		Player = Sprite::create("character/mulberry.png");
		PlayerShow = Sprite::create("character/mulberry.png");
		PlayerShow->setScale(0.5f);
		Fruits[4].used = true;
		Fruits[4].index = 0;
		for (int i = 0; i < 5; i++) {
			Pop[i].newCharacter = Mulberry[i];
		}
		Pop[5].weaponShoot = "weapon/mulberryarrow.png";
	}
	Player->setPosition(Vec2(x*scale, y*scale));
	addChild(Player, 2);
	int value;
	x = o1["x"].asFloat();
	y = o1["y"].asFloat();
	while(1){
		value = random() % 5;
		if (Fruits[value].used == false) {
			Opponent1 = Sprite::create(Fruits[value].fru);
			OppShow1 = Sprite::create(Fruits[value].fru);
			OppShow1->setScale(0.5f);
			Fruits[value].used = true;
			Fruits[value].index = 1;
			Opponent1->setPosition(Vec2(x*scale, y*scale));
			addChild(Opponent1, 1,1);
			break;
		}
	}
	x = o2["x"].asFloat();
	y = o2["y"].asFloat();
	while(1) {
		value = random() % 5;
		if (Fruits[value].used == false) {
			Opponent2 = Sprite::create(Fruits[value].fru);
			OppShow2 = Sprite::create(Fruits[value].fru);
			OppShow2->setScale(0.5f);
			Fruits[value].used = true;
			Fruits[value].index = 2;
			Opponent2->setPosition(Vec2(x*scale, y*scale));
			addChild(Opponent2, 1,2);
			break;
		}
	}
	x = o3["x"].asFloat();
	y = o3["y"].asFloat();
	while(1) {
		value = random() % 5;
		if (Fruits[value].used == false) {
			Opponent3 = Sprite::create(Fruits[value].fru);
			OppShow3 = Sprite::create(Fruits[value].fru);
			OppShow3->setScale(0.5f);
			Fruits[value].used = true;
			Fruits[value].index = 3;
			Opponent3->setPosition(Vec2(x*scale, y*scale));
			addChild(Opponent3, 1,3);
			break;
		}
	}

	collision = tileMap->getLayer("collision");
	collision->setVisible(false);



	auto blood_bg = Sprite::create("bar/blood_bg.png");
	blood_bg->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2, 
		                       origin.y + visibleSize.height * 79 / 80 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_bg, 3);
	auto blood_bar = Sprite::create("bar/blood_bar.png");
	PlayerProgress = ProgressTimer::create(blood_bar);
	PlayerProgress->setType(ProgressTimer::Type::BAR);
	PlayerProgress->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2,
		                             origin.y + visibleSize.height * 79 / 80 - blood_bg->getContentSize().height / 2));
	PlayerProgress->setMidpoint(Vec2(0, 0.5));
	PlayerProgress->setBarChangeRate(Vec2(1, 0));
	PlayerProgress->setPercentage(100);
	this->addChild(PlayerProgress, 3);
	auto blood_front = Sprite::create("bar/blood_front.png");
	blood_front->setPosition(Vec2(origin.x + visibleSize.width / 30+ blood_bg->getContentSize().width / 2,
		                          origin.y + visibleSize.height * 79 /80 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_front, 3);
	PlayerShow->setPosition(Vec2(origin.x  + PlayerShow->getContentSize().width / 3,
		                         origin.y + visibleSize.height-PlayerShow->getContentSize().height/4));
	this->addChild(PlayerShow, 3);


	auto blood_bg1 = Sprite::create("bar/blood_bg.png");
	blood_bg1->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2,
		                        origin.y + visibleSize.height *19 / 20 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_bg1, 3);
	auto blood_bar1 = Sprite::create("bar/blood_bar.png");
	OppProgress1 = ProgressTimer::create(blood_bar1);
	OppProgress1->setType(ProgressTimer::Type::BAR);
	OppProgress1->setPosition(Vec2(origin.x + visibleSize.width / 30+ blood_bg->getContentSize().width / 2,
		                           origin.y + visibleSize.height * 19 / 20 - blood_bg->getContentSize().height / 2));
	OppProgress1->setMidpoint(Vec2(0, 0.5));
	OppProgress1->setBarChangeRate(Vec2(1, 0));
	OppProgress1->setPercentage(100);
	this->addChild(OppProgress1, 3,10);
	auto blood_front1 = Sprite::create("bar/blood_front.png");
	blood_front1->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2,
		                           origin.y + visibleSize.height *19 / 20 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_front1, 3);
	OppShow1->setPosition(Vec2(origin.x +  PlayerShow->getContentSize().width / 3,
		                       origin.y + visibleSize.height - PlayerShow->getContentSize().height*3 / 4));
	this->addChild(OppShow1, 3);


	auto blood_bg2 = Sprite::create("bar/blood_bg.png");
	blood_bg2->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2,
		                        origin.y + visibleSize.height * 73 / 80 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_bg2, 3);
	auto blood_bar2 = Sprite::create("bar/blood_bar.png");
	OppProgress2 = ProgressTimer::create(blood_bar2);
	OppProgress2->setType(ProgressTimer::Type::BAR);
	OppProgress2->setPosition(Vec2(origin.x + visibleSize.width /30 + blood_bg->getContentSize().width / 2,
		                           origin.y + visibleSize.height * 73 / 80 - blood_bg->getContentSize().height / 2));
	OppProgress2->setMidpoint(Vec2(0, 0.5));
	OppProgress2->setBarChangeRate(Vec2(1, 0));
	OppProgress2->setPercentage(100);
	this->addChild(OppProgress2, 3,20);
	auto blood_front2 = Sprite::create("bar/blood_front.png");
	blood_front2->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2,
		                           origin.y + visibleSize.height * 73 / 80 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_front2, 3);
	OppShow2->setPosition(Vec2(origin.x +  PlayerShow->getContentSize().width / 3,
		                       origin.y + visibleSize.height - PlayerShow->getContentSize().height * 5 / 4));
	this->addChild(OppShow2, 3);


	auto blood_bg3 = Sprite::create("bar/blood_bg.png");
	blood_bg3->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2,
		                        origin.y + visibleSize.height * 7 / 8 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_bg3, 3);
	auto blood_bar3 = Sprite::create("bar/blood_bar.png");
	OppProgress3 = ProgressTimer::create(blood_bar3);
	OppProgress3->setType(ProgressTimer::Type::BAR);
	OppProgress3->setPosition(Vec2(origin.x + visibleSize.width /30 + blood_bg->getContentSize().width / 2,
		                           origin.y + visibleSize.height * 7 / 8 - blood_bg->getContentSize().height / 2));
	OppProgress3->setMidpoint(Vec2(0, 0.5));
	OppProgress3->setBarChangeRate(Vec2(1, 0));
	OppProgress3->setPercentage(100);
	this->addChild(OppProgress3, 3,30);
	auto blood_front3 = Sprite::create("bar/blood_front.png");
	blood_front3->setPosition(Vec2(origin.x + visibleSize.width / 30 + blood_bg->getContentSize().width / 2,
		origin.y + visibleSize.height * 7 / 8 - blood_bg->getContentSize().height / 2));
	this->addChild(blood_front3, 3);
	OppShow3->setPosition(Vec2(origin.x +PlayerShow->getContentSize().width / 3,
		origin.y + visibleSize.height - PlayerShow->getContentSize().height * 7 / 4));
	this->addChild(OppShow3, 3);

	auto countdown_bg = Sprite::create("bar/count_down_bg.png");
	countdown_bg->setPosition(Vec2(origin.x + visibleSize.width * 79 / 80 - countdown_bg->getContentSize().width / 2,
		                           origin.y + visibleSize.height * 159 / 160 - countdown_bg->getContentSize().height / 2));
	this->addChild(countdown_bg, 3);
	auto countdown_bar = Sprite::create("bar/count_down_bar.png");
	CountDownProgress = ProgressTimer::create(countdown_bar);
	CountDownProgress->setType(ProgressTimer::Type::BAR);
	CountDownProgress->setPosition(Vec2(origin.x + visibleSize.width * 79 / 80 - countdown_bar->getContentSize().width / 2,
		                                origin.y + visibleSize.height * 159 / 160 - countdown_bar->getContentSize().height / 2));
	CountDownProgress->setMidpoint(Vec2(0, 0.5));
	CountDownProgress->setBarChangeRate(Vec2(1, 0));
	CountDownProgress->setPercentage(100);
	this->addChild(CountDownProgress, 3);

	Timettf = LabelTTF::create("180 s", "HiraKakuProN-W6", 22);
	Timettf->setPosition(Vec2(origin.x + visibleSize.width * 79 / 80 - countdown_bg->getContentSize().width/2,
		                      origin.y+visibleSize.height*159/160-Timettf->getContentSize().height));
	Timettf->setColor(Color3B(0, 0, 0));
	
	this->addChild(Timettf, 3);


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
	
	auto UpItem = MenuItemImage::create(
		"menu/singlegame/UpNormal.png",
		"menu/singlegame/UpSelected.png",
		CC_CALLBACK_1(SingleGame::menuItemUp, this)
	);
	UpItem->setAnchorPoint(Vec2(0, 0));
	UpItem->setPosition(Vec2(UpItem->getContentSize().width,2*UpItem->getContentSize().height));
	auto DownItem = MenuItemImage::create(
		"menu/singlegame/DownNormal.png",
		"menu/singlegame/DownSelected.png",
		CC_CALLBACK_1(SingleGame::menuItemDown, this)
	);
	DownItem->setAnchorPoint(Vec2(0, 0));
	DownItem->setPosition(Vec2(DownItem->getContentSize().width,0));
	auto LeftItem = MenuItemImage::create(
		"menu/singlegame/LeftNormal.png",
		"menu/singlegame/LeftSelected.png",
		CC_CALLBACK_1(SingleGame::menuItemLeft, this)
	);
	LeftItem->setAnchorPoint(Vec2(0, 0));
	LeftItem->setPosition(Vec2(0,LeftItem->getContentSize().height));
	
	auto RightItem = MenuItemImage::create(
		"menu/singlegame/RightNormal.png",
		"menu/singlegame/RightSelected.png",
		CC_CALLBACK_1(SingleGame::menuItemRight, this)
	);
	RightItem->setAnchorPoint(Vec2(0, 0));
	RightItem->setPosition(Vec2(2*RightItem->getContentSize().width,RightItem->getContentSize().height));
	auto menu = Menu::create(exitItem,UpItem,DownItem,LeftItem,RightItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	
	
	scheduleUpdate();
	
	schedule(schedule_selector(SingleGame::myupdate),0.1f);
	
	return true;
}

void SingleGame::onEnter() {
	Scene::onEnter();
	
	
	auto listener1 = EventListenerMouse::create();
	auto listener2 = EventListenerKeyboard::create();
	
	
	listener1->onMouseDown = [=](Event*event) {
		
		EventMouse*e = (EventMouse*)event;
		
		float rx = e->getCursorX() - Player->getPosition().x;
		float ry = e->getCursorY() - Player->getPosition().y;
		Size s = Player->getContentSize();
		
		if (abs(rx)<s.width/2&&abs(ry)<s.width/2) {
			
			attack = true;
		}
		else { 
			attack = false;
			
		}
		
	};
	listener1->onMouseUp = [=](Event*event) {
		
		EventMouse*e = (EventMouse*)event;
		Sprite*weapon;
		
		if (attack==true) {
			
			
			weapon = Sprite::create(Pop[weaponIndex].weaponShoot);
			Vec2 position = Player->getPosition();
			weapon->setPosition(position);
			this->addChild(weapon,1 );
			float speed = tileMap->getTileSize().width*4;
			float rx = e->getCursorX() - position.x;
			float ry = e->getCursorY() - position.y;
			weapon->setRotation(90 - atan2(ry, rx)*57.29578);
			Player->setRotation(90 - atan2(ry, rx)*57.29578);
		    Weapon.pushBack(weapon);
			Vec2 weaponTerminal = weaponPosition(position, rx, ry);
			rx = position.x - weaponTerminal.x;
			ry = position.y - weaponTerminal.y;
			float time= sqrt(rx*rx + ry * ry)/speed;
			auto callfunc = CallFunc::create([=] {
				this->removeChild(Weapon.at(0));
			    Weapon.erase(0);
				
			});
			    
			weapon->runAction(Sequence::create(MoveTo::create(time, weaponTerminal), FadeOut::create(0.1f),callfunc, NULL));
				
		}
		
	};
	listener2->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*event) {
		
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			direction = "right";
			float x = Player->getPosition().x + tileMap->getTileSize().width;
			float y = Player->getPosition().y;
			
			Player->runAction(RotateTo::create(0.1f, 90));
			this->setPlayerPosition(Vec2(x, y));
			
			
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			direction = "left";
			float x = Player->getPosition().x - tileMap->getTileSize().width;
			float y = Player->getPosition().y;
			
			Player->runAction(RotateTo::create(0.1f, -90));
			this->setPlayerPosition(Vec2(x, y));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			direction = "up";
			float x = Player->getPosition().x;
			float y = Player->getPosition().y + tileMap->getTileSize().width;
			
			Player->runAction(RotateTo::create(0.1f, 0));
			this->setPlayerPosition(Vec2(x, y));
			
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			direction = "down";
			float x = Player->getPosition().x;
			float y = Player->getPosition().y - tileMap->getTileSize().width;
			
			Player->runAction(RotateTo::create(0.1f, 180));
			this->setPlayerPosition(Vec2(x, y));
		}
		Sprite*weapon;
		weapon = Sprite::create(Pop[weaponIndex].weaponShoot);
	    if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			
			weapon->setPosition(Vec2(Player->getPosition()));
			weapon->setRotation(180);
			this->addChild(weapon, 1);
			Player->setRotation(180);
			Weapon.pushBack(weapon);
			Vec2 position = Player->getPosition();
			float speed = tileMap->getTileSize().width * 4;
			float rx = 0;
			float ry = -tileMap->getTileSize().width*8;
			Vec2 weaponTerminal = weaponPosition(position, rx, ry);
			rx = position.x - weaponTerminal.x;
			ry = position.y - weaponTerminal.y;
			float time = sqrt(rx*rx + ry * ry) / speed;
			auto callfunc = CallFunc::create([=] {
				this->removeChild(Weapon.at(0));
				Weapon.erase(0);
			});
			weapon->runAction(Sequence::create(MoveTo::create(time, weaponTerminal), FadeOut::create(0.1f),callfunc, NULL));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			
			weapon->setPosition(Vec2(Player->getPosition()));
			weapon->setRotation(0);
			this->addChild(weapon, 1);
			Player->setRotation(0);
			Weapon.pushBack(weapon);
			Vec2 position = Player->getPosition();
			float speed = tileMap->getTileSize().width * 4;
			float rx = 0;
			float ry = tileMap->getTileSize().width * 8;
			Vec2 weaponTerminal = weaponPosition(position, rx, ry);
			rx = position.x - weaponTerminal.x;
			ry = position.y - weaponTerminal.y;
			float time = sqrt(rx*rx + ry * ry) / speed;
			auto callfunc = CallFunc::create([=] {
				this->removeChild(Weapon.at(0));
				Weapon.erase(0);
			});
			weapon->runAction(Sequence::create(MoveTo::create(time, weaponTerminal), FadeOut::create(0.1f), callfunc,NULL));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			
			weapon->setPosition(Vec2(Player->getPosition()));
			weapon->setRotation(-90);
			this->addChild(weapon, 1);
			Player->setRotation(-90);
			Weapon.pushBack(weapon);
			Vec2 position = Player->getPosition();
			float speed = tileMap->getTileSize().width * 4;
			float rx = -tileMap->getTileSize().width * 8;
			float ry =0;
			Vec2 weaponTerminal = weaponPosition(position, rx, ry);
			rx = position.x - weaponTerminal.x;
			ry = position.y - weaponTerminal.y;
			float time = sqrt(rx*rx + ry * ry) / speed;
			auto callfunc = CallFunc::create([=] {
				this->removeChild(Weapon.at(0));
				Weapon.erase(0);
			});
			weapon->runAction(Sequence::create(MoveTo::create(time, weaponTerminal), FadeOut::create(0.1f),callfunc, NULL));
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			
			weapon->setPosition(Vec2(Player->getPosition()));
			weapon->setRotation(90);
			this->addChild(weapon, 1);
			Player->setRotation(90);
			Weapon.pushBack(weapon);
			Vec2 position = Player->getPosition();
			float speed = tileMap->getTileSize().width * 4;
			float rx = tileMap->getTileSize().width * 8;
			float ry = 0;
			Vec2 weaponTerminal = weaponPosition(position, rx, ry);
			rx = position.x - weaponTerminal.x;
			ry = position.y - weaponTerminal.y;
			float time = sqrt(rx*rx + ry * ry) / speed;
			auto callfunc = CallFunc::create([=] {
				this->removeChild(Weapon.at(0));
				Weapon.erase(0);
		    });
			weapon->runAction(Sequence::create(MoveTo::create(time, weaponTerminal), FadeOut::create(0.1f),callfunc, NULL));
		}
		
	};
	
	EventDispatcher*eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, Player);
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, Player);
	
}

void SingleGame::onExit() {
	Scene::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(Player);
	this->removeAllChildren();
}



void SingleGame::setPlayerPosition(Vec2 position) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (position.x <= 0 || position.y <=0 || position.x >= visibleSize.width || position.y >= visibleSize.height) {
		return;
	}
	Vec2 tileCoord = this->tileCoordFromPosition(position);
	int tileGid = collision->getTileGIDAt(tileCoord);
	
	if (tileGid > 0) {
		
		return;
	}
	else{  
		
		if(direction=="up"){ 
		   Player->stopAllActions();
		   Player->runAction(RotateTo::create(0.1f, 0));
	       Player->runAction(MoveBy::create(0.3f, Vec2(0, tileMap->getTileSize().width)));
		}
		else if(direction=="down"){  
		   Player->stopAllActions();
		   Player->runAction(RotateTo::create(0.1f, 180));
	       Player->runAction(MoveBy::create(0.3f, Vec2(0, -tileMap->getTileSize().width)));
		}
		else if (direction == "left") {
			Player->stopAllActions();
			Player->runAction(RotateTo::create(0.1f, -90));
	        Player->runAction(MoveBy::create(0.3f, Vec2(-tileMap->getTileSize().width, 0)));
		}
		else if(direction=="right"){ 
			Player->stopAllActions();
			Player->runAction(RotateTo::create(0.1f, 90));
	        Player->runAction(MoveBy::create(0.3f, Vec2(tileMap->getTileSize().width, 0)));
		}
	}
}

Vec2 SingleGame::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height *tileMap->getTileSize().height) - pos.y) /
		tileMap->getTileSize().height;
	return Vec2(x, y);
}


void SingleGame::menuItemExitCallback(Ref*pSender) {
	Director::getInstance()->popScene();
}


void SingleGame::menuItemUp(cocos2d::Ref*pSender) {
	
	direction = "up";
	float x = Player->getPosition().x;
	float y = Player->getPosition().y+tileMap->getTileSize().width;
	
	Player->runAction(RotateTo::create(0.1f, 0));
	this->setPlayerPosition(Vec2(x, y));
}
void SingleGame::menuItemDown(cocos2d::Ref*pSender) {
	
	direction = "down";
	float x = Player->getPosition().x;
	float y = Player->getPosition().y - tileMap->getTileSize().width;
    
	Player->runAction(RotateTo::create(0.1f, 180));
	this->setPlayerPosition(Vec2(x, y));
}
void SingleGame::menuItemLeft(cocos2d::Ref*pSender) {
	
	direction = "left";
	float x = Player->getPosition().x- tileMap->getTileSize().width;
	float y = Player->getPosition().y;
	
	Player->runAction(RotateTo::create(0.1f, -90));
	this->setPlayerPosition(Vec2(x, y));
}
void SingleGame::menuItemRight(cocos2d::Ref*pSender) {
	
	direction = "right";
	float x = Player->getPosition().x+tileMap->getTileSize().width;
	float y = Player->getPosition().y;
	
	Player->runAction(RotateTo::create(0.1f, 90));
	this->setPlayerPosition(Vec2(x, y));
}
Vec2 SingleGame::weaponPosition(Vec2 position, float rx, float ry) {
	float x = tileMap->getTileSize().width*rx / sqrt(rx*rx + ry * ry);
	float y= tileMap->getTileSize().width*ry / sqrt(rx*rx + ry * ry);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 tileCoord; 
	int tileGid;
	
	for (int i = 0; i < 8; i++) {
		position.x += x;
		position.y += y;
		if(position.x>0&&position.x<visibleSize.width&&position.y>0&&position.y<visibleSize.height){ 
		   tileCoord = this->tileCoordFromPosition(position);
		   tileGid = collision->getTileGIDAt(tileCoord);
		   if (tileGid > 0) {
			   position.x -= x;
			   position.y -= y;
			   return position;
		   }
		}
		else {
			position.x -= x;
			position.y -= y;
		}
	}
	
	return position;
}

Vec2 SingleGame::RandomMovePosition(Sprite*opponent) {
	Vec2 position;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	int randx = random() % (int(tileMap->getTileSize().width)*5);
	int randy = random() % (int(tileMap->getTileSize().width)*5);
	int value = (random() % 4 )+ 1;
	if (value==1) {
		position = Vec2(opponent->getPosition().x - randx, opponent->getPosition().y - randy);
		
	}
	else if(value==2) {
		position = Vec2(opponent->getPosition().x + randx, opponent->getPosition().y + randy);
		
	}
	else if (value == 3) {
		position = Vec2(opponent->getPosition().x + randx, opponent->getPosition().y - randy);
	}
	else if (value == 4) {
		position = Vec2(opponent->getPosition().x - randx, opponent->getPosition().y +randy);
	}
	if (position.x <= 0 || position.y <= 0 || position.x >= visibleSize.width || position.y >= visibleSize.height)
		return RandomMovePosition(opponent);
	else{ 
	    Vec2 tileCoord = tileCoordFromPosition(position);
	    int tileGid = collision->getTileGIDAt(tileCoord);
	    if (tileGid > 0) {
		   return RandomMovePosition(opponent);
	    }
	    else return position;
	}
}

void SingleGame::opponentRepeatedlyMove(float dt) {
	Sprite*opponent;
	ProgressTimer*progress;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 tileCoord;
	int tileGid;
	for (int i = 1; i <= 3; i++) {
		progress = (ProgressTimer*)this->getChildByTag(i * 10);
		if(progress->getPercentage()>0)
		  opponent=(Sprite*)this->getChildByTag(i);
		else continue;
		Vec2 position = RandomMovePosition(opponent);
		Vec2 opp_p = opponent->getPosition();
		float rx = position.x - opp_p.x;
		float ry = position.y - opp_p.y;
		int nx = rx / tileMap->getTileSize().width;
		int ny = ry / tileMap->getTileSize().width;
		std::vector<Vec2>Path;
		Vector<FiniteTimeAction*>action;
		for (int j = 0; j < abs(nx); j++) {
			if(nx>0)
			
			   Path.push_back(Vec2(tileMap->getTileSize().width, 0));
			else 
		       Path.push_back(Vec2(-tileMap->getTileSize().width, 0));
		}
		for (int j = 0; j < abs(ny); j++) {
			if(ny>0)
			   Path.push_back(Vec2(0, tileMap->getTileSize().width));
			else
			   Path.push_back(Vec2(0, -tileMap->getTileSize().width));
		}
		for (int j = 0; j < Path.size(); j++) {
			Vec2 rp = Path.at(j);
			opp_p+=rp;
			if(opp_p.x >0 && opp_p.y >0 && opp_p.x < visibleSize.width&&opp_p.y < visibleSize.height){ 
			    tileCoord = tileCoordFromPosition(opp_p);
			    tileGid = collision->getTileGIDAt(tileCoord);
			}
			else {
				opp_p -= rp;
				continue; 
			}
			if (tileGid > 0) {
				opp_p -= rp;
			}
			else {  
			    if (j < abs(nx)) {
				
				    if (rp.x > 0){
  
					   auto Roate = RotateTo::create(0.1f, 90);
					   auto Move = MoveBy::create(1.0f, rp);
					   action.pushBack(Roate);
					   action.pushBack(Move);
				    }
				    else {
				   	   auto Roate = RotateTo::create(0.1f, -90);
					   auto Move = MoveBy::create(1.0f, rp);
					   action.pushBack(Roate);
					   action.pushBack(Move);
				    }
			    }
			    else {
				    if (rp.y > 0) {
					   auto Roate = RotateTo::create(0.1f, 0);
					   auto Move = MoveBy::create(1.0f, rp);
					   action.pushBack(Roate);
					   action.pushBack(Move);
				    }
				    else {
					   auto Roate = RotateTo::create(0.1f, 180);
					   auto Move = MoveBy::create(1.0f, rp);
					   action.pushBack(Roate);
					   action.pushBack(Move);
				    }
			    }
			}
		}
		auto callfunc = CallFunc::create([=] {
			opponent_ismoving[i] = false;
		});
		action.pushBack(callfunc);
		if (opponent_ismoving[i] == false) {
			opponent_ismoving[i] = true;
			
			opponent->runAction(Sequence::create(action));
		}
	}

}
void SingleGame::attackUpdate(float dt) {
	Sprite*opponent;
	ProgressTimer*progress;
	
	float rx, ry, distance;
	
	for (int i = 1; i <= 3; i++) {
		progress = (ProgressTimer*)this->getChildByTag(i * 10);
		if(progress->getPercentage()>0)
		   opponent =(Sprite*)this->getChildByTag(i);
		else continue;
		Vec2 opp_p = opponent->getPosition();
		Vec2 position = Player->getPosition();
	    rx = position.x- opp_p.x;
		ry = position.y- opp_p.y;
		distance = sqrt(rx*rx + ry * ry);
		
		if (distance < tileMap->getTileSize().width * 5) {
			count[i] += 1;
			if(count[i]%20==1){  
			   
			   for (int j = 0; j < 5; j++) {
				   if (Fruits[j].index == i) {
					
					   auto weapon = Sprite::create(Fruits[j].weapon);
					   weapon->setPosition(opp_p);
					   this->addChild(weapon,2);
					   weapon->setRotation(90 - atan2(ry, rx)*57.29578);
					   opponent->setRotation(90 - atan2(ry, rx)*57.29578);
					   

					   Opp_weapon.pushBack(weapon);
					  
					   float speed = tileMap->getTileSize().width * 5;
					   Vec2 weaponTerminal = weaponPosition(opp_p, rx, ry);
					   rx = weaponTerminal.x- opp_p.x;
					   ry = weaponTerminal.y-opp_p.y;
					   float time = sqrt(rx*rx + ry * ry) / speed;
					  
					   auto callfunc = CallFunc::create([=] {
						    
							this->removeChild(Opp_weapon.at(0));
							 Opp_weapon.erase(0);
						});
					    weapon->runAction(Sequence::create(MoveTo::create(time, weaponTerminal), FadeOut::create(0.1f), callfunc,NULL));
						
					   break;
				   }
			   }
			}
		}
		
		
		
	}
}

void SingleGame::OppAttackValidityUpdate(float dt) {
	Vec2 Player_position;
	Vec2 weapon_position;
	Size size = Player->getContentSize();
	float percentage;
	float rx, ry;
	
	for (int i = 0; i < Opp_weapon.size(); i++) {
		//if(Opp_weapon[i].test==false){ 
		   Player_position = Player->getPosition();
		   weapon_position = Opp_weapon.at(i)->getPosition();
		   rx = Player_position.x - weapon_position.x;
		   ry = Player_position.y - weapon_position.y;
		   if (abs(rx) < size.width/2 &&abs(ry) < size.height/2) {
			  percentage = PlayerProgress->getPercentage();
			  percentage = percentage - 6.25f;
			  PlayerProgress->setPercentage(percentage);
			  
			  this->removeChild(Opp_weapon.at(i));
			  Opp_weapon.erase(i);
			 
			  
		   }
		   
		
	}

}
void SingleGame::AttackValidityUpdate(float dt) {
	Vec2 Opp_position;
	Vec2 weapon_position;
	Size size = Player->getContentSize();
	Sprite*opponent;
	ProgressTimer*progress;
	float percentage;
	float rx, ry;
	
	for (int i = 1; i <= 3; i++) {
		
		progress = (ProgressTimer*)this->getChildByTag(10 * i);
		if(progress->getPercentage()>0)
			opponent = (Sprite*)this->getChildByTag(i);
		else continue;
		for(int j=0;j<Weapon.size();j++){   
		   Opp_position = opponent->getPosition();
		   weapon_position = Weapon.at(j)->getPosition();
		   rx = Opp_position.x - weapon_position.x;
		   ry = Opp_position.y - weapon_position.y;
		   if (abs(rx) < size.width / 2 && abs(ry) < size.height / 2) {
			   percentage = progress->getPercentage();
			   percentage = percentage - 6.25f*aggressivity[weaponIndex];
			   progress->setPercentage(percentage);
			   if (percentage<= 0) {
				   oppDead[i] =true;
				   auto callfunc = CallFunc::create([=] {
					   
					   removeChildByTag(i);
				   });
				   
				   opponent->runAction(Sequence::create(FadeOut::create(2.0f), callfunc, NULL));
				  
			   }
			  
			   this->removeChild(Weapon.at(j));
			   Weapon.erase(j);
			  

		   }
		}
	}
}
void SingleGame::TestResultUpdate(float dt) {
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (PlayerProgress->getPercentage() <= 0) {
		if(Over==false){  
			Over = true;
			auto slogan = Sprite::create("slogan/lose.png");
		    slogan->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		    slogan->setScale(0.1f);
		    this->addChild(slogan, 4);
		    auto spawn = Spawn::create(RotateBy::create(2.0f, 720.0f), ScaleTo::create(2.0f, 1.0f), NULL);
			auto delay = DelayTime::create(5.0f);
		    auto fadeout = FadeOut::create(2.0f);
			auto callfunc = CallFuncN::create([=](Ref*pSender) {
			 Director::getInstance()->popScene();
		    });
		    slogan->runAction(Sequence::create(spawn,delay, fadeout, callfunc, NULL));
		}
	}
	else if(oppDead[1]==true&&oppDead[2]==true&&oppDead[3]==true){
		if(Over==false){
			Over =true;
		   auto slogan = Sprite::create("slogan/win.png");
		   slogan->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		   slogan->setScale(0.1f);
		   this->addChild(slogan, 4);
		   auto spawn = Spawn::create(RotateBy::create(2.0f, 720.0f), ScaleTo::create(2.0f, 1.0f), NULL);
		   auto delay = DelayTime::create(5.0f);
		   auto fadeout = FadeOut::create(2.0f);
		   auto callfunc = CallFuncN::create([=](Ref*pSender) {
			  Director::getInstance()->popScene();
		});
		slogan->runAction(Sequence::create(spawn,delay,fadeout, callfunc, NULL));
		}
	}
	else if (CountDownProgress->getPercentage() <= 0) {
		if (Over == false) {
			Over = true;
			auto slogan = Sprite::create("slogan/lose.png");
			slogan->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
			slogan->setScale(0.1f);
			this->addChild(slogan, 4);
			auto spawn = Spawn::create(RotateBy::create(2.0f, 720.0f), ScaleTo::create(2.0f, 1.0f), NULL);
			auto delay = DelayTime::create(5.0f);
			auto fadeout = FadeOut::create(2.0f);
			auto callfunc = CallFuncN::create([=](Ref*pSender) {
				Director::getInstance()->popScene();
			});
			slogan->runAction(Sequence::create(spawn,delay, fadeout, callfunc, NULL));
		}
	}
}
void SingleGame::PopWeaponUpdate(float dt) {
	auto weapons = tileMap->getObjectGroup("weapons");
	int rand1, rand2;
	float x, y;
	Sprite*weapon;
	timeDelay ++;
	if(timeDelay%80==1){    
       while (1) {
		   rand1 = rand() % 8;
		   if (showWeapon[rand1] == true)
			   continue;
		   else {
			   ValueMap wp = weapons->getObject(PopName[rand1]);
			   showWeapon[rand1] = true;
			   index1.push_back(rand1);
			  
			   x = wp["x"].asFloat();
			   y = wp["y"].asFloat();
			   rand2 = rand() % 5;
			   weapon = Sprite::create(Pop[rand2].weaponPickup);
			   weapon->setPosition(Vec2(x*scale, y*scale));
			   this->addChild(weapon, 0);
			   PopWeapon.pushBack(weapon);
			   index2.push_back(rand2);
			   auto callback = CallFunc::create([=] {
				  this->removeChild(PopWeapon.at(0));
				  PopWeapon.erase(0);
				  index2.erase(index2.begin());
				  showWeapon[index1.at(0)] = false;
				  index1.erase(index1.begin());
				  
			   });
			   weapon->runAction(Sequence::create(DelayTime::create(10.0f), FadeOut::create(2.0f), callback, NULL));
			   break;
		   }
	   }
	}
	
}
void SingleGame::TestPickWeaponUpdate(float dt) {
	Vec2 PlayerPosition;
	Vec2 WeaponPosition;
	float rx, ry;
	Sprite*weapon;
	Size s;
	PlayerPosition = Player->getPosition();
	for (int i = 0; i < PopWeapon.size(); i++) {
		weapon = PopWeapon.at(i);
		s = weapon->getContentSize();
		WeaponPosition = weapon->getPosition();
		rx = PlayerPosition.x - WeaponPosition.x;
		ry = PlayerPosition.y - WeaponPosition.y;
		if (abs(rx) < s.width/2&&abs(ry) < s.height/2) {
			this->removeChild(PopWeapon.at(i));
			PopWeapon.erase(i);
			auto sprite = Sprite::create(Pop[index2.at(i)].newCharacter);
			sprite->setPosition(PlayerPosition);
			this->addChild(sprite, 2);
			auto sprite1 = Player;
			Player = sprite;
			sprite1->runAction(Hide::create());
			showWeapon[index1.at(i)] = false;
			index1.erase(index1.begin() + i);
			weaponIndex = index2.at(i);
			index2.erase(index2.begin() + i);
		}

	}
}
void SingleGame::CountDownUpdate(float dt) {
	float percentage = CountDownProgress->getPercentage();
	percentage = percentage - 0.055f;
	CountDownProgress->setPercentage(percentage);
	int a = percentage * 1.8f;
	auto str = String::createWithFormat("%d s", a);
	Timettf->setString(str->getCString());
}
void SingleGame::myupdate(float dt) {
	CountDownUpdate(dt);
	TestResultUpdate(dt);
	AttackValidityUpdate(dt);
	OppAttackValidityUpdate(dt);
	opponentRepeatedlyMove(dt);
	PopWeaponUpdate(dt);
	TestPickWeaponUpdate(dt);
	attackUpdate(dt);
	if (Over == true)
		unschedule(schedule_selector(SingleGame::myupdate));

}
void SingleGame::update(float dt) {
	
	
}
