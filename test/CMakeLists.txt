# List of single-file tests
SET(scr_files stencil_test benchmark64k-heavy matrix-uniforms custom-mesh-layout-ints multiple-materials render-depth spinning-sphere-cubemap particle-test polygon-offset-example multiple-lights particle-sprite sprite-test multi-cameras static_vertex_attribute custom-mesh-layout-default-values imgui_demo texture-test screen-point-to-ray pbr-test gamma primitives-test imgui-color-test)

# Create custom build targets
FOREACH(scr_file ${scr_files})
    add_executable(SRE-Test-${scr_file} ${scr_file}.cpp)
    target_link_libraries(SRE-Test-${scr_file} ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${OPENVR_LIB} SRE)
ENDFOREACH()

file(COPY ../test_data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ../test_data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)

IF (WIN32)
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
ENDIF(WIN32)
