#ifndef SRC_EDITOR_EDITORMARKER_HPP
#define SRC_EDITOR_EDITORMARKER_HPP
#include "../render/model.hpp"
class EditorMarker{
    Model model;
    Camera* cam;
public:
    EditorMarker(Camera* cam);
    void update();
};
#endif