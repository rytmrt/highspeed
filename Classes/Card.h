/*
 * Card.h
 *
 *  Created on: 2013/12/03
 *      Author: s112179
 */

#ifndef CARD_H_
#define CARD_H_

#include "Utility.h"

class Card
{
public:
	// マーク（スート）の列挙
	enum Suit
	{
		UNKNOWN = -1,
		CLUBS,
		SPADES,
		HEARTS,
		DIAMONDS,
	};

public:
	// マーク（スート）
	Suit m_suit;
	// 数字
	int m_number;
	// スプライト
	cocos2d::Sprite* m_pSprite;

public:
	/// コンストラクタ
	Card():m_suit(UNKNOWN),m_number(-1),m_pSprite(NULL){};
	/// デストラクタ
	~Card(){};
	/// 初期化
	void Initialize(){};
	/// 更新
	void Update(){};
};


#endif /* CARD_H_ */
