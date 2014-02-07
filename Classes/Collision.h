/*
 * Collision.h
 *
 *  Created on: 2014/01/14
 *      Author: s112205
 */

#ifndef COLLISION_H_
#define COLLISION_H_

#include "Utility.h"

/// AABBとpointの衝突判定
bool AABB2Point(const Utility::AABB box, const cocos2d::Point point );

/// AABBとAABBの衝突判定
bool AABB2AABB(const Utility::AABB boxA, const Utility::AABB boxB );


#endif /* COLLISION_H_ */
