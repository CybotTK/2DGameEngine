#include "Graphics/Mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh& other) {
	this->vertices = other.vertices;
	this->faces    = other.faces;
}

Mesh::~Mesh() {
	Reset(true);
}

Mesh* Mesh::CreatePlane() {
	Mesh* out = new Mesh();

	for (int i = 0; i < 4; i++) {
		int x = i % 2;
		int y = (i / 2) % 2;
		out->AddVertex(glm::vec2(x * 2 - 1, y * 2 - 1), glm::vec2(x, y));
	}
	out->faces = { {0,1,2}, {2,1,3} };

	out->BindMeshBuffersData();
	return out;
}

void Mesh::BindMeshBuffersData() {
	assert(!alreadySentToGPU);
	alreadySentToGPU = true;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	//Creating Vertex Buffer Array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	if (vertices.size() > 0) {
		glBufferData(GL_ARRAY_BUFFER,
			vertices.size() * sizeof(Vertex),
			&vertices[0], GL_STATIC_DRAW
		);
	}
	else {
		// If there are no vertices, we need to send at least one to avoid a crash
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	}

	//Creating Element Buffer Object (for face indices)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	if (faces.size() > 0) {
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			GetNumIndices() * sizeof(unsigned int),
			&faces[0], GL_STATIC_DRAW
		);
	}
	else {
		// If there are no faces, we need to send at least one to avoid a crash
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
	}

	//Mapping the vertex attributes (Elements)
	{
		// glm::vec2 Position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		// glm::vec2 Texture attribute uv
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
	}

	//glBindVertexArray(0); // We unbind the VAO, maybe we use it later

}

void Mesh::Reset(bool resetData) {
	Use();

	if (alreadySentToGPU) {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
		alreadySentToGPU = false;
	}

	if (resetData) {
		vertices.clear();
		faces.clear();
	}
}

void Mesh::Reload() {
	Reset(false);
	BindMeshBuffersData();
}

void Mesh::Use() {
	if (!alreadySentToGPU) {
		glBindVertexArray(VAO);
	}
}

void Mesh::Draw() {
	assert(alreadySentToGPU); 
	glDrawElements(GL_TRIANGLES, (unsigned int)GetNumIndices(), GL_UNSIGNED_INT, 0);
}

void Mesh::AddVertex(glm::vec2 position, glm::vec2 texCoords) {
	vertices.push_back({ position, texCoords });
}

void Mesh::MakeTriangle(unsigned int v1, unsigned int v2, unsigned int v3) {
	faces.push_back({ v1,v2,v3 });
}

size_t Mesh::GetNumIndices() {
	return faces.size() * 3;
}