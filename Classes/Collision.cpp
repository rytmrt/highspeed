/*
 * Collision.cpp
 *
 *  Created on: 2014/01/14
 *      Author: s112205
 */

#include "Collision.h"

USING_NS_CC;

/// AABBとpointの衝突判定
bool AABB2Point(const Utility::AABB box, const cocos2d::Point point )
{
	//衝突判定
	if( box.min.x <= point.x &&  box.min.y <= point.y && 
		box.max.x >= point.x &&  box.max.y >= point.y )
	{
		return true;
	}
	return false;
}

/// AABBとAABBの衝突判定
bool AABB2AABB(const Utility::AABB boxA, const Utility::AABB boxB )
{
	//衝突判定
	if( boxA.min.x <= boxB.max.x &&  boxA.min.y <= boxB.max.y && 
		boxA.max.x >= boxB.min.x &&  boxA.max.y >= boxB.min.y
		)
	{
		return true;
	}
	return false;
}

