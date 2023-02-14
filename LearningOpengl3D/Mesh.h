#pragma once

class Mesh
{
private:
	//. Variables
	unsigned nrOfVertices;
	unsigned nrOfIndices;

	GLuint VAO, VBO, EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 modelMatrix;

	//. Funcitons
	void initVAO(
		Primitive* primitive)
	{
		//! Set variables
		this->nrOfVertices = primitive->getNrOfVertices();
		this->nrOfIndices = primitive->getNrOfIndices();


		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW);
		if (this->nrOfIndices)
		{
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);
		}
		//! Set lenght for 1 set of information (input assembly)
		// vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		// color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		// texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		// normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);
	}
	void initVAO(
		Vertex* vertexArray, const unsigned& nrOfVertices,
		GLuint* indexArray, const unsigned& nrOfIndices)
	{
		//! Set variables
		this->nrOfVertices = nrOfVertices;
		this->nrOfIndices = nrOfIndices;


		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices * sizeof(Vertex), vertexArray, GL_STATIC_DRAW);
		if (this->nrOfIndices)
		{
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices * sizeof(GLuint), indexArray, GL_STATIC_DRAW);

		}

		//! Set lenght for 1 set of information (input assembly)
		// vertex
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		// color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		// texcoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);
		// normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);
	}
	void updateUniforms(Shader* shader)
	{
		shader->setMat4fv(this->modelMatrix, "modelMatrix");
	}
	void updateModelMatrix()
	{
		this->modelMatrix = glm::mat4(1.f);
		this->modelMatrix = glm::translate(this->modelMatrix, this->position); //move
		this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.f, 0.f, 0.f));	//x
		this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.f, 1.f, 0.f));	//y
		this->modelMatrix = glm::rotate(this->modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.f, 0.f, 1.f));	//z
		this->modelMatrix = glm::scale(this->modelMatrix, this->scale);
	}

public:
	//. Constructor-Destructor
	Mesh(
		Vertex* vertexArray, const unsigned& nrOfVertices,
		GLuint* indexArray, const unsigned& nrOfIndices,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		this->updateModelMatrix();
	}
	Mesh(
		Primitive* primitive,
		glm::vec3 position = glm::vec3(0.f),
		glm::vec3 rotation = glm::vec3(0.f),
		glm::vec3 scale = glm::vec3(1.f))
	{
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;
		this->initVAO(primitive);
		this->updateModelMatrix();
	}
	~Mesh()
	{
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		if (this->nrOfIndices)
		{
			glDeleteBuffers(1, &this->EBO);
		}
	}

	//. Modifiers
	void setPosition(const glm::vec3 position)
	{
		this->position = position;
	}
	void setRotation(const glm::vec3 rotation)
	{
		this->rotation = rotation;
	}
	void setScale(const glm::vec3 scale)
	{
		this->scale = scale;
	}
	//. Functions
	void move(const glm::vec3 position)
	{
		this->position += position;
	}
	void rotate(const glm::vec3 rotation)
	{
		this->rotation += rotation;

	}
	void scaleUp(const glm::vec3 scale)
	{
		this->scale += scale;
	}

	void render(Shader* shader)
	{
		this->updateModelMatrix();
		this->updateUniforms(shader);
		glBindVertexArray(this->VAO);
		shader->use();
		if (!this->nrOfIndices)
		{
			glDrawArrays(GL_TRIANGLES, 0, this->nrOfIndices);
		}
		else
			glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
	}
};