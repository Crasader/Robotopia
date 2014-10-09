#include "DataManager.h"

USING_NS_CC;

bool DataManager::init()
{
	initModuleData();
	initFloorData();
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
	m_ModuleData.clear();
	for (int i = 0; i < 15; i++)
	{
		std::vector<StageModuleData> moduleDataVector;

		moduleDataVector.clear();

		m_ModuleData[i] = moduleDataVector;
	}
	m_FloorStageData.clear();
}

DataManager::~DataManager()
{

}

bool DataManager::initFloorData()
{
	unsigned long fileSize;
	Data data = FileUtils::getInstance()->getDataFromFile(FLOOR_FILE_NAME);
	char* rawData = (char*)data.getBytes();
	const char* tokenList = " \r\n\0";
	int floorNum;
	int floorRawData[4][100][100] = {0,};
	int originX = 0, originY = 0;
	int endX = 0, endY = 0;

	CCLOG("%s", rawData);


	rawData = strtok(rawData, tokenList);

	floorNum = atoi(rawData);

	for (int i = 0; i < floorNum; i++)
	{
		std::vector<StageData> dataVector;

		dataVector.clear();

		m_FloorStageData[i] = dataVector;
	}

	for (int i = 0; i < floorNum; i++)
	{
		int stageNum, stageRandNum;
		int maxStageWidth, maxStageHeight;
		
		rawData = strtok(nullptr, tokenList);
		stageNum = atoi(rawData);

		rawData = strtok(nullptr, tokenList);
		stageRandNum = atoi(rawData);

		rawData = strtok(nullptr, tokenList);
		maxStageWidth = atoi(rawData);

		rawData = strtok(nullptr, tokenList);
		maxStageHeight = atoi(rawData);

		stageNum = stageNum + (rand() % (stageRandNum * 2)) - stageRandNum;

		for (int s = 0; s < stageNum; s++)
		{
			int x, y, width, height;
			while (true)
			{
				bool passFlag = true;

				width = 1 + rand() % maxStageWidth;
				height = 1 + rand() % maxStageHeight;

				if (s == 0)
				{
					x = 0;
					y = 0;
				}
				else
				{
					int nearRoom = rand() % s;
					int dir = rand() % 4;

					x = m_FloorStageData[i][nearRoom].x;
					y = m_FloorStageData[i][nearRoom].y;

					switch (dir)
					{
					case 0: //왼쪽
						x -= width;
						y += (rand() % height) - height + 1;
						break;
					case 1: //위
						x += (rand() %width ) - width + 1;
						y -= height;
						break;
					case 2: //오른쪽
						x += m_FloorStageData[i][nearRoom].width;
						y += (rand() % height) - height + 1;
						break;
					case 3: //아래
						x += (rand() % width) - width + 1;
						y += m_FloorStageData[i][nearRoom].height;
						break;

					}
				}

				for (int p = 0; p < s; p++)
				{
					int enemyX = m_FloorStageData[i][p].x;
					int enemyY = m_FloorStageData[i][p].y;
					int enemyWidth = m_FloorStageData[i][p].width;
					int enemyHeight = m_FloorStageData[i][p].height;

					if (!(x + width<=enemyX || x>=enemyX + enemyWidth ||
						y + height<=enemyY || y>=enemyY + enemyHeight))
					{
						passFlag = false;
						break;
					}
				}

				if (passFlag == true)
					break;
			}

			StageData stage;

			stage.x = x;
			stage.y = y;
			stage.width = width;
			stage.height = height;

			if (x < originX) originX = x;
			if (y < originY) originY = y;
			if (x + width > endX) endX = x + width;
			if (y + height > endY) endY = y + height;

			m_FloorStageData[i].push_back(stage);
		}

		endX -= originX;
		endY -= originY;

		for (int s = 0; s < stageNum; s++)
		{
			m_FloorStageData[i][s].y -= originY;
			m_FloorStageData[i][s].x -= originX;
			for (int j = m_FloorStageData[i][s].y; j < m_FloorStageData[i][s].y + m_FloorStageData[i][s].height; j++)
			{
				for (int k = m_FloorStageData[i][s].x; k < m_FloorStageData[i][s].x + m_FloorStageData[i][s].width; k++)
				{
					floorRawData[i][j][k] = s + 1;
				}
			}
		}

		for (int y = 0; y < endY; y++)
		{
			for (int x = 0; x < endX; x++)
			{
				m_FloorData[i].data.push_back(floorRawData[i][y][x]);
			}
		}
	}
	return true;
}
