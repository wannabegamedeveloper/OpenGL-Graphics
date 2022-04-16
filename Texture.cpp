#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;	
	int widthImg, heightImg, colorChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("samurai-_-wallpaper.jpg", &widthImg, &heightImg, &colorChannels, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	float flatColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(texType, GL_TEXTURE_BORDER_COLOR, flatColor);

	glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUni(Shader shader, const char* uniform, GLuint unit)
{
	GLuint tex = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(tex, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}