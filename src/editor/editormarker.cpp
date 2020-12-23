#include "editormarker.hpp"
EditorMarker::EditorMarker(Camera* cam){
    EditorMarker::cam=cam;
    std::vector<float> verts={
        0.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,1.0f,1.0f,
        1.0f,1.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        1.0f,1.0f,1.0f,
        0.0f,0.0f,1.0f,
        1.0f,0.0f,1.0f,
        1.0f,0.0f,0.0f,
        0.0f,0.0f,0.0f
    };
}