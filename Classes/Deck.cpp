// デッキクラス

#include "Deck.h"
#include <stdlib.h>
#include <iostream>

using namespace std;
USING_NS_CC;

//----------public----------

//コンストラクタ
Deck::Deck()
{
}

//デストラクタ
Deck::~Deck()
{
	for( int i = 0 ; i < DECK_MAX_CARD ; ++i )
	{
		delete m_deckSrc[i];
		m_deckSrc[i] = NULL;
	}
}

//初期化
void Deck::Initialize(cocos2d::Layer* layer,cocos2d::SpriteBatchNode* node, Utility::PLAYER player)
{
	//init
	m_player = player;
	for( int i = 0 ; i < DECK_MAX_CARD ; ++i )
	{
		m_deckSrc[i] = new Card();

		m_deckSrc[i]->m_number = i % 10;
		m_deckSrc[i]->m_suit = static_cast<Card::Suit>(i / 10);
		m_deckSrc[i]->m_pSprite = Sprite::createWithTexture(node->getTexture(), Rect(0, 360, 64, 90));
		// スプライトのサイズ変更
		m_deckSrc[i]->m_pSprite->setScale(0.75f);
		if (m_player == Utility::PLAYER_1)
		{
			// スプライトの移動
			m_deckSrc[i]->m_pSprite->setPosition(Point(32 - i / 10, 116 + i / 10));
		}
		else
		{
			// スプライトの移動
			m_deckSrc[i]->m_pSprite->setPosition(Point(Utility::SCRN_WHIDTH - (32 - i / 10),
                                                       Utility::SCRN_HEIGHT - 116 - i / 10));
		}
		// レイヤーに追加する
		layer->addChild(m_deckSrc[i]->m_pSprite,2);

		m_deck[i] = m_deckSrc[i];
	}

	m_num = DECK_MAX_CARD;

	//shuffle
	Shuffle();

}

//更新
void Deck::Update()
{
}

//ドロー(カードを引く)
Card Deck::Draw()
{
	if (m_num <= 0) return Card();

	Card data = *m_deck[m_num-1];
	m_deck[m_num-1] = NULL;
	--m_num;

	return data;
}

//描画
void Deck::Render()
{
	for( int i = 0 ; i < DECK_MAX_CARD ; ++i )
	{
		if (i < m_num)
		{
			m_deckSrc[i]->m_pSprite->setVisible(true);
		}
		else
		{
			m_deckSrc[i]->m_pSprite->setVisible(false);
		}
	}
}



//----------private----------

//置き換え
void Deck::Swap(Card* a, Card* b)
{
	Card temp;

	temp.m_number = a->m_number;
	a->m_number = b->m_number;
	b->m_number = temp.m_number;

	temp.m_suit = a->m_suit;
	a->m_suit = b->m_suit;
	b->m_suit = temp.m_suit;

}

//シャッフル
void Deck::Shuffle()
{
	int randA = 0 ,randB = 0;
	for(int i = 0 ; i < 100 ; ++i)
	{
		randA = rand() % DECK_MAX_CARD;
		randB = rand() % DECK_MAX_CARD;
		Swap(m_deck[randA],m_deck[randB]);
	}
}
