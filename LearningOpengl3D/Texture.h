#pragma once

class Texture
{
private:
	//. Variables
	GLuint id;
	int width;
	int height;
	GLenum type;
	//. Functions
public:
	//. Constructors-Destructors
	Texture(const char* imageLoc, GLenum type)
	{
		this->type = type;
		unsigned char* image = SOIL_load_image(imageLoc, &this->width, &this->height, NULL, SOIL_LOAD_RGBA);
		glGenTextures(1, &this->id);
		glBindTexture(type, this->id);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT); //s = x 
		glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT); //t = y 
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		if (!image)
			std::cout << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << imageLoc << std::endl;
		else
		{
			glTexImage2D(type, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			glGenerateMipmap(type);
		}
		glActiveTexture(0);
		glBindTexture(type, 0);
		SOIL_free_image_data(image);
	}
	~Texture()
	{
		glDeleteTextures(1, &this->id);
	}
	//. Functions
	inline GLuint getTexture() const { return this->id; }
	void bindTex(const GLuint textureUnit) 
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(this->type, this->id);
	}
	void unbindTex()
	{
		glActiveTexture(0);
		glBindTexture(this->type, 0);
	}
};