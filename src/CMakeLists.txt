file(GLOB SOURCE_FILES
	"sre/*.cpp"
	"sre/impl/*.cpp"
	"../include/sre/*.hpp"
	"../include/sre/impl/*.hpp"
    "imgui/*.cpp"
)

include_directories(.)

add_library(SRE SHARED ${SOURCE_FILES})
target_link_libraries(SRE ${EXTRA_LIBS} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES})

if(WIN32)
	if(LIBRARY_INSTALL_DIR)
	if(INCLUDE_INSTALL_DIR)
		foreach(dir ${LIBRARY_INSTALL_DIR})
			message(${dir})	
			install(TARGETS SRE 
				LIBRARY DESTINATION ${dir}
				ARCHIVE DESTINATION ${dir}
				RUNTIME DESTINATION ${dir}
			)

			install(
				FILES 
					${CMAKE_BINARY_DIR}/src/SRE.exp
					${CMAKE_BINARY_DIR}/src/SRE.ilk
					${CMAKE_BINARY_DIR}/src/SRE.pdb
				DESTINATION ${dir} OPTIONAL
			)

		endforeach() 
		foreach(dir ${INCLUDE_INSTALL_DIR})
			message(${dir})	
			install(DIRECTORY ${CMAKE_SOURCE_DIR}/include DESTINATION ${dir})
		endforeach()
	endif()   
	endif()
else()
	install(TARGETS SRE DESTINATION lib)
	install(DIRECTORY ../include/ DESTINATION include)
endif()