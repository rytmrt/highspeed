/*
 * Input.cpp
 *
 *  Created on: 2014/01/14
 *      Author: s112179
 */

#include "Input.h"

USING_NS_CC;

/**
 * @fn		bool init()
 * @brief	初期化
 * @retval	true	初期化に成功
 * @retval	false	初期化に失敗
 */
bool Input::init()
{
	// 基底クラスの初期化
	if(!Layer::init())
	{
		return false;
	}

    
//	Director::getInstance()->getTouchDispatcher()->addStandardDelegate(this, 0);

	// マルチタッチできるよ
	setTouchEnabled(true);
	setTouchMode(Touch::DispatchMode::ALL_AT_ONCE);

	m_annyTouchFlag = false;

	m_pTouch = Point::ZERO;

	return true;
}

/**
 * @brief	更新
 */
void Input::update(float deltatime)
{
	m_pTouch = Point::ZERO;

	m_annyTouchFlag = false;
}

//// ------------------- シングル ---------------------------
/**
 * @brief	タッチ開始時のイベント
 */
bool Input::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	log("onTouchBegan");
	m_annyTouchFlag = true;
	m_pTouch = pTouch->getLocation();
	return true;
}

/**
 * @brief	タッチ移動時のイベント
 */
void Input::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	log("onTouchMoved");
	m_pTouch = pTouch->getLocation();
}

/**
 * @brief	タッチ終了時のイベント
 */
void Input::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	log("onTouchEnded");
	m_annyTouchFlag = false;
}

/**
 * @brief	タッチキャンセル時のイベント
 */
void Input::onTouchCancelled(Touch* pTouch, Event* pEvent)
{
}

//// ------------------- マルチ ---------------------------
/**
 * @brief	マルチタッチ開始時のイベント
 */
void Input::onTouchesBegan(Set* pTouch, Event* pEvent)
{
	//Log("onTouchesBegan");
	m_annyTouchFlag = true;
	for (SetIterator it = pTouch->begin(); it != pTouch->end(); ++it)
	{
		// キャストして保存
		Touch* touch = (Touch*)(*it);
		m_pTouch = touch->getLocation();

		if(m_pTouch.x > 0 || m_pTouch.y > 0)
		{
			return;
		}
	}
}

/**
 * @brief	マルチタッチ移動時のイベント
 */
void Input::onTouchesMoved(Set* pTouch, Event* pEvent)
{
	//Log("onTouchesMoved");
	for (SetIterator it = pTouch->begin(); it != pTouch->end(); ++it)
	{
		// キャストして保存
		Touch* touch = (Touch*)(*it);
		m_pTouch = touch->getLocation();

		if(m_pTouch.x > 0 || m_pTouch.y > 0)
		{
			return;
		}
	}
}

/**
 * @brief	マルチタッチ終了時のイベント
 */
void Input::onTouchesEnded(Set* pTouch, Event* pEvent)
{
}

/**
 * @brief	マルチタッチキャンセル時のイベント
 */
void Input::onTouchesCancelled(Set* pTouch, Event* pEvent)
{
}



