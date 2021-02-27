/*
 * block.hpp
 *
 *  Created on: 18 mar 2020
 *      Author: kuba
 */

#ifndef SRC_WORLD_BLOCK_HPP_
#define SRC_WORLD_BLOCK_HPP_
#include <stdint.h>
enum BlockType{
	AIR,STONE,COBBLE,STONE_BRICKS,GRASS,BRICKS,SAND,IRON,GOLD,CRYSTAL,WATER,LAVA,DIRT,GLASS,CARDBOARD,POLISHED_STONE,
	WOOD,PLANKS,LEAVES
};
class Block {
public:
	uint8_t type;
	Block();
	Block(BlockType type);
};

#endif /* SRC_WORLD_BLOCK_HPP_ */
