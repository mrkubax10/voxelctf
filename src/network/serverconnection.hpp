#ifndef SRC_NETWORK_SERVERCONNECTION_HPP
#define SRC_NETWORK_SERVERCONNECTION_HPP
#include <enet/enet.h>
#include "chat.hpp"
#include "../world/world.hpp"
enum ServerInitializationCommand{
    PLAYER_NAME,PLAYER_DATA,MAP_DATA
};
enum ServerNetworkCommand{
    MOVE,ACTIVITY,EXIT,READY,CHAT_MESSAGE,WORLD_DATA,REJECT,NEW_PLAYER,CONNECTION
};
class ServerConnection{
    ENetHost* host;
    ENetAddress address;
    ENetPeer* socket;
    ENetEvent event;
    Chat* chat;
    bool connected;
public:
    ServerConnection(Chat* chat);
    void initGame(World* world,TextureAtlas* atlas);
    bool connect(std::string ip,int port,std::string name);
    void update();
    void send(char* data,int len);
    void disconnect();
};
#endif