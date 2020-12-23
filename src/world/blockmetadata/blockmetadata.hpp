/*
 * blockmetadata.hpp
 *
 *  Created on: 30 kwi 2020
 *      Author: kuba
 */

#ifndef SRC_WORLD_BLOCKMETADATA_HPP_
#define SRC_WORLD_BLOCKMETADATA_HPP_

enum BlockMetadataType{
	COLORED
};
#include <iostream>
class BlockMetadata {
public:
	virtual std::string toTag()=0;
	virtual void fromTag(std::string tag)=0;
	uint8_t type;
};

#endif /* SRC_WORLD_BLOCKMETADATA_HPP_ */
