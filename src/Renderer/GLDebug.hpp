#ifndef GL_DEBUG_HPP
#define GL_DEBUG_HPP

#include <string>

#include <GL/gl.h>

#define GL_DEBUG

#ifdef GL_DEBUG
	#define glCheck(call) ((call), glCheckError(__FILE__, __LINE__))
#else
	#define glCheck(call) (call)
#endif

void glCheckError(const std::string& file, unsigned int line);

#endif
