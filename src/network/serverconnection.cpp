#include "serverconnection.hpp"
ServerConnection::ServerConnection(Chat* chat){
    ServerConnection::chat=chat;
}
bool ServerConnection::connect(std::string ip,int port,std::string name){
    ServerConnection::host=enet_host_create(0,1,2,0,0);
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
    if(enet_host_service(host,&event,10000)){
        if(event.type==ENET_EVENT_TYPE_RECEIVE){
            if(event.packet->data[0]==ServerInitializationCommand::PLAYER_DATA){
                //TODO
            }
        }
    }
    if(enet_host_service(host,&event,10000)){
        if(event.type==ENET_EVENT_TYPE_RECEIVE){
            if(event.packet->data[0]==ServerInitializationCommand::MAP_DATA){
                std::vector<unsigned char> mapData;
                mapData.assign(event.packet->data+18,event.packet->data+event.packet->dataLength);
                world->loadMapFromMemory(mapData);
                world->generateMesh(atlas);
            }
        }
    }
}
void ServerConnection::send(char* data,int len){
    ENetPacket* packet=enet_packet_create(data,len,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(socket,0,packet);
    enet_host_flush(host);
    //!!!!
    enet_packet_destroy(packet);
}
void ServerConnection::update(){

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