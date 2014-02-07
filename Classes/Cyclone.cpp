/**
 * @file	Cyclone.cpp
 * @brief	サイクロンのエフェクト
 * @author	Shosuke Mimura
 */

#include "Cyclone.h"

USING_NS_CC;

namespace
{
	/// ノードタグ
	enum NodeTag
	{
		NODETAG_BATCHNODE,	/// バッチノード
	};

	/// サイクロンに使うリソースのパス
	const char* RESOURCE_PATH = "";

	/// フェードアウトの持続時間
	const float FADEOUT_DURATION = 0.2f;

	/// 回転の持続時間
	const float ROTATE_DURATION = 0.5f;

	/// 回転の量
	const float ROTATE_QUANTITY = 360.0f;

	/// 比率の持続時間
	const float SCALE_DURATION = ROTATE_DURATION;

	/// 比率の量
	const float SCALE_QUANTITY = 0.5f;
}

/**
 * @brief	サイクロンのコールバック
 * @param	sender	送信者
 */
void Cyclone::callBackCyclone(Node* sender)
{
	Sprite* sprite = static_cast<Sprite*>(sender);
	this->removeChild(sprite, true);
}

/**
 * @brief	サイクロンの生成
 * @return	生成されたサイクロン
 */
Sprite* Cyclone::createCyclone()
{
	SpriteBatchNode* batchnode = static_cast<SpriteBatchNode*>(this->getChildByTag(NODETAG_BATCHNODE));
	Sprite* sprite = Sprite::createWithTexture(batchnode->getTexture());
	sprite->setScale(0.0f);

	RotateBy* rotate = RotateBy::create(ROTATE_DURATION, ROTATE_QUANTITY);
	ScaleTo* scale = ScaleTo::create(SCALE_DURATION, SCALE_QUANTITY);
	FadeOut* fadeout = FadeOut::create(FADEOUT_DURATION);
	CallFuncN* actionDone = CallFuncN::create(this, callfuncN_selector(Cyclone::callBackCyclone));

	Spawn* spawn = Spawn::create(rotate, scale, NULL);
	Sequence* sequence = Sequence::create(spawn, fadeout, actionDone, NULL);

	sprite->runAction(sequence);

	return sprite;
}

/**
 * @brief	サイクロンバッチノードの初期化
 */
void Cyclone::initCycloneBatchNode()
{
	SpriteBatchNode* batchnode = SpriteBatchNode::create(RESOURCE_PATH);
	batchnode->setTag(NODETAG_BATCHNODE);
	this->addChild(batchnode);
}

/**
 * @brief	サイクロンの初期化
 * @retval	true	初期化に成功
 * @retval	false	初期化に失敗
 */
bool Cyclone::init()
{
	if(!Base::init())
	{
		return false;
	}

	// バッチノードの初期化
	this->initCycloneBatchNode();

	return true;
}

/**
 * @brief	追加
 * @param	[in]	position	座標
 */
void Cyclone::add(const Point& position)
{
	SpriteBatchNode* batchnode = static_cast<SpriteBatchNode*>(this->getChildByTag(NODETAG_BATCHNODE));
	Sprite* cyclone = this->createCyclone();
	batchnode->addChild(cyclone);
}


