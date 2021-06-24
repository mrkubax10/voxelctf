/*
 * world.cpp
 *
 *  Created on: 19 mar 2020
 *      Author: kuba
 */

#include "world.hpp"
#include "../framework/app.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
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
void World::renderEntities(ShaderProgram program,Camera cam,Model* flagModel,App* app){
	if(!app->getServerConnection()->flag1Fetch){
		app->getResourceManager()->getNativeTexture("team1flag")->use();
		flagModel->translate(metadata.team1FlagPosition);
		flagModel->draw(program,cam,GL_TRIANGLES);
	}
	if(!app->getServerConnection()->flag2Fetch){
		app->getResourceManager()->getNativeTexture("team2flag")->use();
		flagModel->translate(metadata.team2FlagPosition);
		flagModel->draw(program,cam,GL_TRIANGLES);
	}
}
void World::loadMapFromMemory(std::vector<unsigned char> chunkData){
	World::metadata.team1FlagPosition.x=chunkData[0];
	World::metadata.team1FlagPosition.y=chunkData[1];
	World::metadata.team1FlagPosition.z=chunkData[2];
	World::metadata.team2FlagPosition.x=chunkData[3];
	World::metadata.team2FlagPosition.y=chunkData[4];
	World::metadata.team2FlagPosition.z=chunkData[5];
	int blockDataID=5+1;
	BlockType lastBlockType=BlockType::AIR;
	for(int cx=0; cx<WORLD_SIZE*CHUNK_SIZE_WD; cx++){
		for(int y=0; y<CHUNK_SIZE_H; y++){
			for(int cz=0; cz<WORLD_SIZE*CHUNK_SIZE_WD; cz++){
				if(chunkData[blockDataID]==cx && chunkData[blockDataID+1]==y && chunkData[blockDataID+2]==cz){
					lastBlockType=(BlockType)chunkData[blockDataID+3];
					blockDataID+=4;
				}
				World::setBlock(cx,y,cz,lastBlockType);
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
	char* data=(char*)malloc(5+1);
	file.read(data,5+1);
	chunkData.push_back(data[0]);
	chunkData.push_back(data[1]);
	chunkData.push_back(data[2]);
	chunkData.push_back(data[3]);
	chunkData.push_back(data[4]);
	chunkData.push_back(data[5]);
	free(data);
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
void World::createDefaultMap(){
	for(int x=0; x<WORLD_SIZE*CHUNK_SIZE_WD; x++){
		for(int z=0; z<WORLD_SIZE*CHUNK_SIZE_WD; z++){
			World::setBlock(x,0,z,BlockType::POLISHED_STONE);
		}
	}
}
void World::saveMap(std::string name){
	std::ofstream file("res/maps/"+name+".blockctf",std::ios::out|std::ios::binary);
	uint8_t team1Flag[3],team2Flag[3];
	team1Flag[0]=(uint8_t)World::metadata.team1FlagPosition.x;
	team1Flag[1]=(uint8_t)World::metadata.team1FlagPosition.y;
	team1Flag[2]=(uint8_t)World::metadata.team1FlagPosition.z;
	team2Flag[0]=(uint8_t)World::metadata.team2FlagPosition.x;
	team2Flag[1]=(uint8_t)World::metadata.team2FlagPosition.y;
	team2Flag[2]=(uint8_t)World::metadata.team2FlagPosition.z;
	file.write("BlockCTF",sizeof("BlockCTF"));
	file.write(GAME_VERSION,sizeof(GAME_VERSION));
	file.write((char*)&team1Flag[0],1);
	file.write((char*)&team1Flag[1],1);
	file.write((char*)&team1Flag[2],1);
	file.write((char*)&team2Flag[0],1);
	file.write((char*)&team2Flag[1],1);
	file.write((char*)&team2Flag[2],1);
	std::vector<char> mapData;
	BlockType lastBlockType=BlockType::AIR;
	mapData.push_back(0);
	mapData.push_back(0);
	mapData.push_back(0);
	mapData.push_back(World::getChunk(0,0)->getBlock(0,0,0)->type);
	for(int cx=0; cx<WORLD_SIZE*CHUNK_SIZE_WD; cx++){
		for(int y=0; y<CHUNK_SIZE_H; y++){
			for(int cz=0; cz<WORLD_SIZE*CHUNK_SIZE_WD; cz++){
				if(lastBlockType!=World::getBlock(cx,y,cz)->type){
					lastBlockType=(BlockType)World::getBlock(cx,y,cz)->type;
					mapData.push_back(cx);
					mapData.push_back(y);
					mapData.push_back(cz);
					mapData.push_back(World::getBlock(cx,y,cz)->type);
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
