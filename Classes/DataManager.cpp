#include "DataManager.h"

USING_NS_CC;

bool DataManager::init()
{
	initModuleData();
	return true;
}

bool DataManager::initModuleData()
{
	unsigned long fileSize;
	Data data = FileUtils::getInstance()->getDataFromFile(MODULES_FILE_NAME);
	char* rawData = (char*)data.getBytes();
	const char* tokenList = " \r\n\0";
	int tokenNum;

	rawData = strtok(rawData, tokenList);

	tokenNum = atoi(rawData);

	for (int i = 0; i < tokenNum; i++)
	{
		StageModuleData module;
		Directions closedDirections;
		rawData = strtok(nullptr, tokenList);
		closedDirections = atoi(rawData);
		rawData = strtok(nullptr, tokenList);
		module.width = atoi(rawData);
		rawData =strtok(nullptr, tokenList);
		module.height = atoi(rawData);
		
		for (int y = 0; y < module.height; y++)
		{
			for (int x = 0; x < module.width; x++)
			{
				rawData = strtok(nullptr, tokenList);

				module.data.push_back(atoi(rawData));
			}
		}

		m_ModuleData[closedDirections].push_back(module);
	}

	return true;
}

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}
