/*
 * Hand.h
 *
 *  Created on: 2013/12/03
 *      Author: s112179
 */

#ifndef HAND_H_
#define HAND_H_

#include "Card.h"

class Hand
{
public:
	// 手札1枚のサイズ
	static cocos2d::Point SIZE;

private:

	/// プレイヤー
	Utility::PLAYER m_player;

	/// 手札３枚分
	Card m_hand[3];

	/// カードおけるよフラグ
	bool m_putFlag[3];

	/// 選択されている場所
	int m_selectLocation;

	// 選択カーソルのスプライト
	cocos2d::Sprite* m_pCursorSprite;

	/// 速度
	cocos2d::Point m_vel[3];

	/// カードを持っているフラグ
	bool m_pickFlag;

	// AABB
	Utility::AABB m_aabb[3];

public:
	/// コンストラクタ
	Hand();
	/// デストラクタ
	~Hand();
	/// 初期化
	void Initialize(cocos2d::Layer* layer,cocos2d::SpriteBatchNode* node, Utility::PLAYER player);
	/// 更新
	void Update();

	/// 描画
	void Render();

	/// カードをセット
	void SetCard(const Card& card, int location) {m_hand[location].m_number = card.m_number; m_hand[location].m_suit = card.m_suit; m_putFlag[location] = false;}
	/// カードおける？
	bool IsPutCard(int location) {return m_putFlag[location];}
	/// カード選択
	void SelectCard(int location) {m_selectLocation = location;}
	/// 選択されたカードの場所取得
	int GetSelectLocation() {return m_selectLocation;}
	/// カードを取得
	Card GetCard(int location) {return m_hand[location];}
	/// 選択したカードを取得
	Card GetCard() {return m_hand[m_selectLocation];}
	/// カードを出す
	Card SendCard(int location) {
		m_putFlag[location] = true;
		Card card = m_hand[location];
		m_hand[location].m_number = -1;
		m_hand[location].m_suit = Card::UNKNOWN;
		return card;
	}
	/// カードを出す
	Card SendCard() {
		m_putFlag[m_selectLocation] = true;
		Card card = m_hand[m_selectLocation];
		m_hand[m_selectLocation].m_number = -1;
		m_hand[m_selectLocation].m_suit = Card::UNKNOWN;
		return card;
	}
	/// AABB取得
	Utility::AABB GetAABB(int location) {return m_aabb[location];}
};


#endif /* HAND_H_ */
