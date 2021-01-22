/*
 * chunk.cpp
 *
 *  Created on: 18 mar 2020
 *      Author: kuba
 */

#include "chunk.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/noise.hpp>
Chunk::Chunk(short x,short z){
	Chunk::x=x;
	Chunk::z=z;
	glGenBuffers(1,&mesh.blocksVBO);
	glGenBuffers(1,&mesh.blocksEBO);
	glGenBuffers(1,&mesh.blocksTBO);
	glGenBuffers(1,&mesh.waterVBO);
	glGenBuffers(1,&mesh.waterEBO);
	glGenBuffers(1,&mesh.waterTBO);
	glGenBuffers(1,&mesh.blockNormals);
	glGenVertexArrays(1,&mesh.blocksVAO);
	glGenVertexArrays(1,&mesh.waterVAO);
	
	Chunk::hasGeneratedMesh=false;
}
Chunk::Chunk(){
	Chunk::x=0;
	Chunk::z=0;
	Chunk::hasGeneratedMesh=false;
}
void Chunk::destroy(){
	glDeleteBuffers(1,&mesh.blocksVBO);
	glDeleteBuffers(1,&mesh.blocksTBO);
	glDeleteBuffers(1,&mesh.blocksEBO);
	glDeleteBuffers(1,&mesh.waterVBO);
	glDeleteBuffers(1,&mesh.waterTBO);
	glDeleteBuffers(1,&mesh.waterEBO);
	glDeleteVertexArrays(1,&mesh.blocksVAO);
	glDeleteVertexArrays(1,&mesh.waterVAO);
}
void Chunk::generateMesh(TextureAtlas* atlas){
	std::vector<float>* blockVertices=new std::vector<float>;
	std::vector<float>* blockUVs=new std::vector<float>;
	std::vector<float>* waterVertices=new std::vector<float>;
	std::vector<float>* waterUVs=new std::vector<float>;
	std::vector<float>* blockLightValues=new std::vector<float>;
	std::vector<float>* waterNormals=new std::vector<float>;
	std::vector<unsigned int>* blockIndices=new std::vector<unsigned int>;
	std::vector<unsigned int>* waterIndices=new std::vector<unsigned int>;
	std::vector<float> *currentVertices=blockVertices,*currentUVs=blockUVs,*currentLightValues=blockLightValues;
	std::vector<unsigned int> *currentIndices=blockIndices;
	int faces=0;
	float lightValue=1.0f;
	for(int x=0; x<CHUNK_SIZE_WD; x++){
		for(int y=0; y<CHUNK_SIZE_H; y++){
			for(int z=0; z<CHUNK_SIZE_WD; z++){
				if(BlockInformations::getBlockInformations(Chunk::getBlock(x,y,z)->type).invisible)
					continue;
				if(!BlockInformations::getBlockInformations(Chunk::getBlock(x+1,y,z)->type).transparent &&
						!BlockInformations::getBlockInformations(Chunk::getBlock(x-1,y,z)->type).transparent &&
						!BlockInformations::getBlockInformations(Chunk::getBlock(x,y+1,z)->type).transparent &&
						!BlockInformations::getBlockInformations(Chunk::getBlock(x,y-1,z)->type).transparent &&
						!BlockInformations::getBlockInformations(Chunk::getBlock(x,y,z+1)->type).transparent &&
						!BlockInformations::getBlockInformations(Chunk::getBlock(x,y,z-1)->type).transparent)
					continue;
				if((BlockType)Chunk::getBlock(x,y,z)->type==10 || (BlockType)Chunk::getBlock(x,y,z)->type==11){
					currentVertices=waterVertices;
					currentUVs=waterUVs;
					currentIndices=waterIndices;
					currentLightValues=waterNormals;
				}else{
					currentVertices=blockVertices;
					currentUVs=blockUVs;
					currentIndices=blockIndices;
					currentLightValues=blockLightValues;
				}
				if(BlockInformations::getBlockInformations(Chunk::getBlock(x+1,y,z)->type).transparent){
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).left);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).left+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).left+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).left);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-3);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-1);
					for(int i=0; i<4; i++){
						currentLightValues->push_back(0.5f);
					}
					faces++;
				}
				if(BlockInformations::getBlockInformations(Chunk::getBlock(x-1,y,z)->type).transparent){
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).right);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).right+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).right+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).right);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-3);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-1);
					for(int i=0; i<4; i++){
						currentLightValues->push_back(0.5f);
					}
					faces++;
				}
				if(BlockInformations::getBlockInformations(Chunk::getBlock(x,y+1,z)->type).transparent){
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).top);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).top+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).top+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).top);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-3);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-1);
					lightValue=1.0f;
					for(int i=y+1; i<CHUNK_SIZE_H; i++){
						if(!BlockInformations::getBlockInformations(Chunk::getBlock(x,i,z)->type).transparent)
							lightValue=0.5f;
					}
					for(int i=0; i<4; i++){
						currentLightValues->push_back(lightValue);
					}
					faces++;
				}
				if(BlockInformations::getBlockInformations(Chunk::getBlock(x,y-1,z)->type).transparent){
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).bottom);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).bottom+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).bottom+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).bottom);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-3);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-1);
					for(int i=0; i<4; i++){
						currentLightValues->push_back(0.4f);
					}
					faces++;
				}
				if(BlockInformations::getBlockInformations(Chunk::getBlock(x,y,z+1)->type).transparent){
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z+1);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).front);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).front+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).front+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).front);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-3);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-1);
					for(int i=0; i<4; i++){
						currentLightValues->push_back(0.5f);
					}
					faces++;
				}
				if(BlockInformations::getBlockInformations(Chunk::getBlock(x,y,z-1)->type).transparent){
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentVertices->push_back(Chunk::x*CHUNK_SIZE_WD+x+1);
					currentVertices->push_back(y+1);
					currentVertices->push_back(Chunk::z*CHUNK_SIZE_WD+z);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).back);
					currentUVs->push_back(0);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).back+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).back+atlas->getTextureBlockSize());
					currentUVs->push_back(1);
					currentUVs->push_back(atlas->getBlockUV(Chunk::getBlock(x,y,z)->type).back);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-3);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-2);
					currentIndices->push_back(currentVertices->size()/3-4);
					currentIndices->push_back(currentVertices->size()/3-1);
					for(int i=0; i<4; i++){
						currentLightValues->push_back(0.5f);
					}
					faces++;
				}
			}
		}
	}
	glBindVertexArray(Chunk::mesh.blocksVAO);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.blocksVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*blockVertices->size(),blockVertices->data(),GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Chunk::mesh.blocksEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*blockIndices->size(),blockIndices->data(),GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.blocksTBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*blockUVs->size(),blockUVs->data(),GL_STATIC_DRAW);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.blockNormals);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*blockLightValues->size(),blockLightValues->data(),GL_STATIC_DRAW);
	glVertexAttribPointer(2,1,GL_FLOAT,GL_FALSE,1*sizeof(float),(void*)0);
	glBindVertexArray(0);
	
	glBindVertexArray(Chunk::mesh.waterVAO);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.waterVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*waterVertices->size(),waterVertices->data(),GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Chunk::mesh.waterEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int)*waterIndices->size(),waterIndices->data(),GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.waterTBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(float)*waterUVs->size(),waterUVs->data(),GL_STATIC_DRAW);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2*sizeof(float),(void*)0);
	
	Chunk::mesh.blockIndicesCount=blockIndices->size();
	Chunk::mesh.waterIndicesCount=waterIndices->size();
	Chunk::setHasGeneratedMesh(true);
	delete blockVertices;
	delete blockUVs;
	delete blockLightValues;
	delete waterVertices;
	delete waterUVs;
	delete waterNormals;
	delete blockIndices;
	delete waterIndices;
	
}
Block* Chunk::getBlock(int x,int y,int z){
	if(x<0 || x>=CHUNK_SIZE_WD || y<0 || y>=CHUNK_SIZE_H || z<0 || z>=CHUNK_SIZE_WD)
		return new Block(BlockType::AIR);
	return &Chunk::blocks[x][y][z];
}
void Chunk::setBlock(int x,int y,int z,BlockType type){
	if(x<0 || x>CHUNK_SIZE_WD || y<0 || y>CHUNK_SIZE_H || z<0 || z>CHUNK_SIZE_WD)
		return;
	Chunk::blocks[x][y][z].type=type;
}
void Chunk::draw(Camera cam,ShaderProgram program,ShaderProgram waterProgram){
	// Block rendering
	if(!Chunk::isHasGeneratedMesh()) return;
	glEnable(GL_DEPTH_TEST);
	program.use();
	glBindVertexArray(Chunk::mesh.blocksVAO);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.blocksVBO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.blocksTBO);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Chunk::mesh.blocksEBO);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.blockNormals);
	glEnableVertexAttribArray(2);
	
	program.setMat4("projection",cam.getProjection());
	program.setMat4("view",cam.getView());
	program.setInt("textureid",0);
	glDrawElements(GL_TRIANGLES,Chunk::mesh.blockIndicesCount,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(2);
	// Fluid (water, lava etc.) block rendering
	waterProgram.use();
	glBindVertexArray(Chunk::mesh.waterVAO);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.waterVBO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,Chunk::mesh.waterTBO);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,Chunk::mesh.waterEBO);
	program.setMat4("projection",cam.getProjection());
	program.setMat4("view",cam.getView());
	program.setInt("textureid",0);
	glDrawElements(GL_TRIANGLES,Chunk::mesh.waterIndicesCount,GL_UNSIGNED_INT,0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
}

bool Chunk::isHasGeneratedMesh() {
	return hasGeneratedMesh;
}

void Chunk::setHasGeneratedMesh(bool hasGeneratedMesh) {
	Chunk::hasGeneratedMesh = hasGeneratedMesh;
}
void Chunk::generateSimpleTerrain(int maxHeight,int minHeight){
	for(int x=0; x<CHUNK_SIZE_WD; x++){
		for(int z=0;z<CHUNK_SIZE_WD; z++){
			float height=glm::simplex(glm::vec2((float)(Chunk::x*CHUNK_SIZE_WD+x)/64.0f,(float)(Chunk::z*CHUNK_SIZE_WD+z)/64.0f))*(maxHeight-minHeight);
			for(int y=0; y<minHeight+height; y++){
				Chunk::setBlock(x,y,z,BlockType::STONE);
			}
			if(minHeight+height<20)
				Chunk::setBlock(x,minHeight+height+1,z,BlockType::SAND);
			else
				Chunk::setBlock(x,minHeight+height+1,z,BlockType::GRASS);

		}
	}
}

bool Chunk::findChunkInVector(std::vector<glm::vec2> vec,glm::vec2 chunk){
	bool out=false;
	for(int i=0; i<vec.size(); i++){
		if(vec[i]==chunk){
			out=true;
			break;
		}
	}
	return out;
}
bool Chunk::blockHasMetadata(int x,int y,int z){
	if(Chunk::metadata.count(x)){
		if(Chunk::metadata.count(y)){
			if(Chunk::metadata.count(z))
				return true;
		}
	}
	return 0;
}
