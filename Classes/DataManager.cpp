#include "DataManager.h"

USING_NS_CC;

bool DataManager::init()
{

	return true;
}

bool DataManager::initModuleData()
{
	CCLOG("%s",FileUtils::getInstance()->getSearchPaths()[0].c_str());
	return true;
}

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}
