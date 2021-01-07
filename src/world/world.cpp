/*
 * world.cpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#include "world.hpp"
World::World() {
	World::gravity=0.0001;
	for(int i=0; i<WORLD_SIZE; i++){
		for(int j=0; j<WORLD_SIZE; j++){
			World::chunks[i][j]=Chunk(i,j);
		}
	}
}
void World::destroy(){
	for(int i=0; i<WORLD_SIZE; i++){
		for(int j=0; j<WORLD_SIZE; j++){
			World::chunks[i][j].destroy();
		}
	}
}
void World::draw(Camera cam,ShaderProgram program,ShaderProgram waterProgram){

	for(int i=0; i<WORLD_SIZE; i++){
		for(int j=0; j<WORLD_SIZE; j++){
			World::chunks[i][j].draw(cam,program,waterProgram);
		}
	}
}
void World::setBlock(int x,int y,int z,BlockType type){
	World::getChunk(x/CHUNK_SIZE_WD,z/CHUNK_SIZE_WD)->setBlock(x-x/CHUNK_SIZE_WD*CHUNK_SIZE_WD,y,z-z/CHUNK_SIZE_WD*CHUNK_SIZE_WD,type);
}
Block* World::getBlock(int x,int y,int z){
	return World::getChunk(x/CHUNK_SIZE_WD,z/CHUNK_SIZE_WD)->getBlock(x-x/CHUNK_SIZE_WD*CHUNK_SIZE_WD,y,z-z/CHUNK_SIZE_WD*CHUNK_SIZE_WD);
}
Chunk* World::getChunk(int x,int z){
	if(x<0 || x>WORLD_SIZE || z<0 || z>WORLD_SIZE)
		return new Chunk();
	return &World::chunks[x][z];
}
void World::generateMesh(TextureAtlas* atlas){

	for(int i=0; i<WORLD_SIZE; i++){
			for(int j=0; j<WORLD_SIZE; j++){
				World::chunks[i][j].generateMesh(atlas);
			}
		}
}
void World::loadMapFromMemory(std::vector<unsigned char> chunkData){
	int blockDataID=0;
	BlockType lastBlockType=BlockType::AIR;
	for(int cx=0; cx<WORLD_SIZE; cx++){
		for(int cz=0; cz<WORLD_SIZE; cz++){
			for(int x=0; x<CHUNK_SIZE_WD; x++){
				for(int y=0; y<CHUNK_SIZE_H; y++){
					for(int z=0; z<CHUNK_SIZE_WD; z++){
						if(chunkData[blockDataID]==cx*WORLD_SIZE+x && chunkData[blockDataID+1]==y && chunkData[blockDataID+2]==cz*WORLD_SIZE+z){
							lastBlockType=(BlockType)chunkData[blockDataID+3];
							blockDataID+=4;
						}
						World::getChunk(cx,cz)->setBlock(x,y,z,lastBlockType);
					}
				}
			}
		}
	}
}
void World::loadMap(std::string mapName,TextureAtlas* atlas){
	std::vector<unsigned char> chunkData;
	std::ifstream file("res/maps/"+mapName+".blockctf",std::ios::in|std::ios::binary);
	char* header=(char*)malloc(9);
	file.read(header,9);
	if(strcmp(header,"BlockCTF")!=0){
		
		return;
	}
	char* version=(char*)malloc(8);
	file.read(version,8);
	if(strcmp(version,GAME_VERSION)!=0){
		std::cout<<"(Warn) [Map Loader] Cannot load map: Map is for different version"<<std::endl;
		return;
	}
	char* blockData=(char*)malloc(4);
	while(!file.eof()){
		file.read(blockData,4);
		chunkData.push_back(blockData[0]);
		chunkData.push_back(blockData[1]);
		chunkData.push_back(blockData[2]);
		chunkData.push_back(blockData[3]);
	}
	file.close();
	free((void*)header);
	free((void*)version);
	free((void*)blockData);
	World::loadMapFromMemory(chunkData);
	World::generateMesh(atlas);
}
void World::saveMap(std::string name){
	std::ofstream file("res/maps/"+name+".blockctf",std::ios::out|std::ios::binary);
	file.write("BlockCTF",sizeof("BlockCTF"));
	file.write(GAME_VERSION,sizeof(GAME_VERSION));
	std::vector<char> mapData;
	BlockType lastBlockType=BlockType::AIR;
	mapData.push_back(0);
	mapData.push_back(0);
	mapData.push_back(0);
	mapData.push_back(World::getChunk(0,0)->getBlock(0,0,0)->type);
	for(int cx=0; cx<WORLD_SIZE; cx++){
		for(int cz=0; cz<WORLD_SIZE; cz++){
			for(int x=0; x<CHUNK_SIZE_WD; x++){
				for(int y=0; y<CHUNK_SIZE_H; y++){
					for(int z=0; z<CHUNK_SIZE_WD; z++){
						if(World::getChunk(cx,cz)->getBlock(x,y,z)->type!=(uint8_t)lastBlockType){
							lastBlockType=(BlockType)World::getChunk(cx,cz)->getBlock(x,y,z)->type;
							mapData.push_back(cx*CHUNK_SIZE_WD+x);
							mapData.push_back(y);
							mapData.push_back(cz*CHUNK_SIZE_WD+z);
							mapData.push_back(World::getChunk(cx,cz)->getBlock(x,y,z)->type);
						}
					}
				}
			}
		}
	}
	file.write(mapData.data(),mapData.size());
	file.close();
}
float World::getGravity(){
	return gravity;
}
