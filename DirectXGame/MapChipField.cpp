#include "MapChipField.h"
#include <map>
#include <fstream>
#include <sstream>
#include <cassert>

namespace {
	std::map<std::string, MapChipType> mapChipTable = {
		{"0", MapChipType::kBlank},
		{"1", MapChipType::kBlock},
	};
}

MapChipField::MapChipField()
{

}

MapChipField::~MapChipField()
{

}

void MapChipField::Initialize()
{

}

void MapChipField::ResetMapChipData()
{
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumBlockVertical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data)
	{
		mapChipDataLine.resize(kNumBlockHorizontal);
	}
}

void MapChipField::LoadMapChipCsv(const std::string& filePath)
{
	//Open file
	ResetMapChipData();
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	//Mapchip CSV
	std::stringstream mapChipCsv;
	//Copy the contents of the CSV file into the stringstream
	mapChipCsv << file.rdbuf();
	//Close the file
	file.close();

	for (uint32_t i = 0; i < kNumBlockVertical; i++)
	{
		std::string line;
		getline(mapChipCsv, line);
		//Read one row from the file and transform it into a stream
		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumBlockHorizontal; j++)
		{
			std::string word;

			getline(line_stream, word, ',');

			if (mapChipTable.contains(word)) {
				mapChipData_.data[i][j] = mapChipTable[word];
			}
		}
	}
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex)
{
	//if were outside the mapchip return blank
	if (xIndex < 0 || kNumBlockHorizontal - 1 < xIndex)
	{
		return MapChipType::kBlank;
	}

	if (yIndex < 0 || kNumBlockVertical - 1 < yIndex)
	{
		return MapChipType::kBlank;
	}

	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex)
{
	return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumBlockVertical -1 - yIndex), 0);
}

IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position)
{
	IndexSet indexSet = {};
	indexSet.xIndex = ((uint32_t)position.x + (uint32_t)kBlockWidth / 2) / (uint32_t)kBlockWidth;
	//uint32_t rotateY = ((uint32_t)position.y + (uint32_t)kBlockHeight / 2) / (uint32_t)kBlockHeight;
	//float bh  = (kBlockHeight);
	//float bnv = (kNumBlockVertical);
	//float py  = (position.y);
	//float y = (bh * (bnv - py)) / bh;
	indexSet.yIndex = (((uint32_t)kBlockHeight * (uint32_t)kNumBlockVertical -  (uint32_t)position.y) / (uint32_t)kBlockHeight);
	//indexSet.yIndex = uint32_t(y);
	//int32_t maxYIndex = kNumBlockVertical - 1;
	
	return indexSet;
}

Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex)
{
	Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);
	Rect rect;

	rect.left = center.x - kBlockWidth / 2.0f;
	rect.right = center.x + kBlockWidth / 2.0f;
	rect.top = center.y - kBlockHeight / 2.0f;
	rect.bottom = center.y + kBlockHeight / 2.0f;

	return rect;
}

void MapChipField::Update()
{

}

void MapChipField::Draw()
{

}

