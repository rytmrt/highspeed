/*
 * Field.cpp
 *
 *  Created on: 2013/12/03
 *      Author: s112179
 */

#include "Field.h"

USING_NS_CC;

//// 定数
// 手札一枚のサイズ
Point Field::SIZE = Point(64, 90);

/// コンストラクタ
Field::Field()
{
}

/// デストラクタ
Field::~Field()
{
}

/// 初期化
void Field::Initialize(cocos2d::Layer* layer,cocos2d::SpriteBatchNode* node)
{
	m_leftField.m_number = -1;
	m_leftField.m_suit = Card::UNKNOWN;
	// スプライトの生成
	m_leftField.m_pSprite = Sprite::createWithTexture(node->getTexture(), Rect(0, 0, 64, 90));
	// スプライトの移動
	m_leftField.m_pSprite->setPosition(Point(Utility::SCRN_WHIDTH / 2 - 48, Utility::SCRN_HEIGHT / 2));
	m_leftField.m_pSprite->setVisible(false);
	// AABB
	m_aabb[Utility::PLAYER_1].min = m_leftField.m_pSprite->getPosition() - SIZE / 2;
	m_aabb[Utility::PLAYER_1].max = m_leftField.m_pSprite->getPosition() + SIZE / 2;
	// レイヤーに追加する
	layer->addChild(m_leftField.m_pSprite,1);

	m_rightField.m_number = -1;
	m_rightField.m_suit = Card::UNKNOWN;
	// スプライトの生成
	m_rightField.m_pSprite = Sprite::createWithTexture(node->getTexture(), Rect(256, 0, 64, 90));
	// スプライトの移動
	m_rightField.m_pSprite->setPosition(Point(Utility::SCRN_WHIDTH / 2 + 48, Utility::SCRN_HEIGHT / 2));
	m_rightField.m_pSprite->setVisible(false);
	// AABB
	m_aabb[Utility::PLAYER_2].min = m_rightField.m_pSprite->getPosition() - SIZE / 2;
	m_aabb[Utility::PLAYER_2].max = m_rightField.m_pSprite->getPosition() + SIZE / 2;
	// レイヤーに追加する
	layer->addChild(m_rightField.m_pSprite,1);

}

/// 更新
void Field::Update()
{
	// テクスチャのレクト変更
	m_leftField.m_pSprite->setTextureRect(Rect(m_leftField.m_number * 64, m_leftField.m_suit * 90, 64, 90));
	m_rightField.m_pSprite->setTextureRect(Rect(m_rightField.m_number * 64, m_rightField.m_suit * 90, 64, 90));
}
	
/// ゲームをはじめる
void Field::StartGame(Card leftField , Card rightField)
{
	m_leftField.m_number = leftField.m_number;
	m_leftField.m_suit = leftField.m_suit;
	
	m_rightField.m_number = rightField.m_number;
	m_rightField.m_suit = rightField.m_suit;
}
	
/// 左のフィールドに置く
bool Field::PutLeftField(Card card)
{
	if( m_leftField.m_number == card.m_number || m_leftField.m_suit == card.m_suit )
	{
		m_leftField.m_number = card.m_number;
		m_leftField.m_suit = card.m_suit;
		return true;
	}

	return false;
}

/// 右のフィールドに置く
bool Field::PutRightField(Card card)
{
	if( m_rightField.m_number == card.m_number || m_rightField.m_suit == card.m_suit )
	{
		m_rightField.m_number = card.m_number;
		m_rightField.m_suit = card.m_suit;
		return true;
	}

	return false;
}

/// 左のフィールドに置く
void Field::SetLeftField(Card card)
{
	m_leftField.m_number = card.m_number;
	m_leftField.m_suit = card.m_suit;
}

/// 右のフィールドに置く
void Field::SetRightField(Card card)
{
	m_rightField.m_number = card.m_number;
	m_rightField.m_suit = card.m_suit;
}

/// 描画
void Field::Render()
{
	// ナンバーが異常じゃないか、スートがわからなくないなら
	// 左の場札
	if (m_leftField.m_number != -1 ||
			m_leftField.m_suit != Card::UNKNOWN)
	{
		m_leftField.m_pSprite->setVisible(true);
	}
	else
	{
		m_leftField.m_pSprite->setVisible(false);
	}

	// 右の場札
	if (m_rightField.m_number != -1 ||
			m_rightField.m_suit != Card::UNKNOWN)
	{
		m_rightField.m_pSprite->setVisible(true);
	}
	else
	{
		m_rightField.m_pSprite->setVisible(false);
	}
}
