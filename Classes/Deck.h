// デッキクラス

#pragma once

#include "Card.h"

static const int DECK_MAX_CARD = 40;

class Deck
{
private:
	
	// プレイヤー
    Utility::PLAYER m_player;

	//カードの束（デッキ）
	Card* m_deck[DECK_MAX_CARD];

	//元のカードの束（デッキ）
	Card* m_deckSrc[DECK_MAX_CARD];

	//カードの残数
	int m_num;

private:
	
	//置き換え
	void Swap(Card* a, Card* b);

	//シャッフル
	void Shuffle();

public:
	//コンストラクタ
	Deck();

	//デストラクタ
	~Deck();
	
	//初期化
	void Initialize(cocos2d::Layer* layer,cocos2d::SpriteBatchNode* node, Utility::PLAYER player);

	//更新
	void Update();

	//ドロー(カードを引く)
	Card Draw();

	//描画
	void Render();

	//カードの残数
	int GetNum() {return m_num; }

};

