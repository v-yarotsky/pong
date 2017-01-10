CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(pong)

SET(MACOSX_BUNDLE_BUNDLE_NAME Pong)

SET(CMAKE_CXX_STANDARD 14)

SET(SOURCE_FILES main.cpp
                 texture.h
                 texture.cpp
                 timer.h
                 timer.cpp dot.cpp dot.h CollisionUtils.cpp CollisionUtils.h constants.h Platform.cpp Platform.h Collider.cpp Collider.h Particle.cpp Particle.h DotWithParticles.cpp DotWithParticles.h TextureMap.h)

SET(RESOURCE_FILES lazy.ttf
                   dot.png
                   platform.png
                   red.bmp
                   green.bmp
                   blue.bmp
                   shimmer.bmp
                   flush.wav)

ADD_EXECUTABLE(Pong MACOSX_BUNDLE ${SOURCE_FILES} ${RESOURCE_FILES})
SET_TARGET_PROPERTIES(Pong PROPERTIES
                      MACOSX_BUNDLE TRUE
                      RESOURCE "${RESOURCE_FILES}")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image)
PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS}
                    ${SDL2_MIXER_INCLUDE_DIRS}
                    ${SDL2_TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(Pong
                      ${SDL2_LIBRARIES}
                      ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_MIXER_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES})

INSTALL(CODE "
    set(BU_CHMOD_BUNDLE_ITEMS ON)
    include(BundleUtilities)
    fixup_bundle(${CMAKE_BINARY_DIR}/Pong.app \"\" \"\")

" Runtime)
