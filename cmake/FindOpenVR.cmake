message("-- OpenVR")
 
if(WIN32)
    #add_definitions(-DVR_API_EXPORT)
    
    SET(OPENVR_LIBRARY 
        #"${PLATFORM_PATHS}/openvr/${PLATFORM_ARCH}/openvr_api.dll"
        "${PLATFORM_PATHS}/openvr/${PLATFORM_ARCH}/openvr_api.lib"
    )
else()
    SET(OPENVR_LIBRARY "${PLATFORM_PATHS}/openvr/${PLATFORM_ARCH}/libopenvr_api.so")
endif()

set(OPENVR_INCLUDE_DIR ${CROSS_PLATFORM_PATHS}/openvr/headers)
