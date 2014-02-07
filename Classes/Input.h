/*
 * Input.h
 *
 *  Created on: 2014/01/14
 *      Author: s112179
 */

#ifndef INPUT_H_
#define INPUT_H_

#include "cocos2d.h"

class Input : public cocos2d::Layer
{
private:

	// どこかタッチしたか
	bool m_annyTouchFlag;
	// マルチタッチ座標
	cocos2d::Point m_pTouch;

private:
	Input(){}
	Input(const Input&);
	Input& operator =(const Input&);

public:
	static Input* GetInstance()
	{
		static Input instance;
		return &instance;
	}

public:
	/**
	 * @fn		static PlayScene* create()
	 * @brief	プレイシーンの生成
	 * @return	プレイシーンのアドレス
	 */
	CREATE_FUNC(Input);

	/**
	 * @fn		bool init()
	 * @brief	初期化
	 * @retval	true	初期化に成功
	 * @retval	false	初期化に失敗
	 */
	bool init();

	/**
	 * @brief	更新
	 */
	void update(float deltatime);
	/// どこかタッチしたかを取得
	bool GetAnnyTouchFlag() {return m_annyTouchFlag;}
	/// タッチ座標
	cocos2d::Point GetTouch() {return m_pTouch;}

public:
	//// ----------------- シングル ---------------------
	/**
	 * @brief	タッチ開始時のイベント
	 */
	bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	/**
	 * @brief	タッチ移動時のイベント
	 */
	void onTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	/**
	 * @brief	タッチ終了時のイベント
	 */
	void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	/**
	 * @brief	タッチキャンセル時のイベント
	 */
	void onTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);

	//// ------------------- マルチ ---------------------------
	/**
	 * @brief	マルチタッチ開始時のイベント
	 */
	void onTouchesBegan(cocos2d::Set* pTouch, cocos2d::Event* pEvent);

	/**
	 * @brief	マルチタッチ移動時のイベント
	 */
	void onTouchesMoved(cocos2d::Set* pTouch, cocos2d::Event* pEvent);

	/**
	 * @brief	マルチタッチ終了時のイベント
	 */
	void onTouchesEnded(cocos2d::Set* pTouch, cocos2d::Event* pEvent);

	/**
	 * @brief	マルチタッチキャンセル時のイベント
	 */
	void onTouchesCancelled(cocos2d::Set* pTouch, cocos2d::Event* pEvent);
};

#endif /* INPUT_H_ */
