/**
 * @file	Cyclone.h
 * @brief	サイクロンのエフェクト
 * @author	Shosuke Mimura
 */

#ifndef CYCLONE_H_
#define CYCLONE_H_

#include "cocos2d.h"

class Cyclone : public cocos2d::Layer
{
private:

	/// 基底クラス
	typedef	cocos2d::Layer Base;

private:

	/**
	 * @brief	サイクロンのコールバック
	 * @param	sender	送信者
	 */
	void callBackCyclone(cocos2d::Node* sender);

	/**
	 * @brief	サイクロンの生成
	 * @return	生成されたサイクロン
	 */
	cocos2d::Sprite* createCyclone();

	/**
	 * @brief	サイクロンバッチノードの初期化
	 */
	void initCycloneBatchNode();

public:

	/**
	 * @brief	サイクロンの生成
	 * @return	生成されたインスタンス
	 */
	CREATE_FUNC(Cyclone);

	/**
	 * @brief	サイクロンの初期化
	 * @retval	true	初期化に成功
	 * @retval	false	初期化に失敗
	 */
	bool init();

	/**
	 * @brief	追加
	 * @param	[in]	position	座標
	 */
	void add(const cocos2d::Point& position);
};

#endif /* CYCLONE_H_ */
