#include "AssetLoader.h"

#define GL_CLAMP_TO_EDGE 0x812F

#define STB_IMAGE_IMPLEMENTATION
#include "../Graphics/stb_image.h"


uint32_t assetloader::loadTexture(const char* file_location)
{
	int width, height, components;
	unsigned char* data = stbi_load(file_location, &width, &height, &components, STBI_rgb);

	unsigned int id;
	glPushAttrib(GL_TEXTURE_BIT);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glPopAttrib();

	if (!id) {
		printf("The texture: %s could not be found!", file_location);
	}

	return id;
}

uint32_t assetloader::loadTextureEdgeClamp(const char* file_location)
{
	int width, height, components;
	unsigned char* data = stbi_load(file_location, &width, &height, &components, STBI_rgb);

	unsigned int id;
	glPushAttrib(GL_TEXTURE_BIT);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glPopAttrib();

	if (!id) {
		printf("The texture: %s could not be found!", file_location);
	}

	return id;
}

void assetloader::setFlipVerticallyOnLoad(bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
}
