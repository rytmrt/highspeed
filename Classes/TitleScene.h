/*
 * TitleScene.h
 *
 *  Created on: 2013/12/17
 *      Author: s112179
 */

#ifndef TITLESCENE_H_
#define TITLESCENE_H_

#include "cocos2d.h"

/**
 * @class 	TitleScene
 * @brief	タイトルシーンクラス
 */
class TitleScene : public cocos2d::Layer
{
	//////////////////
	// private value
	//////////////////
private:
	cocos2d::Sprite* pSprite;
	cocos2d::Sprite* m_pTitle;

	int m_count;
	float m_textPosY;

	//////////////////
	// private method
	//////////////////
private:

	/**
	 * @fn		initTitleScene()
	 * @brief	タイトルシーンの初期化
	 */
	void initTitleScene();

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
	 * @fn		static TitleScene* create()
	 * @brief	タイトルシーンの生成
	 * @return	タイトルシーンのアドレス
	 */
	CREATE_FUNC(TitleScene);

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
	 * @brief	タイトルシーンを追加したシーンの生成
	 * @return	シーンのアドレス
	 */
	static cocos2d::Scene* scene();

	/**
	 * @fn		void nextScene()
	 * @brief	次のシーンへと切り替える
	 */
	void nextScene(Object* pSender);

	// 終了処理のコールバック関数
	void menuCloseCallback(Object* pSender);
};


#endif /* TITLESCENE_H_ */
