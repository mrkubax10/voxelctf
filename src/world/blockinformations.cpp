/*
 * blockinformations.cpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#include "blockinformations.hpp"
BlockInformations BlockInformations::_inst;
BlockModel BlockInformations::cubeBlock;
BlockModel BlockInformations::slabBlock;
BlockModel BlockInformations::stairsBlock;
BlockInformation BlockInformation::createDefault(){
	BlockInformation inf;
	inf.collidable=true;
	inf.transparent=false;
	inf.invisible=false;
	inf.model=&BlockInformations::cubeBlock;
	inf.fluid=false;
	return inf;
}
BlockInformations::BlockInformations() {
	//Block
	informations[BlockType::AIR].collidable=false;
	informations[BlockType::AIR].transparent=true;
	informations[BlockType::AIR].model=0;
	informations[BlockType::AIR].invisible=true;
	informations[BlockType::STONE]=BlockInformation::createDefault();
	informations[BlockType::COBBLE]=BlockInformation::createDefault();
	informations[BlockType::STONE_BRICKS]=BlockInformation::createDefault();
	informations[BlockType::BRICKS]=BlockInformation::createDefault();
	informations[BlockType::IRON]=BlockInformation::createDefault();
	informations[BlockType::WATER].collidable=false;
	informations[BlockType::WATER].transparent=true;
	informations[BlockType::WATER].invisible=false;
	informations[BlockType::WATER].fluid=true;
	informations[BlockType::WATER].model=&BlockInformations::cubeBlock;
	informations[BlockType::LAVA].collidable=false;
	informations[BlockType::LAVA].transparent=true;
	informations[BlockType::LAVA].invisible=false;
	informations[BlockType::LAVA].fluid=false;
	informations[BlockType::LAVA].model=&BlockInformations::cubeBlock;
	informations[BlockType::GLASS].collidable=true;
	informations[BlockType::GLASS].transparent=true;
	informations[BlockType::GLASS].invisible=false;
	informations[BlockType::GLASS].model=&BlockInformations::cubeBlock;
	informations[BlockType::GRASS]=BlockInformation::createDefault();
	informations[BlockType::POLISHED_STONE]=BlockInformation::createDefault();
	informations[BlockType::WOOD]=BlockInformation::createDefault();
	informations[BlockType::PLANKS]=BlockInformation::createDefault();
	informations[BlockType::LEAVES].collidable=true;
	informations[BlockType::LEAVES].fluid=false;
	informations[BlockType::LEAVES].invisible=false;
	informations[BlockType::LEAVES].transparent=true;
	informations[BlockType::LEAVES].model=&BlockInformations::cubeBlock;
}
BlockInformation BlockInformations::_getBlockInformations(uint8_t type){
	return BlockInformations::informations[type];
}
BlockInformation BlockInformations::getBlockInformations(uint8_t type){
	return _inst._getBlockInformations(type);
}
