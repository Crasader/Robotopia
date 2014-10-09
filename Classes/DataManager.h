#pragma once
#include "cocos2d.h"
#include "Utils.h"
#define MODULES_FILE_NAME "Data\\Stage\\moduleList.mld"

struct StageModuleData
{
	int width, height;
	std::vector<int> data;
};

struct StageData
{
	int width, height;
	std::vector<int> data;
};

struct FloorData
{
	int width, height;
	std::vector<int> data;
};

class DataManager
{
public:
	bool init();
	bool initModuleData();
	DataManager();
	~DataManager();

private:	


};