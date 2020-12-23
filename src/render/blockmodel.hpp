/*
 * BlockModel.h
 *
 *  Created on: 5 cze 2020
 *      Author: kuba
 */

#ifndef SRC_RENDER_BLOCKMODEL_HPP_
#define SRC_RENDER_BLOCKMODEL_HPP_
#include <vector>
class BlockModel {
public:
	std::vector<float> vertices;
	std::vector<float> uvs;
};

#endif /* SRC_RENDER_BLOCKMODEL_HPP_ */
