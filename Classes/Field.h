/*
 * Field.h
 *
 *  Created on: 2013/12/03
 *      Author: s112179
 */

#ifndef FIELD_H_
#define FIELD_H_

#include "Card.h"

class Field
{
public:
// 手札1枚のサイズ
static cocos2d::Point SIZE;

private:
	
	/// カードを置くフィールド
	Card m_leftField;
	Card m_rightField;

	/// AABB
	Utility::AABB m_aabb[Utility::PLAYER_NUM];

public:
	/// コンストラクタ
	Field();
	/// デストラクタ
	~Field();
	/// 初期化
	void Initialize(cocos2d::Layer* layer,cocos2d::SpriteBatchNode* node);
	/// 更新
	void Update();
	
	/// ゲームをはじめる
	void StartGame(Card leftField , Card rightField);
	
	/// 左のフィールドに置く
	bool PutLeftField(Card card);

	/// 右のフィールドに置く
	bool PutRightField(Card card);
	
	/// 左のフィールドに置く
	void SetLeftField(Card card);

	/// 右のフィールドに置く
	void SetRightField(Card card);

	/// 左のフィールドを取得
	Card GetLeftField() { return m_leftField; }

	/// 右のフィールドを取得
	Card GetRightField() { return m_rightField; }

	/// 描画
	void Render();

	// AABB取得
    Utility::AABB GetAABB(int location) {return m_aabb[location];}
};


#endif /* FIELD_H_ */
