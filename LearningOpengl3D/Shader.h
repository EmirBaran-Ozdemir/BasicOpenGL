#pragma once

class Shader
{
private:
	//. Variables
	GLuint id; //Program
	const int GLMajorVer;
	const int GLMinorVer;

	//. Functions
	std::string loadShaderSource(char* fileName)
	{
		std::string temp = "";
		std::string src = "";
		std::ifstream in_file;

		//! vertex shader
		in_file.open(fileName);
		if (in_file.is_open())
		{
			while (std::getline(in_file, temp))
			{
				src += temp + "\n";
			}
		}
		else
		{
			std::cout << "ERROR::SHADERS::COULD_NOT_OPEN_FILE " << fileName << std::endl;
		}
		in_file.close();
		setVersion(src);
		return src;
	}
	void setVersion(std::string src)
	{
		std::string version = std::to_string(this->GLMajorVer) + std::to_string(this->GLMinorVer) + "0";
		src.replace(src.find("#version"), 12, ("#version " + version));
	}
	GLuint loadShader(GLenum type, char* fileName)
	{
		char infoLog[512];
		GLint success;

		GLuint shader = glCreateShader(type);
		std::string str_src = this->loadShaderSource(fileName);
		const GLchar* src = str_src.c_str();
		glShaderSource(shader, 1, &src, NULL);
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_COMPILE_SHADER " << fileName << std::endl;
			std::cout << infoLog << std::endl;
		}
		return shader;
	}
	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader)
	{
		char infoLog[512];
		GLint success;

		this->id = glCreateProgram();

		glAttachShader(this->id, vertexShader);
		if (geometryShader)
		{
			glAttachShader(this->id, geometryShader);
		}
		glAttachShader(this->id, fragmentShader);
		glLinkProgram(this->id);
		glGetProgramiv(this->id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(this->id, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::COULD_NOT_LINK_PROGRAM" << std::endl;
			std::cout << infoLog << std::endl;
		}

		//! End

		glUseProgram(0);
	}

public:
	//. Constructor-Destructor
	Shader(
		const int GLMajorVer, const int GLMinorVer,
		char* vertexFile, char* fragmentFile,
		char* geometryFile = (char*)"")
		: GLMajorVer(GLMajorVer), GLMinorVer(GLMinorVer)
	{
		GLuint vertexShader = 0;
		GLuint geometryShader = 0;
		GLuint fragmentShader = 0;

		vertexShader = loadShader(GL_VERTEX_SHADER, vertexFile);
		if (geometryFile != "")
		{
			geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryFile);
		}
		fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentFile);
		this->linkProgram(vertexShader, geometryShader, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(geometryShader);
		glDeleteShader(fragmentShader);
	}
	~Shader()
	{
		glDeleteProgram(this->id);
	}

	//. Functions
	void use()
	{
		glUseProgram(this->id);
	}
	void unuse()
	{
		glUseProgram(0);
	}
	void set1i(GLint value, const GLchar* name)
	{
		glUniform1i(glGetUniformLocation(this->id, name), value);
	}
	void set1f(GLfloat value, const GLchar* name)
	{
		glUniform1f(glGetUniformLocation(this->id, name), value);
	}
	void setVec2f(glm::fvec2 value, const GLchar* name)
	{
		glUniform2fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	}
	void setVec3f(glm::fvec3 value, const GLchar* name)
	{
		glUniform3fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	}
	void setVec4f(glm::fvec4 value, const GLchar* name)
	{
		glUniform4fv(glGetUniformLocation(this->id, name), 1, glm::value_ptr(value));
	}
	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{
		glUniformMatrix3fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
	}
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE)
	{

		glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, transpose, glm::value_ptr(value));
	}
};