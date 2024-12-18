    cmake_minimum_required(VERSION 3.30)
    project(Breakout)

    set(CMAKE_CXX_STANDARD 20)
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 3.0.0-rc.2
            GIT_SHALLOW ON
            EXCLUDE_FROM_ALL
            SYSTEM)
    FetchContent_MakeAvailable(SFML)

    add_executable(Breakout src/main.cpp
            src/Game.cpp
            src/Game.h
            src/Window.cpp
            src/Window.h
            src/Level.cpp
            src/Level.h
            src/GameMap.cpp
            src/GameMap.h
            src/Paddle.cpp
            src/Paddle.h
            src/Ball.cpp
            src/Ball.h
            src/Brick.cpp
            src/Brick.h
            include/Constants.h)

    target_link_libraries(Breakout PRIVATE sfml-graphics)
    target_compile_features(Breakout PRIVATE cxx_std_17)

    if(WIN32)
        set(OPENAL_DLL "${CMAKE_BINARY_DIR}/_deps/sfml-src/extlibs/bin/x64/openal32.dll")
        if(EXISTS "${OPENAL_DLL}")
            add_custom_command(
                    TARGET Breakout POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy "${OPENAL_DLL}" "${CMAKE_BINARY_DIR}"
            )
        endif()
    endif()