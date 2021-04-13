#include "serverconnection.hpp"
#include "../framework/app.hpp"
#include "../frames/frameconstants.hpp"
ServerConnection::ServerConnection(Chat* chat,App* app){
    ServerConnection::chat=chat;
    ServerConnection::app=app;
    ServerConnection::lastActivityResponse=time(0);
}
bool ServerConnection::connect(std::string ip,int port,std::string name){
    ServerConnection::host=enet_host_create(0,1,2,0,0);
    ServerConnection::lastActivityResponse=time(0);
    enet_address_set_host(&address,ip.c_str());
    address.port=port;
    ServerConnection::socket=enet_host_connect(host,&address,2,0);
    if(!enet_host_service(host,&event,5000)){
        std::cout<<"(Warn) [ServerConnection] Failed to connect to server"<<std::endl;
        return false;
    }
    char* sendData=(char*)malloc(2+name.length());
    sendData[0]=ServerInitializationCommand::PLAYER_NAME;
    sendData[1]=name.length();
    for(int i=0; i<name.length(); i++){
        sendData[i+2]=name[i];
    }
    ServerConnection::send(sendData,2+name.length());
    //!!!!!
    free(sendData);
    ServerConnection::connected=true;
    return true;
}
void ServerConnection::initGame(World* world,TextureAtlas* atlas){
    ServerConnection::connectedPlayers.push_back(ConnectedPlayer("",glm::vec3(1000,0,1000),0,0,ServerConnection::app));
    if(enet_host_service(host,&event,10000)>0){
        if(event.type==ENET_EVENT_TYPE_RECEIVE){
            if(event.packet->data[0]==ServerInitializationCommand::PLAYER_DATA){
                int dataOffset=2;
                if(event.packet->data[1]>0)
                    ServerConnection::connectedPlayers.erase(ServerConnection::connectedPlayers.begin());
                for(int i=0; i<event.packet->data[1]; i++){
                    std::string name;
                    for(int a=0; a<event.packet->data[dataOffset]; a++){
                        name+=event.packet->data[dataOffset+a+1];
                    }
                    float x,y,z;
                    ((uint8_t*)&x)[0]=event.packet->data[dataOffset+name.length()+1];
                    ((uint8_t*)&x)[1]=event.packet->data[dataOffset+name.length()+2];
                    ((uint8_t*)&x)[2]=event.packet->data[dataOffset+name.length()+3];
                    ((uint8_t*)&x)[3]=event.packet->data[dataOffset+name.length()+4];
                    ((uint8_t*)&y)[0]=event.packet->data[dataOffset+name.length()+5];
                    ((uint8_t*)&y)[1]=event.packet->data[dataOffset+name.length()+6];
                    ((uint8_t*)&y)[2]=event.packet->data[dataOffset+name.length()+7];
                    ((uint8_t*)&y)[3]=event.packet->data[dataOffset+name.length()+8];
                    ((uint8_t*)&z)[0]=event.packet->data[dataOffset+name.length()+9];
                    ((uint8_t*)&z)[1]=event.packet->data[dataOffset+name.length()+10];
                    ((uint8_t*)&z)[2]=event.packet->data[dataOffset+name.length()+11];
                    ((uint8_t*)&z)[3]=event.packet->data[dataOffset+name.length()+12];
                    
                    ServerConnection::connectedPlayers.push_back(ConnectedPlayer(name,glm::vec3(x,y,z),event.packet->data[dataOffset+name.length()+12+1],event.packet->data[dataOffset+name.length()+14],ServerConnection::app));
                    dataOffset+=3+name.length()+12;
                }
            }
            enet_packet_destroy(event.packet);
        }
    }
    else{
        std::cout<<"(Warn) [ServerConnection] Failed to recieve player data from server"<<std::endl;
    }
    if(enet_host_service(host,&event,10000)>0){
        if(event.type==ENET_EVENT_TYPE_RECEIVE){
            if(event.packet->data[0]==ServerInitializationCommand::MAP_DATA){
                std::vector<unsigned char> mapData;
                mapData.assign(event.packet->data+18,event.packet->data+event.packet->dataLength);
                world->loadMapFromMemory(mapData);
                world->generateMesh(atlas);
            }
            enet_packet_destroy(event.packet);
        }
    }
    else{
        std::cout<<"(Warn) [ServerConnection] Failed to receive map data from server"<<std::endl;
    }
    if(enet_host_service(host,&event,10000)>0){
        if(event.type==ENET_EVENT_TYPE_RECEIVE){
            if(event.packet->data[0]==ServerInitializationCommand::PLAYER_INIT){
                ServerConnection::team=event.packet->data[1];
            }
        }
    }
    else{
        std::cout<<"(Warn) [ServerConnection] Failed to receive player init data"<<std::endl;
    }
}
void ServerConnection::send(char* data,int len){
    ENetPacket* packet=enet_packet_create(data,len,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(socket,0,packet);
    enet_host_flush(host);
    // if(packet)
    //     enet_packet_destroy(packet);
}
void ServerConnection::update(){
    while(enet_host_service(host,&event,0)){
        if(event.type==ENET_EVENT_TYPE_RECEIVE){
            if(event.packet->data[0]==ServerNetworkCommand::MOVE){
                float x,y,z;
                ((uint8_t*)&x)[0]=event.packet->data[2];
                ((uint8_t*)&x)[1]=event.packet->data[3];
                ((uint8_t*)&x)[2]=event.packet->data[4];
                ((uint8_t*)&x)[3]=event.packet->data[5];
                ((uint8_t*)&y)[0]=event.packet->data[6];
                ((uint8_t*)&y)[1]=event.packet->data[7];
                ((uint8_t*)&y)[2]=event.packet->data[8];
                ((uint8_t*)&y)[3]=event.packet->data[9];
                ((uint8_t*)&z)[0]=event.packet->data[10];
                ((uint8_t*)&z)[1]=event.packet->data[11];
                ((uint8_t*)&z)[2]=event.packet->data[12];
                ((uint8_t*)&z)[3]=event.packet->data[12+1];
                ServerConnection::connectedPlayers[event.packet->data[1]].position.x=x;
                ServerConnection::connectedPlayers[event.packet->data[1]].position.y=y;
                ServerConnection::connectedPlayers[event.packet->data[1]].position.z=z;
            }
            else if(event.packet->data[0]==ServerNetworkCommand::EXIT){
                ServerConnection::chat->addEntry(ServerConnection::app->getLanguageManager()->getFromLanguage("in_playerexit",connectedPlayers[event.packet->data[1]].name));
                for(int i=event.packet->data[1]+1; i<ServerConnection::connectedPlayers.size(); i++){
                    ServerConnection::connectedPlayers[i].id--;
                }
                ServerConnection::connectedPlayers.erase(ServerConnection::connectedPlayers.begin()+event.packet->data[1]);
            
            }
            else if(event.packet->data[0]==ServerNetworkCommand::ACTIVITY){
                ServerConnection::lastActivityResponse=time(0);
            }
            else if(event.packet->data[0]==ServerNetworkCommand::CHAT_MESSAGE){
                short messageLength;
                std::string message=ServerConnection::connectedPlayers[event.packet->data[1]].name+": ";
                ((uint8_t*)&messageLength)[0]=event.packet->data[2];
                ((uint8_t*)&messageLength)[1]=event.packet->data[3];
                for(int i=0; i<messageLength; i++){
                    message+=event.packet->data[4+i];
                }
                ServerConnection::chat->addEntry(message);
            }
            else if(event.packet->data[0]==ServerNetworkCommand::NEW_PLAYER){
                std::string name;
                for(int i=0; i<event.packet->data[3]; i++){
                    name+=event.packet->data[4+i];
                }
                ServerConnection::chat->addEntry(ServerConnection::app->getLanguageManager()->getFromLanguage("in_newplayer",name));
                ServerConnection::connectedPlayers.push_back(ConnectedPlayer(name,glm::vec3(10,10,10),event.packet->data[2],event.packet->data[1],ServerConnection::app));
            }
        }
    }
    if(ServerConnection::lastActivityResponse+5<time(0)){
        std::cout<<"(Log) [ServerConnection] Disconnected from server: Timed out"<<std::endl;
        ServerConnection::app->setFrame(GAME_MENU_FRAME);
    }
}
void ServerConnection::updateActivity(){
    char* sendData=new char;
    sendData[0]=ServerNetworkCommand::ACTIVITY;
    ServerConnection::send(sendData,1);
    delete sendData;
}
void ServerConnection::sendChatMessage(std::string message){
    char* sendData=(char*)malloc(3+message.length());
    sendData[0]=ServerNetworkCommand::CHAT_MESSAGE;
    short messageLength=message.length();
    sendData[1]=((uint8_t*)&messageLength)[0];
    sendData[2]=((uint8_t*)&messageLength)[1];
    for(int i=0; i<message.length(); i++){
        sendData[3+i]=message[i];
    }
    ServerConnection::send(sendData,3+message.length());
}
void ServerConnection::sendPosition(glm::vec3 position){
    char* sendData=(char*)malloc(1+12);
    sendData[0]=ServerNetworkCommand::MOVE;
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
    ServerConnection::send(sendData,1+12);
    free(sendData);
}
void ServerConnection::disconnect(){
    if(!ServerConnection::connected)
        return;
    char* sendData=(char*)malloc(1);
    sendData[0]=ServerNetworkCommand::EXIT;
    ServerConnection::send(sendData,1);
    free(sendData);
    ServerConnection::connected=false;
}
std::vector<ConnectedPlayer> ServerConnection::getPlayerList(){
    return connectedPlayers;
}
uint8_t ServerConnection::getTeam(){
    return ServerConnection::team;
}