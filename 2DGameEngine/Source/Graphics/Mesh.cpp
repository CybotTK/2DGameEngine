#include "Graphics/Mesh.h"

Mesh::Mesh(const Mesh& other){
	this->vertices = other.vertices;
	this->faces = other.faces;
}

int Mesh::Use(){
	return 0;
}

void Mesh::Draw(){
}

void Mesh::AddVertex(glm::vec2 position, glm::vec2 texCoords){
	vertices.push_back({ position, texCoords });
}

void Mesh::MakeTriangle(unsigned int v1, unsigned int v2, unsigned int v3){
	faces.push_back({ v1,v2,v3 });
}
