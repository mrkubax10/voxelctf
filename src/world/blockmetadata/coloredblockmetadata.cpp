/*
 * coloredblockmetadata.cpp
 *
 *  Created on: 30 kwi 2020
 *      Author: kuba
 */

#include "coloredblockmetadata.hpp"

ColoredBlockMetadata::ColoredBlockMetadata(){
	ColoredBlockMetadata::type=BlockMetadataType::COLORED;
}

std::string ColoredBlockMetadata::toTag(){
	return "";
}
void ColoredBlockMetadata::fromTag(std::string tag){

}
