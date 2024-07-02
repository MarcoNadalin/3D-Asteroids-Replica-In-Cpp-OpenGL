#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#if _WIN32
# include <windows.h>
#endif
#if __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

namespace assetloader {

	uint32_t loadTexture(const char* file_location);

	uint32_t loadTextureEdgeClamp(const char* file_location);

	void setFlipVerticallyOnLoad(bool flip);

}

#endif