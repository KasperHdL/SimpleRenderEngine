#pragma once

#include "sre/impl/Export.hpp"

namespace sre {
    // Render stats maintained by SimpleRenderEngine
    struct DllExport RenderStats {
        int frame=0;                                          // The frameid the render stat is captured
        int meshCount=0;                                      // Number of allocated meshes
        int meshBytes=0;                                      // Size of allocated meshes in bytes
        int textureCount=0;                                   // Number of allocated textures
        int textureBytes=0;                                   // Size of allocated textures in bytes
        int shaderCount=0;                                    // Number of allocated shaders
        int drawCalls=0;                                      // Number of drawCalls per frame
        int stateChangesShader=0;                             // Number of state changes for shaders
        int stateChangesMaterial=0;                           // Number of state changes for materials
        int stateChangesMesh=0;                               // Number of state changes for meshes
    };
}
