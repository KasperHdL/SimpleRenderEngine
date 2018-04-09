/*
 *  SimpleRenderEngine (https://github.com/mortennobel/SimpleRenderEngine)
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergensen.com/ )
 *  License: MIT
 */

#pragma once

/// Include GL header

#if defined(EMSCRIPTEN)
#   include <GLES3/gl3.h>
#elif defined(_WIN32)
#   define GLEW_STATIC
#   include <GL/glew.h>
#elif defined __linux__
#   define GLEW_STATIC
#   include <GL/glew.h>
#else
#   include  <OpenGL/gl3.h>
#endif
#include <string>
#include <vector>

// For internal debugging of gl errors
inline void checkGLError(const char* title = nullptr);

inline bool hasExtension(std::string extensionName);
inline std::vector<std::string> listExtension();

inline bool has_sRGB();

#include "GL.inl"
