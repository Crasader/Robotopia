//Utils.h
//
//모든 클래스들에서 기본적으로 참조해야하는 값들과 함수들을 정의해둠.
//
//작성자 : 남현욱
//

#pragma once
#include "cocos2d.h"

//상수들
#define ABSTRACT virtual
#define OVERRIDE virtual
#define GRAVITY 980
#define TAG_GAME_LAYER 1

enum ObjectType
{
	OT_NONE,
	OT_PLAYER,
	OT_FLOOR,
	OT_BLOCK,
	OT_MISSILE,
	OT_LINEAR_MISSILE,
	OT_AIMING_MISSILE,
	OT_MONSTER,
	OT_RUSH_MONSTER,
	OT_VILLAGER,
	OT_GATEWAY,
};

enum EffectType
{
	ET_LINEAR_MISSILE_COLLISION,
	ET_AIMING_MISSILE_COLLISION,
	ET_PLAYER_FLOOR_COLLISION,
};

enum Direction
{
	DIR_NONE,
	DIR_LEFT = 1,
	DIR_UP = 2,
	DIR_RIGHT = 4,
	DIR_DOWN = 8,
};
typedef int Directions;

//유틸 함수 모음. 

class UtilFunctions
{
public:
	static cocos2d::Animation* createAnimation(const char* animationName, int startIdx, size_t frameNum, float delay);
};