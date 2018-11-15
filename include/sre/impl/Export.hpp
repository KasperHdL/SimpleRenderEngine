/*
 *  SimpleRenderEngine (https://github.com/mortennobel/SimpleRenderEngine)
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergensen.com/ )
 *  License: MIT
 */

#pragma once

#include "glm/glm.hpp"
#include <vector>

#ifdef _WIN32

#define DECLSPECIFIER __declspec(dllexport)
#ifdef SRE_EXPORT
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif
#define EXPIMP_TEMPLATE

template struct __declspec(dllexport) glm::tvec4<float, glm::precision(0)>;
template struct __declspec(dllexport) glm::tvec3<float, glm::precision(0)>;
template struct __declspec(dllexport) glm::tvec2<float, glm::precision(0)>;
template struct __declspec(dllexport) glm::tmat4x4<float, glm::precision(0)>;
template struct __declspec(dllexport) glm::tmat3x3<float, glm::precision(0)>;

// https://support.microsoft.com/en-us/kb/168958
//disable warnings on 255 char debug symbols
#pragma warning (disable : 4786)
//disable warnings on extern before template instantiation
#pragma warning (disable : 4231)


#else
#define DllExport 
#endif // _WIN32