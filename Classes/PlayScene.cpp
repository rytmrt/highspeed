/*
 * PlayScene.cpp
 *
 *  Created on: 2013/11/26
 *      Author: s112179
 */

#include "PlayScene.h"
#include "TitleScene.h"
#include "Collision.h"
#include "Input.h"

#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

// スタートするまでの時間
static const int START_TIME = 180;
// いっせ〜のせ！の合計フレーム
static const int ISSENO_TIME = 180;
// いっせ〜のせ！が出る残りフレーム
static const int ISSENO_LEFT_TIME = 60;

/**
 * @fn		initTeamPlay()
 * @brief	プレイシーンの初期化
 */
void PlayScene::initPlayScene()
{
	// トランプのスプライトバッチノード生成
	SpriteBatchNode* pTrunmpBatchNode = SpriteBatchNode::create("trump.png");
	this->addChild(pTrunmpBatchNode);

	// 文字のスプライトバッチノード生成
	SpriteBatchNode* pStringBatchNode = SpriteBatchNode::create("String.png");
	this->addChild(pStringBatchNode);

	// 背景のスプライトを生成する
	Sprite* pBackGround = Sprite::create("BG.png", Rect(0, 160, 480, 320));
	// 背景の回転
	pBackGround->setRotation(90.0f);
	// 背景の移動
	pBackGround->setPosition(Point(160,240));
	// レイヤーに追加する
	this->addChild(pBackGround,0);

	// 場札
	m_pField = new Field();
	m_pField->Initialize(this, pTrunmpBatchNode);
	for (int i = 0; i < Utility::PLAYER_NUM; ++i)
	{
		// デッキ生成
		m_pDeck[i] = new Deck();
		m_pDeck[i]->Initialize(this, pTrunmpBatchNode, (Utility::PLAYER)i);

		// 手札生成
		m_pHand[i] = new Hand();
		m_pHand[i]->Initialize(this, pTrunmpBatchNode, (Utility::PLAYER)i);
	}

	// インプット
	Input::GetInstance()->init();

	// CPU初期化
	m_cpuCount = 0;
	m_pHand[1]->SelectCard(0);

	// ランプスプライト
	m_pLampSprite = Sprite::create("Lamp.png", Rect(0, 0, 512, 128));
	// 表示場所移動
	m_pLampSprite->setPosition(Point(Utility::SCRN_WHIDTH / 2, Utility::SCRN_HEIGHT / 2));
	// サイズ設定
	m_pLampSprite->setScale(0.625f);
	// レイヤーに追加する
	this->addChild(m_pLampSprite, 10);

	// いっせ〜のっ！スプライト
	for (int i = 0; i < Utility::PLAYER_NUM; ++i)
	{
		m_pIssenoSprite[i] = Sprite::createWithTexture(pStringBatchNode->getTexture(), Rect(0, 384, 192, 32));

		// 表示位置移動
		m_pIssenoSprite[i]->setPosition(Point(Utility::SCRN_WHIDTH / 2, Utility::SCRN_HEIGHT / 2 + 90 * (i * 2 -1)));

		// 表示しない
		m_pIssenoSprite[i]->setVisible(false);

		// プレイヤー2なら回転
		if (i == Utility::PLAYER_2)
		{
			m_pIssenoSprite[i]->setRotation(180.0f);
		}

		// レイヤーに追加する
		this->addChild(m_pIssenoSprite[i], 10);
	}

	// 押されてないときのスプライト
	Sprite* item1 = Sprite::create("trump.png", Rect(0,704,64,64));

	// 押されたときのスプライト
	Sprite* item2 = Sprite::create("trump.png", Rect(64,704,64,64));

	// リターンボタン
	MenuItemSprite *pReturnItem = MenuItemSprite::create(
											item1,
											item2,
											this,
											menu_selector(PlayScene::nextScene));

	pReturnItem->setPosition(Utility::SCRN_WHIDTH/2, Utility::SCRN_HEIGHT/2);
	m_pButton = Menu::create(pReturnItem, NULL);
	m_pButton->setPosition(Point::ZERO);
	m_pButton->setEnabled(false);
	m_pButton->setVisible(false);
	this->addChild(m_pButton, 1);

	// 変数初期化
	m_drawFlag = false;
	m_anySend = false;
	m_start = false;
	m_startTime = START_TIME;
	m_issenoTime = ISSENO_LEFT_TIME;

	// 透明にする
/*	pPlay->setOpacity(0);*/

	// BGMの準備
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Play.mp3");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Play.mp3", true);

	schedule(schedule_selector(PlayScene::update), 1.0f / 60.0f);
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
bool PlayScene::init()
{
	// 基底クラスの初期化
	if(!Layer::init())
	{
		return false;
	}

	// マルチタッチできるよ
	setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);
	setTouchEnabled(true);

	// プレイシーンの初期化
	this->initPlayScene();

	return true;
}

/**
 * @brief	メインシーンの更新
 */
void PlayScene::update(float deltatime)
{

	if (m_startTime <= START_TIME - 45 * 3)
	{
		if (m_startTime == START_TIME - 45 * 3)
		{
			SimpleAudioEngine::getInstance()->playEffect("Start.mp3");
		}
		m_pLampSprite->setTextureRect(Rect(0, 384, 512, 128));
	}
	else if (m_startTime <= START_TIME - 45 * 2)
	{
		if (m_startTime == START_TIME - 45 * 2)
		{
			SimpleAudioEngine::getInstance()->setEffectsVolume(3.0f);
			SimpleAudioEngine::getInstance()->playEffect("StartCount.mp3");
		}
		m_pLampSprite->setTextureRect(Rect(0, 256, 512, 128));
	}
	else if (m_startTime <= START_TIME - 45)
	{
		if (m_startTime == START_TIME - 45 * 1)
		{
			SimpleAudioEngine::getInstance()->setEffectsVolume(3.0f);
			SimpleAudioEngine::getInstance()->playEffect("StartCount.mp3");
		}
		m_pLampSprite->setTextureRect(Rect(0, 128, 512, 128));
	}
	SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);

	// スタートタイムが残っているならリターン
	if (m_startTime > 0)
	{
		--m_startTime;
		return;
	}

	for (int i = 0; i < Utility::PLAYER_NUM; ++i)
	{
		m_pDeck[i]->Update();
		m_pHand[i]->Update();
	}
	m_pField->Update();
	m_drawFlag = false;

	///// プレイヤーの処理 /////
	// 手札のタッチ処理
	HandTouchWork();
	// フィールド
	FieldTouchWork();

	// 敵の処理を行う
	CPUWalk();

	// カードを引いたらタイムリセットして描画しない
	if (m_drawFlag)
	{
		m_issenoTime = ISSENO_TIME;
		for (int i = 0; i < Utility::PLAYER_NUM; ++i)
		{
			m_pIssenoSprite[i]->setVisible(false);
		}
	}

	// 勝敗判定
	if (WhoIsWinner() >= 0)
	{
		if (m_pIssenoSprite[0]->getScale() != 1.3f)
		{
			SimpleAudioEngine::getInstance()->playEffect("End1.mp3");
		}
		for (int i = 0; i < Utility::PLAYER_NUM; ++i)
		{
			m_pIssenoSprite[i]->setVisible(true);
			if (WhoIsWinner() == 2)
			{
				m_pIssenoSprite[i]->setTextureRect(Rect(0, 200, 220, 100));
			}
			else
			{
				m_pIssenoSprite[i]->setTextureRect(Rect(0, 100 * ((i + WhoIsWinner()) % 2), 220, 100));
			}
			m_pIssenoSprite[i]->setScale(1.3f);
		}
		m_pButton->setEnabled(true);
		m_pButton->setVisible(true);
	}
	// なんもだせんかスタートなら
	else if (!IsAnySendCard() || !m_start)
	{
		--m_issenoTime;
		// 残りフレームISSENO_LEFT_TIME以下
		if (m_issenoTime <= ISSENO_LEFT_TIME)
		{
			// いっせ〜のせっ！表示
			for (int i = 0; i < Utility::PLAYER_NUM; ++i)
			{
				m_pIssenoSprite[i]->setVisible(true);
			}
			// カウントが0以下になったら
			if (m_issenoTime <= 0)
			{
				if (!m_start)
				{
					// フィールドにデッキからカードを出す
					m_pField->SetLeftField(m_pDeck[Utility::PLAYER_1]->Draw());
					m_pField->SetRightField(m_pDeck[Utility::PLAYER_2]->Draw());
				}
				// ランプ消す
				m_pLampSprite->setVisible(false);
				m_start = true;
				// プレイヤー2のデッキがあるなら
				if (m_pDeck[Utility::PLAYER_2]->GetNum() > 0)
				{
					m_pField->SetLeftField(m_pDeck[Utility::PLAYER_2]->Draw());
					SimpleAudioEngine::getInstance()->playEffect("PutCard2.mp3");
				}
				else
				{
					// 選択しているところにカードがないなら
					if (m_pHand[Utility::PLAYER_2]->GetCard().m_suit == Card::UNKNOWN)
					{
						for (int i = 0; i < 3; ++i)
						{
							// 左から順に見てあるカードを置く
							if (!m_pHand[Utility::PLAYER_2]->IsPutCard(i))
							{
								m_pField->SetLeftField(m_pHand[Utility::PLAYER_2]->SendCard(i));
								SimpleAudioEngine::getInstance()->playEffect("PutCard2.mp3");
								break;
							}
						}
					}
					else
					{
						m_pField->SetLeftField(m_pHand[Utility::PLAYER_2]->SendCard());
						SimpleAudioEngine::getInstance()->playEffect("PutCard2.mp3");
					}
				}
				// プレイヤー1のデッキがあるなら
				if (m_pDeck[Utility::PLAYER_1]->GetNum() > 0)
				{
					m_pField->SetRightField(m_pDeck[Utility::PLAYER_1]->Draw());
					SimpleAudioEngine::getInstance()->playEffect("PutCard2.mp3");
				}
				else
				{
					// 選択しているところにカードがないなら
					if (m_pHand[Utility::PLAYER_1]->GetCard().m_suit == Card::UNKNOWN)
					{
						for (int i = 0; i < 3; ++i)
						{
							// 左から順に見てあるカードを置く
							if (!m_pHand[Utility::PLAYER_1]->IsPutCard(i))
							{
								m_pField->SetRightField(m_pHand[Utility::PLAYER_1]->SendCard(i));
								SimpleAudioEngine::getInstance()->playEffect("PutCard2.mp3");
								break;
							}
						}
					}
					else
					{
						m_pField->SetRightField(m_pHand[Utility::PLAYER_1]->SendCard());
						SimpleAudioEngine::getInstance()->playEffect("PutCard2.mp3");
					}
				}

				for (int i = 0; i < Utility::PLAYER_NUM; ++i)
				{
					// いっせ〜のせっ！非表示
					m_pIssenoSprite[i]->setVisible(false);
				}
				m_issenoTime = ISSENO_TIME;
			}
		}
	}



	// インプット
	Point temp = Input::GetInstance()->GetTouch();
	//Log("%f,%f",temp.x,temp.y);
	Input::GetInstance()->update(deltatime);

	// 描画
	Render();
}

/**
 * @fn		Render()
 * @brief	描画処理
 */
void PlayScene::Render()
{
	m_pField->Render();
	for (int i = 0; i < Utility::PLAYER_NUM; ++i)
	{
		m_pDeck[i]->Render();
		m_pHand[i]->Render();
	}
}

/**
 * @fn		static cocos2d::Scene* scene()
 * @brief	ロゴシーンを追加した、シーンの生成
 * @return	シーンのアドレス
 */
Scene* PlayScene::scene()
{
    Scene *scene = Scene::create();

    PlayScene *layer = PlayScene::create();

    scene->addChild(layer);

    return scene;
}

/**
 * @fn		void nextScene()
 * @brief	次のシーンへと切り替える
 */
void PlayScene::nextScene(Object* pSender)
{
	int soundID = SimpleAudioEngine::getInstance()->playEffect("ButtonPush.mp3");

	// BGMをとめる
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	// 次のシーンを生成する
	Scene* pNextScene = TitleScene::scene();

	// トランジションをつける
	pNextScene = TransitionTurnOffTiles::create(1.0f,pNextScene);

	// シーンを切り替える
	Director::sharedDirector()->replaceScene(pNextScene);
}


/// 手札のタッチ処理
void PlayScene::HandTouchWork()
{
	for (int i = 0; i < 3; ++i)
	{
		// AABBとタッチ座標
		if (!AABB2Point(m_pHand[Utility::PLAYER_1]->GetAABB(i), Input::GetInstance()->GetTouch())) continue;
		// カードがおけるなら
		if (m_pHand[Utility::PLAYER_1]->IsPutCard(i))
		{
			if (m_pDeck[Utility::PLAYER_1]->GetNum() > 0 && m_start)
			{
				SimpleAudioEngine::getInstance()->playEffect("PutCard1.mp3");
				m_pHand[Utility::PLAYER_1]->SetCard(m_pDeck[Utility::PLAYER_1]->Draw(), i);
				m_drawFlag = true;
			}
		}
		else // 置けないなら選択した
		{
			if (m_pHand[Utility::PLAYER_1]->GetSelectLocation() != i)
			{
				m_pHand[Utility::PLAYER_1]->SelectCard(i);
				SimpleAudioEngine::getInstance()->playEffect("Select.mp3");
			}
		}
	}
}

/// フィールドのタッチ処理
void PlayScene::FieldTouchWork()
{
	// 何も選択されていないなら何もしない
	if (m_pHand[Utility::PLAYER_1]->GetSelectLocation() < 0) return;

	for (int i = 0; i < 2; ++i)
	{
		// AABBとタッチ座標
		if (!AABB2Point(m_pField->GetAABB(i), Input::GetInstance()->GetTouch())) continue;

		// フィールドのカード
		Card fCard;
		if (i == 0) fCard = m_pField->GetLeftField();
		else		fCard = m_pField->GetRightField();
		// 選択されているカード
		Card sCard = m_pHand[Utility::PLAYER_1]->GetCard();

		// 選択されたカードがおけるなら置く
		if (fCard.m_number == sCard.m_number || fCard.m_suit == sCard.m_suit)
		{
			SimpleAudioEngine::getInstance()->playEffect("PutCard2.mp3");
			if (i == 0) m_pField->PutLeftField(m_pHand[Utility::PLAYER_1]->SendCard());
			else		m_pField->PutRightField(m_pHand[Utility::PLAYER_1]->SendCard());
		}
	}
}

/**
 * @fn		void CPUWalk()
 * @brief	CPUの仕事
 */
void PlayScene::CPUWalk()
{
	// CPU処理
	m_cpuCount++;
	m_cpuCount %= 30;
	//CPU行動
	if( m_cpuCount <= 0 )
	{
		//　カードを引いて手札に入れる
		for (int k = 0; k < 3; ++k)
		{
			if (m_pHand[1]->IsPutCard(k))
			{
				if (m_pDeck[Utility::PLAYER_2]->GetNum() > 0 && m_start)
				{
					m_pHand[Utility::PLAYER_2]->SetCard(m_pDeck[Utility::PLAYER_2]->Draw(), k);
					return;
				}
			}
		}

		// カードの選択
		{
			Card selectCard = m_pHand[Utility::PLAYER_2]->GetCard();
			Card leftFieldCard = m_pField->GetLeftField();
			Card rightFieldCard = m_pField->GetRightField();

			if( !(leftFieldCard.m_number == selectCard.m_number || leftFieldCard.m_suit == selectCard.m_suit
			 || rightFieldCard.m_number == selectCard.m_number || rightFieldCard.m_suit == selectCard.m_suit) )
			{
				for (int k = 0; k < 3; ++k)
				{
					if (!m_pHand[Utility::PLAYER_2]->IsPutCard(k) &&
							m_pHand[Utility::PLAYER_2]->GetSelectLocation() != k)
					{
						SimpleAudioEngine::getInstance()->playEffect("Select.mp3");
						m_pHand[Utility::PLAYER_2]->SelectCard(k);
					}
					selectCard = m_pHand[Utility::PLAYER_2]->GetCard();
					if( leftFieldCard.m_number == selectCard.m_number || leftFieldCard.m_suit == selectCard.m_suit
					 || rightFieldCard.m_number == selectCard.m_number || rightFieldCard.m_suit == selectCard.m_suit )
					{
						return;
					}
				}
			}
		}

		// カードをフィールドに出す
		{
			// カードの取得
			bool sendResult = false;
			Card selectCard = m_pHand[Utility::PLAYER_2]->GetCard();
			Card fieldCard = m_pField->GetLeftField();

			// フィールドの左右どちらかにカードを出せるか確認し、出せるなら出す
			if( fieldCard.m_number == selectCard.m_number || fieldCard.m_suit == selectCard.m_suit )
			{
				sendResult = m_pField->PutLeftField(m_pHand[Utility::PLAYER_2]->SendCard());
			}
			if( sendResult ){return;}

			fieldCard = m_pField->GetRightField();
			if( fieldCard.m_number == selectCard.m_number || fieldCard.m_suit == selectCard.m_suit )
			{
				sendResult = m_pField->PutRightField(m_pHand[Utility::PLAYER_2]->SendCard());
			}
			if( sendResult ){return;}
		}

	}
}

/// どれか出せるか
bool PlayScene::IsAnySendCard()
{
	for (int i = 0; i < Utility::PLAYER_NUM; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (m_pHand[i]->GetCard(j).m_number == m_pField->GetLeftField().m_number ||
				m_pHand[i]->GetCard(j).m_suit == m_pField->GetLeftField().m_suit)
			{
				return true;
			}
			if (m_pHand[i]->GetCard(j).m_number == m_pField->GetRightField().m_number ||
				m_pHand[i]->GetCard(j).m_suit == m_pField->GetRightField().m_suit)
			{
				return true;
			}
		}
	}
	return false;
}

/**
 * @fn		int WhoIsWinner()
 * @brief	勝敗判定
 * @out		プレイヤーの番号
 * @atention -1なら勝者なし
 */
int PlayScene::WhoIsWinner()
{
	// 勝敗判定
	int winner = -1;

	if( m_pDeck[0]->GetNum() <= 0 &&
		m_pHand[0]->IsPutCard(0) &&
		m_pHand[0]->IsPutCard(1) &&
		m_pHand[0]->IsPutCard(2) )
	{
		winner = 0;
	}

	if( m_pDeck[1]->GetNum() <= 0 &&
		m_pHand[1]->IsPutCard(0) &&
		m_pHand[1]->IsPutCard(1) &&
		m_pHand[1]->IsPutCard(2) )
	{
		if(winner == 0)
		{
			winner = 2;
		}
		else
		{
			winner = 1;
		}
	}

	//勝者なし
	return winner;
}

