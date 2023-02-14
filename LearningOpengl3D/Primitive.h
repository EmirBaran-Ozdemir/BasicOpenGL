#pragma once

class Primitive
{
private:
	//. Variables
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	//. Functions

public:
	//. Constructor-Destructor
	Primitive() {}
	virtual ~Primitive() {}

	//. Functions
	void set(
		const Vertex* vertices, const unsigned nrOfVertices,
		const GLuint* indices, const unsigned nrOfIndices)
	{
		for (size_t i = 0; i < nrOfVertices; i++)
		{
			this->vertices.push_back(vertices[i]);
		}
		for (size_t i = 0; i < nrOfIndices; i++)
		{
			this->indices.push_back(indices[i]);
		}
	}
	inline Vertex* getVertices() { return this->vertices.data(); }
	inline GLuint* getIndices() { return this->indices.data(); }
	inline const unsigned getNrOfVertices() { return this->vertices.size(); }
	inline const unsigned getNrOfIndices() { return this->indices.size(); }
};

class Quad : public Primitive
{
public:
	Quad() :Primitive()
	{
		Vertex vertices[] =
		{
			//Positions						//Colors						//Texcoords				//Normals
			glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.0f,0.f,0.f),	glm::vec2(0.f,1.0f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f, -0.5f, 0.f),	glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f,0.5f,0.0f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(1.f,1.f),		glm::vec3(0.f,0.f,1.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);

		GLuint indices[] =
		{
			0,1,2,
			0,2,3
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

class Triangle : public Primitive
{
public:
	Triangle() :Primitive()
	{
		Vertex vertices[] =
		{
			//Positions						//Colors						//Texcoords				//Normals
			glm::vec3(-0.5f, 0.5f, 0.f),	glm::vec3(1.0f,0.f,0.f),	glm::vec2(1.f,1.0f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(0.5f, -0.5f, 0.f),	glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(-0.5f, -0.5f, 0.f),	glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,1.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
		GLuint indices[] =
		{
			0,1,2
		};
		unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
		this->set(vertices, nrOfVertices, indices, nrOfIndices);

	}
};

class Cube :public Primitive
{
public:
	Cube(glm::vec3 location) :Primitive()
	{
		float x = location.x;
		float y = location.y;
		float z = location.z;

		
		Vertex vertices[] =
		{
			//Positions								//Colors						//Texcoords				//Normals
			//! Front
			glm::vec3(x-0.5f,y+0.5f,z+0.5f),		glm::vec3(1.0f,0.f,0.f),	glm::vec2(0.f,1.0f),	glm::vec3(0.f,0.f,1.f),
			glm::vec3(x-0.5f,y-0.5f,z+0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(x+0.5f,y-0.5f,z+0.5f),		glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,1.f),
			glm::vec3(x+0.5f,y+0.5f,z+0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(1.f,1.f),		glm::vec3(0.f,0.f,1.f),
			//! Back
			glm::vec3(x-0.5f,y+0.5f,z-0.5f),		glm::vec3(1.0f,0.f,0.f),	glm::vec2(0.f,1.0f),	glm::vec3(0.f,0.f,-1.f),
			glm::vec3(x-0.5f,y-0.5f,z-0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(x+0.5f,y-0.5f,z-0.5f),		glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(0.f,0.f,-1.f),
			glm::vec3(x+0.5f,y+0.5f,z-0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(1.f,1.f),		glm::vec3(0.f,0.f,-1.f),
			//! Left
			glm::vec3(x-0.5f,y-0.5f,z+0.5f),		glm::vec3(1.0f,0.f,0.f),	glm::vec2(0.f,1.0f),	glm::vec3(-1.f,0.f,0.f),
			glm::vec3(x-0.5f,y-0.5f,z-0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(x-0.5f,y+0.5f,z-0.5f),		glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(-1.f,0.f,0.f),
			glm::vec3(x-0.5f,y+0.5f,z+0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(1.f,1.f),		glm::vec3(-1.f,0.f,0.f),
			//! Right
			glm::vec3(x+0.5f,y-0.5f,z+0.5f),		glm::vec3(1.0f,0.f,0.f),	glm::vec2(0.f,1.0f),	glm::vec3(1.f,0.f,0.f),
			glm::vec3(x+0.5f,y-0.5f,z-0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(x+0.5f,y+0.5f,z-0.5f),		glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(1.f,0.f,0.f),
			glm::vec3(x+0.5f,y+0.5f,z+0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(1.f,1.f),		glm::vec3(1.f,0.f,0.f),
			//! Top
			glm::vec3(x-0.5f,y+0.5f,z+0.5f),		glm::vec3(1.0f,0.f,0.f),	glm::vec2(0.f,1.0f),	glm::vec3(0.f,1.f,0.f),
			glm::vec3(x-0.5f,y+0.5f,z-0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(0.f,1.f,0.f),
			glm::vec3(x+0.5f,y+0.5f,z-0.5f),		glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(0.f,1.f,0.f),
			glm::vec3(x+0.5f,y+0.5f,z+0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(1.f,1.f),		glm::vec3(0.f,1.f,0.f),
			//! Bottom
			glm::vec3(x-0.5f,y-0.5f,z+0.5f),		glm::vec3(1.0f,0.f,0.f),	glm::vec2(0.f,1.0f),	glm::vec3(0.f,-1.f,0.f),
			glm::vec3(x-0.5f,y-0.5f,z-0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(0.f,0.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(x+0.5f,y-0.5f,z-0.5f),		glm::vec3(0.0f,0.f,1.f),	glm::vec2(1.f,0.f),		glm::vec3(0.f,-1.f,0.f),
			glm::vec3(x+0.5f,y-0.5f,z+0.5f),		glm::vec3(0.0f,1.f,0.f),	glm::vec2(1.f,1.f),		glm::vec3(0.f,-1.f,0.f)
		};
		unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
		int sizeIndices = 6 * (nrOfVertices / 4);
		GLuint* indices = new GLuint[sizeIndices];
		
		
		int offset = 0;
		GLuint defaultFace[] =
		{
			0,1,2,
			0,2,3
		};
		for (int i = 0; i <= (nrOfVertices / 4); i++)
		{
			for (int j = 0; j < (sizeof(defaultFace) / sizeof(GLuint)); j++)
			{
				indices[(sizeof(defaultFace) / sizeof(GLuint)) * i + j] = defaultFace[j] + offset;
			}
			offset += 4;
		}
		unsigned nrOfIndices = sizeIndices / sizeof(GLuint);
		this->set(vertices, nrOfVertices, indices, sizeIndices);
		
	}
};