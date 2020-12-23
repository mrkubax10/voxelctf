/*
 * coloredblockmetadata.hpp
 *
 *  Created on: 30 kwi 2020
 *      Author: kuba
 */

#ifndef SRC_WORLD_BLOCKMETADATA_COLOREDBLOCKMETADATA_HPP_
#define SRC_WORLD_BLOCKMETADATA_COLOREDBLOCKMETADATA_HPP_
#include "blockmetadata.hpp"
#include <glm/glm.hpp>
class ColoredBlockMetadata:public BlockMetadata {
public:
	ColoredBlockMetadata();
	std::string toTag();
	void fromTag(std::string);
	glm::vec4 color;
};

#endif /* SRC_WORLD_BLOCKMETADATA_COLOREDBLOCKMETADATA_HPP_ */
