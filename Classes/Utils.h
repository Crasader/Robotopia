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
	OT_SENTINEL = -1,
	OT_NONE = 0,
	OT_PLAYER = 1,
	OT_FLOOR = 2,
	OT_BLOCK = 3,
	OT_MISSILE = 4,
	OT_LINEAR_MISSILE = 5,
	OT_AIMING_MISSILE = 6,
	OT_MONSTER = 7,
	OT_RUSH_MONSTER = 8,
	OT_VILLAGER = 9,
	OT_GATEWAY = 10,
	OT_NEW_LINEAR_MISSILE = 11,
	OT_MELEE_MISSILE = 12,
	OT_STEAM_PACK = 13,
	OT_TURRET = 14,
	OT_BAT_MONSTER = 15,
	OT_ITEM_LEG = 16,
	OT_TRAP = 17,
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


