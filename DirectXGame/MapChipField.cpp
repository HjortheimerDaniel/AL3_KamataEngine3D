#include "MapChipField.h"
#include <map>
#include <string>

namespace 
{

	std::map<std::string, MapChipType> mapChipTable =
	{
		{"0", MapChipType::kBlank},
		{"1", MapChipType::kBlock},
	};
	
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
