#ifndef SRC_RENDER_MODEL_HPP
#define SRC_RENDER_MODEL_HPP
#include <glm/glm.hpp>
#include <vector>
#include "shaderprogram.hpp"
#include "camera.hpp"
struct Mesh{
	unsigned int VAO,VBO,TBO,EBO;
};
class Model{
	glm::vec3 position,scale;
	glm::mat4 transformation;
	float pitch,yaw,roll;
	Mesh mesh;
	unsigned int indicesCount;
	void generateTransform();
public:
	Model();
	Model(std::vector<float> verts,std::vector<float> uvs,std::vector<int> indices);
	void translate(glm::vec3 pos);
	void rotate(float pitch,float yaw,float roll);
	void setScale(glm::vec3 scale);
	void draw(ShaderProgram program,Camera cam,unsigned int mode);
};
#endif
