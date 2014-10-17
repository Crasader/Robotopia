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
		
		for (int y = module.height - 1; y >= 0; y--)
		{
			for (int x = 0; x < module.width; x++)
			{
				rawData = strtok(nullptr, tokenList);

				module.data.push_back(atoi(rawData));
			}
		}

		m_ModuleData[closedDirections][m_ModuleSize[closedDirections]++] = module;
	}

	return true;
}

DataManager::DataManager()
{
	for (int i = 0; i < 16; i++)
	{
		m_ModuleSize[i] = 0;
	}
	m_FloorStageData.clear();
}

DataManager::~DataManager()
{

}

bool DataManager::initFloorData()
{

	Data data = FileUtils::getInstance()->getDataFromFile(FLOOR_FILE_NAME);
	char* rawData = (char*)data.getBytes();
	const char* tokenList = " \r\n\0";
	int floorNum;
	int floorRawData[4][100][100] = {0,};
	int originX = 0, originY = 0;
	int endX = 0, endY = 0;

	rawData = strtok(rawData, tokenList);

	floorNum = atoi(rawData);

	for (int i = 1; i <= floorNum; i++)
	{
		std::map<int, StageData> dataVector;

		dataVector.clear();

		m_FloorStageData[i] = dataVector;
	}

	for (int i = 0; i < floorNum; i++)
	{
		int stageNum, stageRandNum;
		int maxStageWidth, maxStageHeight;

		originX = 0;
		originY = 0;
		endX = 0;
		endY = 0;
		
		rawData = strtok(nullptr, tokenList);
		stageNum = atoi(rawData);

		rawData = strtok(nullptr, tokenList);
		stageRandNum = atoi(rawData);

		rawData = strtok(nullptr, tokenList);
		maxStageWidth = atoi(rawData);

		rawData = strtok(nullptr, tokenList);
		maxStageHeight = atoi(rawData);

		if (stageRandNum != 0)
		{
			stageNum = stageNum + (rand() % (stageRandNum * 2)) - stageRandNum;
		}
		
		m_FloorData[i].stageNum = stageNum;

		for (int s = 1; s <= stageNum; s++)
		{
			int x, y, width, height;
			while (true)
			{
				bool passFlag = true;

				if (s == 1)
				{
					width = 1;
					height = 1;
				}
				else
				{
					width = 1 + rand() % (maxStageWidth);
					height = 1 + rand() % (maxStageHeight);
				}

				if (s == 1)
				{
					x = 0;
					y = 0;
				}
				else
				{
					int nearRoom = 1 + rand() % (s - 1);
					int dir;

					if (s > 2)
					{
						nearRoom = 2 + rand() % (s - 2);
						dir = rand() % 4;
					}
					else
					{
						dir = 2;
					}

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

				for (int p = 1; p < s && passFlag; p++)
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

			m_FloorStageData[i][s] = stage;
		}

		endX -= originX;
		endY -= originY;

		for (int s = 1; s <= stageNum; s++)
		{
			std::map<int, ObjectType> objectsData;

			m_FloorStageData[i][s].y -= originY;
			m_FloorStageData[i][s].x -= originX;
			m_FloorStageData[i][s].data = objectsData;

			for (int y = m_FloorStageData[i][s].y + 1; y <= m_FloorStageData[i][s].y + m_FloorStageData[i][s].height; y++)
			{
				for (int x = m_FloorStageData[i][s].x + 1; x <= m_FloorStageData[i][s].x + m_FloorStageData[i][s].width; x++)
				{
					floorRawData[i][y][x] = s;
				}
			}
		}
		for (int s = 1; s <= stageNum; s++)
		{
			m_FloorStageData[i][s].width *= MODULE_BASE_WIDTH;
			m_FloorStageData[i][s].height *= MODULE_BASE_HEIGHT;
			int width = m_FloorStageData[i][s].width;
			int height = m_FloorStageData[i][s].height;

			for (int y = m_FloorStageData[i][s].y + 1; y <= m_FloorStageData[i][s].y + m_FloorStageData[i][s].height / MODULE_BASE_HEIGHT; y++)
			{
				for (int x = m_FloorStageData[i][s].x + 1; x <= m_FloorStageData[i][s].x + m_FloorStageData[i][s].width / MODULE_BASE_WIDTH; x++)
				{
					int closedDirection = DIR_NONE;

					if (floorRawData[i][y - 1][x] != floorRawData[i][y][x])
					{
						closedDirection |= DIR_UP;
					}

					if (floorRawData[i][y + 1][x] != floorRawData[i][y][x])
					{
						closedDirection |= DIR_DOWN;
					}

					if (floorRawData[i][y][x - 1] != floorRawData[i][y][x])
					{
						closedDirection |= DIR_LEFT;
					}

					if (floorRawData[i][y][x + 1] != floorRawData[i][y][x])
					{
						closedDirection |= DIR_RIGHT;
					}

					int moduleIdx;

					if (i == floorNum - 1)
					{
						if (s == 1)
						{
							moduleIdx = 5;
						}
						else
						{
							moduleIdx = 6;
						}
					}
					else if (i == 0)
					{
						moduleIdx = 3;
					}
					else if (s == 1)
					{
						moduleIdx = 4;
					}
					else
					{
						if (closedDirection == 15)
						{
							moduleIdx = rand() % (m_ModuleSize[closedDirection] - 4);
						}
						else
						{
							moduleIdx = rand() % m_ModuleSize[closedDirection];
						}
					}

					int moduleWidth = m_ModuleData[closedDirection][moduleIdx].width;
					int moduleHeight = m_ModuleData[closedDirection][moduleIdx].height;


					int idxX = x - m_FloorStageData[i][s].x - 1;
					int idxY = y - m_FloorStageData[i][s].y - 1;

					for (int h = 0; h < moduleHeight; h++)
					{
						for (int w = 0; w < moduleWidth; w++)
						{
	
							int idx = ((m_FloorStageData[i][s].height / MODULE_BASE_HEIGHT - idxY - 1)*moduleHeight + h + 1)*(width + 2) + idxX*moduleWidth + w + 1;
							m_FloorStageData[i][s].data[idx] =
								(ObjectType)m_ModuleData[closedDirection][moduleIdx].data[h*moduleWidth + w];
						}
					}
				}
			}

			for (int y = 0; y <= m_FloorStageData[i][s].height + 1; y++)
			{
				for (int x = 0; x <= m_FloorStageData[i][s].width + 1; x++)
				{
					if (y == 0 || x == 0 ||
						y == m_FloorStageData[i][s].height + 1 ||
						x == m_FloorStageData[i][s].width + 1)
					{
						int idx = y*(width + 2) + x; 
						m_FloorStageData[i][s].data[idx] = (ObjectType)-1;
					}
				}
			}

			m_FloorStageData[i][s].x++;
			m_FloorStageData[i][s].y = endY + 1 - m_FloorStageData[i][s].y - m_FloorStageData[i][s].height/MODULE_BASE_HEIGHT;
			m_FloorStageData[i][s].width += 2;
			m_FloorStageData[i][s].height += 2;
		}

		
		for (int y = endY + 1; y >= 0; y--)
		{
			for (int x = 0; x <= endX + 1; x++)
			{
				if (y == 0 || x == 0 || x == endX + 1 || y == endY + 1)
				{
					m_FloorData[i].data.push_back(0);
				}
				else
				{
					m_FloorData[i].data.push_back(floorRawData[i][y][x]);
				}
			}
		}
		m_FloorData[i].width = endX + 2;
		m_FloorData[i].height = endY + 2;
	}

	return true;
}

bool DataManager::getFloorData(int currentFloor, FloorData* floorData, std::vector<StageData>* stageData)
{
	if (m_FloorData.find(currentFloor - 1) == m_FloorData.end())
	{
		return false;
	}

	*floorData = m_FloorData[currentFloor - 1];

	stageData->clear();

	for (int s = 0; s <= m_FloorData[currentFloor - 1].stageNum; s++)
	{
		stageData->push_back(m_FloorStageData[currentFloor - 1][s]);
	}
	

	return true;
}

bool DataManager::getShakeFloorData(int currentFloor, FloorData* floorData, std::vector<StageData>* stageData)
{
	if (m_FloorData.find(currentFloor) == m_FloorData.end())
	{
		return false;
	}

	int originX = 0, originY = 0;
	int endX = 0, endY = 0;
	int stageNum;
	int floorRawData[4][100][100] = { 0, };

	stageNum = m_FloorData[currentFloor - 1].stageNum;

	for (int s = 1; s <= stageNum; s++)
	{
		int x, y, width, height;
		while (true)
		{
			bool passFlag = true;

			width = m_FloorStageData[currentFloor - 1][s].width / MODULE_BASE_WIDTH;
			height = m_FloorStageData[currentFloor - 1][s].height / MODULE_BASE_HEIGHT;

			if (s == 1)
			{
				x = 0;
				y = 0;
			}
			else
			{
				int nearRoom = 1 + rand() % (s - 1);
				int dir;

				if (s > 2)
				{
					nearRoom = 2 + rand() % (s - 2);
					dir = rand() % 4;
				}
				else
				{
					dir = 2;
				}

				x = m_FloorStageData[currentFloor - 1][nearRoom].x;
				y = m_FloorStageData[currentFloor - 1][nearRoom].y;

				switch (dir)
				{
				case 0: //왼쪽
					x -= width;
					y += (rand() % height) - height + 1;
					break;
				case 1: //위
					x += (rand() % width) - width + 1;
					y -= height;
					break;
				case 2: //오른쪽
					x += m_FloorStageData[currentFloor - 1][nearRoom].width / MODULE_BASE_WIDTH;
					y += (rand() % height) - height + 1;
					break;
				case 3: //아래
					x += (rand() % width) - width + 1;
					y += m_FloorStageData[currentFloor - 1][nearRoom].height / MODULE_BASE_HEIGHT;
					break;
				}
			}

			for (int p = 1; p < s && passFlag; p++)
			{

				int enemyX = m_FloorStageData[currentFloor - 1][p].x;
				int enemyY = m_FloorStageData[currentFloor - 1][p].y;
				int enemyWidth = m_FloorStageData[currentFloor - 1][p].width / MODULE_BASE_WIDTH;
				int enemyHeight = m_FloorStageData[currentFloor - 1][p].height / MODULE_BASE_HEIGHT;

				if (!(x + width <= enemyX || x >= enemyX + enemyWidth ||
					y + height <= enemyY || y >= enemyY + enemyHeight))
				{
					passFlag = false;
					break;
				}
			}

			if (passFlag == true)
				break;
		}

		if (x < originX) originX = x;
		if (y < originY) originY = y;
		if (x + width > endX) endX = x + width;
		if (y + height > endY) endY = y + height;

		m_FloorStageData[currentFloor - 1][s].x = x;
		m_FloorStageData[currentFloor - 1][s].y = y;
		
	}

	endX -= originX;
	endY -= originY;

	for (int s = 1; s <= stageNum; s++)
	{
		m_FloorStageData[currentFloor - 1][s].y -= originY;
		m_FloorStageData[currentFloor - 1][s].x -= originX;

		for (int y = m_FloorStageData[currentFloor - 1][s].y + 1; y <= m_FloorStageData[currentFloor - 1][s].y + m_FloorStageData[currentFloor - 1][s].height / MODULE_BASE_HEIGHT; y++)
		{
			for (int x = m_FloorStageData[currentFloor - 1][s].x + 1; x <= m_FloorStageData[currentFloor - 1][s].x + m_FloorStageData[currentFloor - 1][s].width / MODULE_BASE_WIDTH; x++)
			{
				floorRawData[currentFloor - 1][y][x] = s;
			}
		}
		m_FloorStageData[currentFloor - 1][s].x++;
		m_FloorStageData[currentFloor - 1][s].y = endY + 1 - m_FloorStageData[currentFloor - 1][s].y - m_FloorStageData[currentFloor - 1][s].height / MODULE_BASE_HEIGHT;
	}

	m_FloorData[currentFloor - 1].data.clear();

	for (int y = endY + 1; y >= 0; y--)
	{
		for (int x = 0; x <= endX + 1; x++)
		{
			if (y == 0 || x == 0 || x == endX + 1 || y == endY + 1)
			{
				m_FloorData[currentFloor - 1].data.push_back(0);
			}
			else
			{
				m_FloorData[currentFloor - 1].data.push_back(floorRawData[currentFloor - 1][y][x]);
			}
		}
	}
	m_FloorData[currentFloor - 1].width = endX + 2;
	m_FloorData[currentFloor - 1].height = endY + 2;

	return true;
}
