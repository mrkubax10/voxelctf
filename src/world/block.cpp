/*
 * block.cpp
 *
 *  Created on: 18 mar 2020
 *      Author: kuba
 */

#include "block.hpp"

Block::Block() {
	Block::type=BlockType::AIR;

}
Block::Block(BlockType type){
	Block::type=type;
}
