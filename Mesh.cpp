#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& texture)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::texture = texture;

	vao.Bind();

	VBO VBO(vertices);
	EBO EBO(indices);

	vao.LinkAttrib(VBO, 0, 3, GL_FLOAT, 12 * sizeof(float), (void*)0);
	vao.LinkAttrib(VBO, 1, 4, GL_FLOAT, 12 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(VBO, 2, 2, GL_FLOAT, 12 * sizeof(float), (void*)(7 * sizeof(float)));
	vao.LinkAttrib(VBO, 3, 3, GL_FLOAT, 12 * sizeof(float), (void*)(9 * sizeof(float)));
	vao.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, Camera& camera)
{
	shader.Activate();
	vao.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;

	for (unsigned int i = 0; i < texture.size(); i++)
	{
		std::string num;
		std::string type = texture[i].type;

		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular")
		{
			num = std::to_string(numSpecular++);
		}

		texture[i].texUnit(shader, (type + num).c_str(), i);
		texture[i].Bind();
	}

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, 
		camera.Position.y, camera.Position.z);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}