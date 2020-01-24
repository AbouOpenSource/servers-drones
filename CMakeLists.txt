cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_NAME DroneProject)

file(GLOB_RECURSE PROJECT_FILES "*.cpp" "*.hpp" "*.tcc")
list(FILTER PROJECT_FILES EXCLUDE REGEX "(.CompilerId.cpp$|glut)")

project(${PROJECT_NAME})

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

IF (WIN32)

    message(STATUS ">>> Win32")
    add_compile_definitions(USE_FREEGLUT)
    set(GLUT_DIR "C:/Program Files (x86)/freeglut-3.0.0")
    set(GLUT_INTERFACE_DIRS lib/glutInterface)
    set(GLUT_INTERFACE_LIB_DIRS lib/glutInterface/cmake-build-debug/)
    set(CMAKE_PREFIX_PATH FREEGLUT)

    set(FREEGLUT_INCLUDE_DIRS "C:/Program Files (x86)/freeglut-3.0.0/include")
    set(FREEGLUT_LIBRARY_DIRS "C:/Program Files (x86)/freeglut-3.0.0/cmake-build-debug/lib")
    set(FREEGLUT_LIBRARIES libfreeglut.dll.a)

    find_package(OPENGL REQUIRED)

    include_directories(${FREEGLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLUT_INTERFACE_DIRS})
    link_directories(${FREEGLUT_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS} ${GLUT_INTERFACE_LIB_DIRS})
    add_definitions(${FREEGLUT_DEFINITIONS} ${OPENGL_DEFINITIONS})
    add_executable(${PROJECT_NAME} ${PROJECT_FILES})
    target_link_libraries(${PROJECT_NAME} glutInterface.a ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
ENDIF (WIN32)

IF(LINUX)
    message(STATUS ">>> LINUX")
    add_compile_definitions(USE_FREEGLUT)

    SET(GLUT_INCLUDE_DIR /usr/include)
    SET(GLUT_glut_LIBRARY /usr/lib/x86_64-linux-gnu/libglut.so)
    set(GLUT_INTERFACE_DIRS lib/glutInterface)
    set(GLUT_INTERFACE_LIB_DIRS lib/glutInterface/cmake-build-debug/)

    find_package(GLUT REQUIRED)
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    if(NOT GLUT_FOUND)
        message(ERROR " GLUT not found!")
    endif(NOT GLUT_FOUND)

    find_package(OpenGL REQUIRED)

    include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLUT_INTERFACE_DIRS} )
    link_directories(${FREEGLUT_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS} ${GLUT_INTERFACE_LIB_DIRS})
    add_definitions(${FREEGLUT_DEFINITIONS} ${OPENGL_DEFINITIONS})
    add_executable(${PROJECT_NAME} ${PROJECT_FILES})
    target_link_libraries(${PROJECT_NAME} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} libglutInterface.so)
ENDIF(LINUX)

IF (APPLE)
    message(STATUS ">>> APPLE")
    set(GLUT_INTERFACE_DIRS lib/glutInterface)
    set(GLUT_INTERFACE_LIB_DIRS lib/glutInterface/cmake-build-debug/)

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ${GLUT_INTERFACE_DIRS})
    link_directories(${OPENGL_LIBRARY_DIRS} ${GLUT_INTERFACE_LIB_DIRS})
    add_executable(${PROJECT_NAME} ${PROJECT_FILES} src/controller/CollisionController.cpp src/controller/CollisionController.hpp src/controller/DirectionController.cpp src/controller/DirectionController.hpp)
    target_link_libraries(${PROJECT_NAME} ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} libglutInterface.dylib)
ENDIF(APPLE)
