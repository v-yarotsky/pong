cmake_minimum_required(VERSION 3.6)
project(pong)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp
                 texture.h
                 texture.cpp
                 timer.h
                 timer.cpp dot.cpp dot.h CollisionUtils.cpp CollisionUtils.h constants.h Platform.cpp Platform.h)
add_executable(pong ${SOURCE_FILES})

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    ${SDL2_TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}
                      ${SDL2_LIBRARIES}
                      ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_MIXER_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES})

file(COPY "lazy.ttf" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY "dot.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY "platform.png" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

