/*
 * world.hpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#ifndef SRC_WORLD_WORLD_HPP_
#define SRC_WORLD_WORLD_HPP_
#define WORLD_SIZE 16
#include "chunk.hpp"
#include "../render/camera.hpp"
class World {
	Chunk chunks[WORLD_SIZE][WORLD_SIZE];
	float gravity;
	
public:
	World();
	void destroy();
	void draw(Camera cam,ShaderProgram program,ShaderProgram waterProgram);
	void setBlock(int x,int y,int z,BlockType type);
	Block* getBlock(int x,int y,int z);
	Chunk* getChunk(int x,int z);
	void generateMesh(TextureAtlas* atlas);
	void loadMap(std::string name,TextureAtlas* atlas);
	void loadMapFromMemory(std::vector<unsigned char> chunkData);
	void saveMap(std::string name);
	float getGravity();
	struct{
		glm::vec3 team1FlagPosition,team2FlagPosition;
	} metadata;
};

#endif /* SRC_WORLD_WORLD_HPP_ */
