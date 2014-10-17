#pragma once
#include "cocos2d.h"
#include "Utils.h"
#define MODULES_FILE_NAME "Data\\Stage\\moduleList.mld"
#define FLOOR_FILE_NAME "Data\\Stage\\floorData.fdd"
#define MODULE_BASE_WIDTH 20
#define MODULE_BASE_HEIGHT 20


struct StageModuleData
{
	int width, height;
	std::vector<int> data;
};

struct StageData
{
	int x, y;
	int width, height;
	std::map<int, ObjectType> data;

	StageData(){}
	~StageData(){}
};

struct FloorData
{
	int width, height;
	int stageNum;
	std::vector<int> data;

	FloorData(){}
	~FloorData(){}
};

class DataManager
{
public:
	bool init();
	bool initModuleData();
	bool initFloorData();
	bool getFloorData(int currentFloor, FloorData* floorData, std::vector<StageData>* stageData);
	bool getShakeFloorData(int currentFloor, FloorData* floorData, std::vector<StageData>* stageData);
	DataManager();
	~DataManager();

private:	
	StageModuleData m_ModuleData[16][200];
	int	m_ModuleSize[16];
	//std::map < int, std::vector<StageModuleData>> m_ModuleData;
	std::map < int, std::map<int, StageData>> m_FloorStageData;
	std::map <int, FloorData> m_FloorData;

};