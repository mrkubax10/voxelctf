#ifndef SRC_NETWORK_SERVERCONNECTION_HPP
#define SRC_NETWORK_SERVERCONNECTION_HPP
#include <enet/enet.h>
#include "chat.hpp"
#include "../world/world.hpp"

#include "connectedplayer.hpp"
enum ServerInitializationCommand{
    PLAYER_NAME,PLAYER_DATA,MAP_DATA,PLAYER_INIT,REJECT,STATUS,STATUS_RESPONSE
};
enum ServerNetworkCommand{
    MOVE,ACTIVITY,EXIT,READY,CHAT_MESSAGE,WORLD_DATA,NEW_PLAYER,CONNECTION,FLAG_FETCH,FLAG_CAPTURE
};
class App;
class ServerConnection{
    ENetHost* host;
    ENetAddress address;
    ENetPeer* socket;
    ENetEvent event;
    Chat* chat;
    App* app;
    std::vector<ConnectedPlayer> connectedPlayers;
    bool connected;
    long lastActivityResponse;
    uint8_t team;
public:
    bool flag1Fetch;
    bool flag2Fetch;
    ServerConnection(Chat* chat,App* app);
    void initGame(World* world,TextureAtlas* atlas);
    bool connect(std::string ip,int port,std::string name);
    void update();
    void updateActivity();
    void send(char* data,int len);
    void sendChatMessage(std::string message);
    void sendPosition(glm::vec3 position);
    void sendFlagFetch(uint8_t team);
    void sendFlagCapture(uint8_t team);
    void disconnect();
    std::vector<ConnectedPlayer> getPlayerList();
    uint8_t getTeam();
};
#endif