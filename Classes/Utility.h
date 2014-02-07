/*
 * Utility.h
 *
 *  Created on: 2013/12/24
 *      Author: s112179
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "cocos2d.h"

namespace Utility {

// --------- 定数 ---------
// 画面サイズ
static const int SCRN_WHIDTH = 320;
static const int SCRN_HEIGHT = 480;


// --------- 列挙 ---------
// プレイヤー
enum PLAYER
{
	PLAYER_1,
	PLAYER_2,

	PLAYER_NUM
};

// --------- 構造体 ---------
// AABB
struct AABB
{
	cocos2d::Point min;
	cocos2d::Point max;
};
    
}
#endif /* UTILITY_H_ */
