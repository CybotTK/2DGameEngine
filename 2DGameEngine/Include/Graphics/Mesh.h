#ifndef MESH_H
#define MESH_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec2 position;  // Position (x,y)
	glm::vec2 texCoords; // Texture Coordinates (u, v)
};

class Mesh {
public:
	Mesh();
	virtual ~Mesh();

	//Return the indices size
	int Use();
	void Draw();

	void AddVertex(glm::vec2 position, glm::vec2 texCoords);
	void MakeTriangle(unsigned int v1, unsigned int v2, unsigned int v3);

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices; //for faces
private:
	//OpenGL IDs for buffers and array objects
	GLuint VAO; // Vertex Array Object
	GLuint VBO; // Vertex Buffer Object
	GLuint EBO; // Element buffer Object


};

#endif // MESH_H

