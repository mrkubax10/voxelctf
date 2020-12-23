/*
 * serverconnection.hpp
 *
 *  Created on: 9 kwi 2020
 *      Author: kuba
 */

#ifndef SRC_NETWORK_SERVERCONNECTION_HPP_
#define SRC_NETWORK_SERVERCONNECTION_HPP_
#include "../global.hpp"
#include "../world/world.hpp"
#include "../world/textureatlas.hpp"
#include "connectedplayer.hpp"
#include "../render/model.hpp"
enum ServerConnectionCommand{
	MOVE,ACTIVITY,EXIT,READY,CHAT_MESSAGE,WORLD_DATA,REJECT,NEW_PLAYER,CONNECTION
};
#define MAX_MESSAGE_LENGTH 65537 // sizeof(unsigned short)+2
class ServerConnection {
	TCPsocket socket;
	std::string playerName;
	std::string ip;
	int port;
	IPaddress ipAddress;
	bool connected;
	int lastActivityResponse;
	int lastCommandTime;
	SDLNet_SocketSet sockets;
	std::vector<ConnectedPlayer> players;
	
public:
	ServerConnection();
	bool connect(std::string ip,int port,std::string playerName);
	void sendNetworkCommand(int id,char* params,int len);
	void send(char* data,int len);
	void disconnect();
	bool initGame(World *world,TextureAtlas* atlas);
	void update();
	void updateActivity();
	void sendPosition(glm::vec3 position);
	void drawPlayers(Model* playerModel,ShaderProgram program,Camera cam);
	std::string getIp();
	IPaddress getIpAddress();
	std::string getPlayerName();
	int getPort();
	TCPsocket getSocket();
	bool isConnected();
};

#endif /* SRC_NETWORK_SERVERCONNECTION_HPP_ */
