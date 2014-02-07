/*
 * TitleScene.cpp
 *
 *  Created on: 2013/12/17
 *      Author: s112179
 */
#include "TitleScene.h"
#include "PlayScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

/**
 * @fn		initTeamTitle()
 * @brief	タイトルシーンの初期化
 */
void TitleScene::initTitleScene()
{
	// カードのスプライトバッチノード生成
	SpriteBatchNode* pBatchNode = SpriteBatchNode::create("title.png");
	this->addChild(pBatchNode);

	// 背景のスプライトを生成する
	Sprite* pBackGround = Sprite::createWithTexture(pBatchNode->getTexture(), Rect(0, 200, 480, 320));
	// 背景の回転
	pBackGround->setRotation(90.0f);
	// 背景の移動
	pBackGround->setPosition(Point(160,240));
	// レイヤーに追加する
	this->addChild(pBackGround,0);

	// タイトルのスプライトを生成する
	m_pTitle = CCSprite::createWithTexture(pBatchNode->getTexture(), Rect(0, 0, 250, 160));
	// タイトルの移動
	m_pTitle->setPosition(Point(160,330));
	// レイヤーに追加する
	this->addChild(m_pTitle,1);

	// 透明にする
/*	m_pTitle->setOpacity(0);*/

	schedule(schedule_selector(TitleScene::update), 1.0f / 60.0f);

	// BGMの準備
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Title.mp3");
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Title.mp3", true);


	SimpleAudioEngine::sharedEngine()->preloadEffect("ButtonPush.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("DrawCard.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("PutCard1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("PutCard2.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Start.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("StartCount.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("End1.mp3");
	SimpleAudioEngine::sharedEngine()->preloadEffect("Select.mp3");



	// タイトル文字の位置
	m_textPosY = 330.0f;
	m_count = 0;
}

//////////////////
// public method
//////////////////

/**
 * @fn		bool init()
 * @brief	初期化
 * @retval	true	初期化に成功
 * @retval	false	初期化に失敗
 */
bool TitleScene::init()
{
	// 基底クラスの初期化
	if(!CCLayer::init())
	{
		return false;
	}

	// タッチできるよ
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	// 押されてないときのスプライト
	Sprite* item1 = Sprite::create("title.png", Rect(250,0,259,44));

	// 押されたときのスプライト
	Sprite* item2 = Sprite::create("title.png", Rect(250,44,259,44));

	// スタートボタン
	MenuItemSprite *pStartItem = MenuItemSprite::create(
											item1,
											item2,
											this,
											menu_selector(TitleScene::nextScene));

	pStartItem->setPosition(160,120);
	Menu* pButton = Menu::create(pStartItem, NULL);
	pButton->setPosition(Point::ZERO);
	this->addChild(pButton, 1);

/*	// 押されてないときのスプライト
	CCSprite* item1 = CCSprite::create("sample.png", CCRectMake(0,0,128,64));

	// 押されたときのスプライト
	CCSprite* item2 = CCSprite::create(NULL);
	item2->setColor(ccc3(102,102,102));

	CCMenuItemSprite* itemSprite = CCMenuItemSprite::create(
														item1,
														item2,
														this,
														menu_selector(TitleScene::))

	Menu* menu = CCMenu::createWithArray(arr);
	menu->setPosition(CCPointZero);

	CCArray* arr = CCArray::create();
	arr->addObject(itemSprite);*/



	// クローズボタン
	MenuItemImage *pCloseItem = MenuItemImage::create(
	                                        "CloseNormal.png",
	                                        "CloseSelected.png",
	                                        this,
	                                        menu_selector(TitleScene::menuCloseCallback));

	pCloseItem->setPosition(280,30);
	Menu* pMenu = Menu::create(pCloseItem, NULL);
	pMenu->setPosition(Point::ZERO);
	this->addChild(pMenu, 1);

	// タイトルシーンの初期化
	this->initTitleScene();

	return true;
}

/**
 * @brief	メインシーンの更新
 */
void TitleScene::update(float deltatime)
{

	m_count+=3;
	if(m_count >= 3600) { m_count = 0; }
	m_textPosY += cos( m_count * (3.1415926535f / 180.0f) );
	// タイトルの移動
	m_pTitle->setPosition(ccp(160,m_textPosY));

	// 描画
	Render();
}

/**
 * @fn		Render()
 * @brief	描画処理
 */
void TitleScene::Render()
{

}

/**
 * @fn		static cocos2d::CCScene* scene()
 * @brief	ロゴシーンを追加した、シーンの生成
 * @return	シーンのアドレス
 */
Scene* TitleScene::scene()
{
    Scene *scene = Scene::create();

    TitleScene *layer = TitleScene::create();

    scene->addChild(layer);

    return scene;
}

/**
 * @fn		void nextScene()
 * @brief	次のシーンへと切り替える
 */
void TitleScene::nextScene(Object* pSender)
{
	int soundID = SimpleAudioEngine::sharedEngine()->playEffect("ButtonPush.mp3");

	// BGMをとめる
	SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);

	// 次のシーンを生成する
	Scene* pNextScene = PlayScene::scene();

	// トランジションをつける
	pNextScene = TransitionTurnOffTiles::create(1.0f,pNextScene);

	// シーンを切り替える
	Director::sharedDirector()->replaceScene(pNextScene);

}


void TitleScene::menuCloseCallback(Object* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    Director::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

