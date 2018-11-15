


if(WIN32)
    string(REPLACE "\\" "/" HOME $ENV{USERPROFILE})
    set(LIBRARY_INSTALL_DIR 
        "${HOME}/Projects/animation_tool/libraries/windows/SRE"
        "${HOME}/Projects/Sidetracked_Engine/libraries/windows/SRE"
    )
    set(INCLUDE_INSTALL_DIR 
        "${HOME}/Projects/animation_tool/libraries/multi/include"
        "${HOME}/Projects/Sidetracked_Engine/libraries/multi/include"
    )
else()
endif()

