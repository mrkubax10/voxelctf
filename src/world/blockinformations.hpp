/*
 * blockinformations.hpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#ifndef SRC_WORLD_BLOCKINFORMATIONS_HPP_
#define SRC_WORLD_BLOCKINFORMATIONS_HPP_
#include "block.hpp"
#include "../global.hpp"
#include <map>
#include "../render/blockmodel.hpp"
class BlockInformation{
public:
	bool transparent,collidable,invisible,fluid;
	static BlockInformation createDefault();
	BlockModel* model;
};
class BlockInformations {
	std::map<uint8_t,BlockInformation> informations;
	static BlockInformations _inst;
	BlockInformation _getBlockInformations(uint8_t type);

public:
	static BlockModel cubeBlock,stairsBlock,slabBlock;
	BlockInformations();
	static BlockInformation getBlockInformations(uint8_t type);
};

#endif /* SRC_WORLD_BLOCKINFORMATIONS_HPP_ */
