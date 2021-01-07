/*
 * serverconnection.cpp
 *
 *  Created on: 9 kwi 2020
 *      Author: kuba
 */

#include "serverconnection.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
ServerConnection::ServerConnection(Chat* chat){
	ServerConnection::connected=false;
	ServerConnection::lastActivityResponse=0;
	ServerConnection::chat=chat;
}
bool ServerConnection::connect(std::string ip,int port,std::string playerName){

	ServerConnection::playerName=playerName;
	ServerConnection::ip=ip;
	ServerConnection::port=port;
	SDLNet_ResolveHost(&ipAddress,ip.c_str(),port);

	ServerConnection::socket=SDLNet_TCP_Open(&ipAddress);
	if(!socket){
		std::cout<<"(Warn) [ServerConnection] Can't connect to server: "<<SDLNet_GetError()<<std::endl;
		return false;
	}
	if(playerName.length()>255){
		std::cout<<"(Warn) [ServerConnection] Player name is longer than 255"<<std::endl;
		return false;
	}
	
	char* connectionData=(char*)malloc(2+playerName.length());
	connectionData[0]=ServerConnectionCommand::CONNECTION;
	connectionData[1]=playerName.length();
	for(int i=0; i<playerName.length(); i++){
		connectionData[i+2]=playerName[i];
	}
	SDLNet_TCP_Send(ServerConnection::socket,connectionData,2+playerName.length());
	free(connectionData);
	ServerConnection::connected=true;
	sockets=SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(sockets,socket);
	char* playerData=(char*)malloc(MAX_MESSAGE_LENGTH);
	SDLNet_TCP_Recv(socket,playerData,MAX_MESSAGE_LENGTH);
	int dataOffset=2;
	std::cout<<(int)playerData[0]<<std::endl;
	std::cout<<(int)playerData[1]<<std::endl;
	if(playerData[0]==1 && playerData[1]!=0){
		for(int i=0; i<playerData[1]; i++){
			ConnectedPlayer player("",glm::vec3(),playerData[dataOffset]);
			char* name=(char*)malloc(playerData[dataOffset+1]+1);
			for(int b=0; b<playerData[dataOffset+1]; b++){
				name[b]=playerData[dataOffset+1+b];
			}
			std::cout<<(int)playerData[dataOffset+1]<<std::endl;
			name[playerData[dataOffset+1]]='\0';
			std::cout<<name<<std::endl;
			((uint8_t*)&player.position.x)[0]=playerData[dataOffset+1+playerData[dataOffset+1]];
			((uint8_t*)&player.position.x)[1]=playerData[dataOffset+1+playerData[dataOffset+1]+1];
			((uint8_t*)&player.position.x)[2]=playerData[dataOffset+1+playerData[dataOffset+1]+2];
			((uint8_t*)&player.position.x)[3]=playerData[dataOffset+1+playerData[dataOffset+1]+3];
			((uint8_t*)&player.position.y)[0]=playerData[dataOffset+1+playerData[dataOffset+1]+4];
			((uint8_t*)&player.position.y)[1]=playerData[dataOffset+1+playerData[dataOffset+1]+5];
			((uint8_t*)&player.position.y)[2]=playerData[dataOffset+1+playerData[dataOffset+1]+6];
			((uint8_t*)&player.position.y)[3]=playerData[dataOffset+1+playerData[dataOffset+1]+7];
			((uint8_t*)&player.position.z)[0]=playerData[dataOffset+1+playerData[dataOffset+1]+8];
			((uint8_t*)&player.position.z)[1]=playerData[dataOffset+1+playerData[dataOffset+1]+9];
			((uint8_t*)&player.position.z)[2]=playerData[dataOffset+1+playerData[dataOffset+1]+10];
			((uint8_t*)&player.position.z)[3]=playerData[dataOffset+1+playerData[dataOffset+1]+11];
			player.name=std::string(name);
			players.push_back(player);
			dataOffset+=1+playerData[dataOffset+1]+12;
		}
	}
	free(playerData);
	
	return true;

}
void ServerConnection::sendNetworkCommand(int id,char* params,int len){
	char* fullData=(char*)malloc(len+1);
	fullData[0]=id;
	if(params!=0){
		for(int i=1; i<len; i++){
			fullData[i]=params[i-1];
		}
	}
	ServerConnection::send(fullData,1+len);
	free(fullData);
}
void ServerConnection::send(char* data,int len){
	SDLNet_TCP_Send(socket,data,len);
}
void ServerConnection::disconnect(){
	std::cout<<"(Log) [ServerConnection] Disconnecting!"<<std::endl;
	ServerConnection::sendNetworkCommand(ServerConnectionCommand::EXIT,0,0);
	SDLNet_TCP_Close(socket);
	ServerConnection::connected=false;
}
bool ServerConnection::initGame(World* world,TextureAtlas* atlas){
	
	char* worldData=(char*)malloc(MAX_MESSAGE_LENGTH);
	SDLNet_TCP_Recv(ServerConnection::socket,worldData,MAX_MESSAGE_LENGTH);
	if(worldData[0]==0){
		unsigned short worldDataLength=0;
		((uint8_t*)&worldDataLength)[0]=worldData[1];
		((uint8_t*)&worldDataLength)[1]=worldData[2];
		std::vector<unsigned char> worldDataList;
		worldDataList.assign(worldData+20,worldData+worldDataLength+2);
		std::cout<<(int)worldDataList[0]<<std::endl;
		world->loadMapFromMemory(worldDataList);
		world->generateMesh(atlas);
	}
	free(worldData);
	
	return true;
}
void ServerConnection::update(){
	if(ServerConnection::lastActivityResponse+5000<=SDL_GetTicks()){
		std::cout<<"(Warn) [ServerConnection] Timed out"<<std::endl;
		ServerConnection::disconnect();
	}
	if(SDLNet_CheckSockets(sockets,10)>0){
		char* data=(char*)malloc(MAX_MESSAGE_LENGTH);
		SDLNet_TCP_Recv(socket,data,MAX_MESSAGE_LENGTH);
		if(data[0]==ServerConnectionCommand::MOVE){
			for(int i=0; i<ServerConnection::players.size(); i++){
				if(ServerConnection::players[i].id==data[1]){
					((uint8_t*)&players[i].position.x)[0]=data[2];
					((uint8_t*)&players[i].position.x)[1]=data[3];
					((uint8_t*)&players[i].position.x)[2]=data[4];
					((uint8_t*)&players[i].position.x)[3]=data[5];
					((uint8_t*)&players[i].position.y)[0]=data[6];
					((uint8_t*)&players[i].position.y)[1]=data[7];
					((uint8_t*)&players[i].position.y)[2]=data[8];
					((uint8_t*)&players[i].position.y)[3]=data[9];
					((uint8_t*)&players[i].position.z)[0]=data[10];
					((uint8_t*)&players[i].position.z)[1]=data[11];
					((uint8_t*)&players[i].position.z)[2]=data[12];
					((uint8_t*)&players[i].position.z)[3]=data[12+1];
					break;
				}
			}
		}else if(data[0]==ServerConnectionCommand::NEW_PLAYER){
			char* name=(char*)malloc(data[2]+1);
			for(int i=0; i<data[2]; i++){
				name[i]=data[3+i];
			}
			name[data[2]]='\0';
			players.push_back(ConnectedPlayer(std::string(name),glm::vec3(0,0,0),data[1]));
			ServerConnection::chat->addEntry("Player "+std::string(name)+" joined the game");
			free(name);
		}else if(data[0]==ServerConnectionCommand::EXIT){
			for(int i=0; i<ServerConnection::players.size(); i++){
				if(ServerConnection::players[i].id==data[1]){
					ServerConnection::players.erase(players.begin()+i);
					for(int b=i+1; b<ServerConnection::players.size(); b++){
						ServerConnection::players[b].id--;
					}
				}
			}
		}
	}
}
void ServerConnection::updateActivity(){
	char* sendData=(char*)malloc(1);
	sendData[0]=ServerConnectionCommand::ACTIVITY;
	ServerConnection::send(sendData,0);
	free(sendData);
}
void ServerConnection::drawPlayers(Model* playerModel,ShaderProgram program,Camera cam){
	for(int i=0; i<ServerConnection::players.size(); i++){
		playerModel->translate(ServerConnection::players[i].position);
		playerModel->draw(program,cam,GL_TRIANGLES);
	}
}
void ServerConnection::sendPosition(glm::vec3 position){
	char* sendData=(char*)malloc(12+1);
	sendData[0]=ServerConnectionCommand::MOVE;
	sendData[1]=((uint8_t*)&position.x)[0];
	sendData[2]=((uint8_t*)&position.x)[1];
	sendData[3]=((uint8_t*)&position.x)[2];
	sendData[4]=((uint8_t*)&position.x)[3];
	sendData[5]=((uint8_t*)&position.y)[0];
	sendData[6]=((uint8_t*)&position.y)[1];
	sendData[7]=((uint8_t*)&position.y)[2];
	sendData[8]=((uint8_t*)&position.y)[3];
	sendData[9]=((uint8_t*)&position.z)[0];
	sendData[10]=((uint8_t*)&position.z)[1];
	sendData[11]=((uint8_t*)&position.z)[2];
	sendData[12]=((uint8_t*)&position.z)[3];
	ServerConnection::send(sendData,12+1);
	free(sendData);
}

 std::string ServerConnection::getIp() {
	return ip;
}

IPaddress ServerConnection::getIpAddress() {
	return ipAddress;
}

 std::string ServerConnection::getPlayerName() {
	return playerName;
}

int ServerConnection::getPort() {
	return port;
}

TCPsocket ServerConnection::getSocket() {
	return socket;
}
bool ServerConnection::isConnected(){
	return connected;
}
