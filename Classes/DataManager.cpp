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
	unsigned char* rawData = data.getBytes();

	delete rawData;
	return true;
}

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}
