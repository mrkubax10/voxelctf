/*
 * chunk.hpp
 *
 *  Created on: 18 mar 2020
 *      Author: kuba
 */

#ifndef SRC_WORLD_CHUNK_HPP_
#define SRC_WORLD_CHUNK_HPP_
#define CHUNK_SIZE_WD 16
#define CHUNK_SIZE_H 64
#include "block.hpp"
#include "blockinformations.hpp"
#include <vector>
#include "textureatlas.hpp"
#include "../render/camera.hpp"
#include "blockmetadata/blockmetadata.hpp"
#include "blockmetadata/coloredblockmetadata.hpp"
struct ChunkMesh{
	unsigned int blocksVAO,blocksVBO,blocksEBO,blocksTBO,blockNormals;
	unsigned int waterVAO,waterVBO,waterEBO,waterTBO;
	int blockIndicesCount,waterIndicesCount;
};
class Chunk {
	short x,z;
	Block blocks[CHUNK_SIZE_WD][CHUNK_SIZE_H][CHUNK_SIZE_WD];
	ChunkMesh mesh;
	bool hasGeneratedMesh;
	std::map<int,std::map<int,std::map<int,BlockMetadata*>>> metadata;
public:
	Chunk(short x,short z);
	Chunk();
	void generateMesh(TextureAtlas* atlas);
	void draw(Camera cam,ShaderProgram program,ShaderProgram waterProgram);
	Block* getBlock(int x,int y,int z);
	void setBlock(int x,int y,int z,BlockType type);
	void generateSimpleTerrain(int maxHeight=64,int minHeight=1);
	bool isHasGeneratedMesh();
	void setHasGeneratedMesh(bool hasGeneratedMesh);
	bool blockHasMetadata(int x,int y,int z);
};

#endif /* SRC_WORLD_CHUNK_HPP_ */
