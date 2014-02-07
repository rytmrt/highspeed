/*
 * Hand.cpp
 *
 *  Created on: 2013/12/03
 *      Author: s112179
 */

#include "Hand.h"
#include "Collision.h"
#include "Input.h"


USING_NS_CC;

//// 定数
// 手札一枚のサイズ
Point Hand::SIZE = Point(64, 90);

/// コンストラクタ
Hand::Hand()
{
}

/// デストラクタ
Hand::~Hand()
{
}

/// 初期化
void Hand::Initialize(cocos2d::Layer* layer,cocos2d::SpriteBatchNode* node, Utility::PLAYER player)
{
	m_player = player;
	for(int i = 0 ; i < 3 ; ++i)
	{
		m_hand[i].m_number = -1;
		m_hand[i].m_suit = Card::UNKNOWN;
		m_putFlag[i] = true;
		m_vel[i] = Point(0.0f, 0.0f);
		// スプライト生成
		m_hand[i].m_pSprite = Sprite::createWithTexture(node->getTexture(), Rect(0, 0, SIZE.x, SIZE.y));
		if (m_player == Utility::PLAYER_1)
		{
			// スプライトの移動
			m_hand[i].m_pSprite->setPosition(Point(i * (64 + 16) + 96,64));
		}
		else
		{
			// スプライトの移動
			m_hand[i].m_pSprite->setPosition(Point(Utility::SCRN_WHIDTH - (i * (64 + 16) + 96),
                                                   Utility::SCRN_HEIGHT - 64));
		}
		m_hand[i].m_pSprite->setVisible(false);
		// レイヤーに追加する
		layer->addChild(m_hand[i].m_pSprite,5);
		// AABB
		m_aabb[i].min = m_hand[i].m_pSprite->getPosition() - SIZE / 2;
		m_aabb[i].max = m_hand[i].m_pSprite->getPosition() + SIZE / 2;
	}
	// 最初は何も選択してない
	m_selectLocation = -1;
	// 選択カーソルのスプライト
	m_pCursorSprite = Sprite::createWithTexture(node->getTexture(), Rect(64, 360, SIZE.x, SIZE.y));
	m_pCursorSprite->setVisible(false);
	layer->addChild(m_pCursorSprite, 6);
	m_pickFlag = false;
}

/// 更新
void Hand::Update()
{
	for(int i = 0 ; i < 3 ; ++i)
	{
//		int ID = -1;
//		// カードがあるところをドラッグで持てる
//		if (!m_pickFlag)
//		{
//			if (!m_putFlag[i])
//			{
//				AABB aabb;
//				aabb.min = m_hand[i].m_pSprite->getPosition() - m_hand[i].m_pSprite->getTextureRect().size / 2.0f;
//				aabb.max = m_hand[i].m_pSprite->getPosition() + m_hand[i].m_pSprite->getTextureRect().size / 2.0f;
////				for (int k = 0; k < 10; ++k)
////				{
//					// タッチしてたら
//					if (AABB2Point(aabb, Input::GetInstance()->GetTouch()))
//					{
//						m_hand[i].m_pSprite->setPosition(Input::GetInstance()->GetTouch());
//						//m_vel[i] = Input::GetInstance()->GetTouch(0).getDelta();
//					}
////				}
//			}
//		}
//		if (!Input::GetInstance()->GetAnnyTouchFlag())
//		{
//			m_hand[i].m_pSprite->setPosition(m_hand[i].m_pSprite->getPosition() + m_vel[i]);
//			m_vel[i] = Point(m_vel[i].x * 0.9f, m_vel[i].y * 0.9f);
//		}


		// テクスチャのレクト変更
		m_hand[i].m_pSprite->setTextureRect(Rect(m_hand[i].m_number * 64, m_hand[i].m_suit * 90, 64, 90));
		if (m_player == Utility::PLAYER_2)
		{
			// テクスチャ回転
			m_hand[i].m_pSprite->setRotation(180.0f);
		}
	}
	// カーソルの表示場所設定
	if (m_selectLocation >= 0)
	{
		if (m_player == Utility::PLAYER_1)
        {
            m_pCursorSprite->setPosition(Point(m_selectLocation * (64 + 16) + 96,64));
        }
		else
        {
            m_pCursorSprite->setPosition(Point(Utility::SCRN_WHIDTH - (m_selectLocation * (64 + 16) + 96),
                                               Utility::SCRN_HEIGHT - 64));
        }
	}

	// カーソルアニメーション
	m_pCursorSprite->setScale(1.0f);
}

/// 描画
void Hand::Render()
{
	for(int i = 0 ; i < 3 ; ++i)
	{
		// ナンバーが異常じゃないか、スートがわからなくないなら
		if (m_hand[i].m_number != -1 ||
			m_hand[i].m_suit != Card::UNKNOWN)
		{
			m_hand[i].m_pSprite->setVisible(true);
		}
		else
		{
			m_hand[i].m_pSprite->setVisible(false);
		}
	}

	// どこか選択されていたら描画
	if (m_selectLocation >= 0)
	{
		m_pCursorSprite->setVisible(true);
	}
	else
	{
		m_pCursorSprite->setVisible(false);
	}
}



