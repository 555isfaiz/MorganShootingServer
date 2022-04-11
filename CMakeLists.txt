cmake_minimum_required(VERSION 3.16)
PROJECT(shooting)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")
# SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/include.cmake)

AUX_SOURCE_DIRECTORY(./jni SRC_JNI)
AUX_SOURCE_DIRECTORY(./utils SRC_UTILS)
AUX_SOURCE_DIRECTORY(./game/. SRC_GAME)
AUX_SOURCE_DIRECTORY(./game/physics SRC_PHYSICS)
AUX_SOURCE_DIRECTORY(./game/tasks SRC_TASKS)
AUX_SOURCE_DIRECTORY(./msg SRC_MSG)
AUX_SOURCE_DIRECTORY(./libs/json SRC_JSON)

ADD_LIBRARY(nativeshooting SHARED 
        ${SRC_JNI} 
        ${SRC_UTILS} 
        ${SRC_GAME}
        ${SRC_PHYSICS}
        ${SRC_TASKS}
        ${SRC_MSG}
        ${SRC_JSON}
        )

target_link_libraries(nativeshooting
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/BulletDynamics/libBulletDynamics.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/BulletCollision/libBulletCollision.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/LinearMath/libLinearMath.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/Bullet3Collision/libBullet3Collision.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/Bullet3Common/libBullet3Common.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/Bullet3Dynamics/libBullet3Dynamics.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/Bullet3Geometry/libBullet3Geometry.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/Bullet3OpenCL/libBullet3OpenCL_clew.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/Bullet3Serialize/Bullet2FileLoader/libBullet2FileLoader.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/BulletInverseDynamics/libBulletInverseDynamics.a
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/bullet3/src/BulletSoftBody/libBulletSoftBody.a
        )


