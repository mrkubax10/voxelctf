#ifndef SRC_FRAMES_GAMEFRAME_HPP
#define SRC_FRAMES_GAMEFRAME_HPP
#include "../framework/frame.hpp"
#include "../world/world.hpp"
#include "../gameplay/player.hpp"
#include "../render/fpscamera.hpp"
#include "../render/model.hpp"
#include "../network/chat.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameFrame : public Frame{
    FPSCamera* cam;
    Player* player;
    World* world;
    Model* playerModel;
    SDL_TimerID activityTimer,moveTimer;
    glm::vec3 lastPosition;
public:
    void begin();
    void render();
    void finish();
};
#endif