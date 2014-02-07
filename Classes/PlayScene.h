/*
 * PlayScene.h
 *
 *  Created on: 2013/11/26
 *      Author: s112179
 */

#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_

#include "Deck.h"
#include "Hand.h"
#include "Field.h"

/**
 * @class 	PlayScene
 * @brief	プレイシーンクラス
 */
class PlayScene : public cocos2d::Layer
{
	// マルチタッチの取得数
	static const int TOUCHES_NUM = 10;


	//////////////////
	// private value
	//////////////////
private:
	// デッキ
	Deck* m_pDeck[Utility::PLAYER_NUM];
	// 手札
	Hand* m_pHand[Utility::PLAYER_NUM];
	// 場札
	Field* m_pField;

	// CPU
	static const int CPU_MEVE_COUNT = 30;
	int m_cpuCount;
	int m_pattern;
	enum CPUMovePattern
	{
		CPU_SET = 0,
		CPU_SELECT,
		CPU_SEND,
	};

	// 引いたフラグ
	bool m_drawFlag;
	// 何かおける
	bool m_anySend;

	// スタートフラグ
	bool m_start;
	// スタートタイム
	int m_startTime;
	// ランプスプライト
	cocos2d::Sprite* m_pLampSprite;

	// いっせ〜のっ！タイム
	int m_issenoTime;
	// いっせ〜のっ！スプライト
	cocos2d::Sprite* m_pIssenoSprite[Utility::PLAYER_NUM];

	// ボタン
	cocos2d::Menu* m_pButton;


	//////////////////
	// private method
	//////////////////
private:

	/**
	 * @fn		initPlayScene()
	 * @brief	プレイシーンの初期化
	 */
	void initPlayScene();

	/**
	 * @fn		Render()
	 * @brief	描画処理
	 */
	void Render();

	//////////////////
	// public method
	//////////////////
public:

	/**
	 * @fn		static PlayScene* create()
	 * @brief	プレイシーンの生成
	 * @return	プレイシーンのアドレス
	 */
	CREATE_FUNC(PlayScene);

	/**
	 * @fn		bool init()
	 * @brief	初期化
	 * @retval	true	初期化に成功
	 * @retval	false	初期化に失敗
	 */
	bool init();

	/**
	 * @brief	メインシーンの更新
	 */
	void update(float deltatime);

	/**
	 * @fn		static cocos2d::CCScene* scene()
	 * @brief	プレイシーンを追加したシーンの生成
	 * @return	シーンのアドレス
	 */
	static cocos2d::Scene* scene();

	/**
	 * @fn		void nextScene()
	 * @brief	次のシーンへと切り替える
	 */
	void nextScene(Object* pSender);

private:
	/// 手札のタッチ処理
	void HandTouchWork();

	/// フィールドのタッチ処理
	void FieldTouchWork();

	/**
	 * @fn		void CPUWalk()
	 * @brief	CPUの仕事
	 */
	void CPUWalk();

	/// どれか出せるか
	bool IsAnySendCard();

	/// 勝敗判定
	int WhoIsWinner();
};


#endif /* PLAYSCENE_H_ */
