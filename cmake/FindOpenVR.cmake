message("-- OpenVR")
 
if(WIN32)
    SET(OPENVR_LIBRARY "${PLATFORM_PATHS}/openvr/${PLATFORM_ARCH}/openvr_api.${LIBRARY_EXTENSION}")
else()
    SET(OPENVR_LIBRARY "${PLATFORM_PATHS}/openvr/${PLATFORM_ARCH}/libopenvr_api.${LIBRARY_EXTENSION}")
endif()

set(OPENVR_INCLUDE_DIR ${CROSS_PLATFORM_PATHS}/openvr/headers)
