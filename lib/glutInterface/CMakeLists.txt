cmake_minimum_required(VERSION 3.12)

project(glutInterface)

set(CMAKE_CXX_STANDARD 14)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()


IF (WIN32)
    message(STATUS ">>> Win32")
    add_compile_definitions(USE_FREEGLUT)
    set(GLUT_DIR F:/freeglut-3.0.0)
    set(CMAKE_PREFIX_PATH FREEGLUT)

    set(FREEGLUT_INCLUDE_DIRS F:/freeglut-3.0.0/include)
    set(FREEGLUT_LIBRARY_DIRS F:/freeglut-3.0.0/cmake-build-debug/lib)
    set(FREEGLUT_LIBRARIES freeglutd.lib)

    find_package(OPENGL REQUIRED)

    include_directories(${FREEGLUT_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS})
    link_directories(${FREEGLUT_LIBRARY_DIRS} ${OPENGL_LIBRARY_DIRS})

    add_library(glutInterface glutWindow.cpp glutWindow.h)
ENDIF (WIN32)

IF(LINUX)
    message(STATUS ">>> Linux")
    add_compile_definitions(USE_FREEGLUT)

    SET(GLUT_INCLUDE_DIR /usr/include)
    SET(GLUT_glut_LIBRARY /usr/lib/x86_64-linux-gnu/libglut.so)

    # GLUT
    #########################################################
    # FIND GLUT
    #########################################################
    find_package(GLUT REQUIRED)
    #include_directories(${GLUT_INCLUDE_DIRS})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    if(NOT GLUT_FOUND)
        message(ERROR " GLUT not found!")
    endif(NOT GLUT_FOUND)

    # OpenGL
    find_package(OpenGL REQUIRED)

    include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )

    add_library(glutInterface SHARED glutWindow.cpp glutWindow.h)
ENDIF(LINUX)

IF (APPLE)
    message(STATUS ">>> APPLE")

    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
    add_library(glutInterface SHARED glutWindow.cpp glutWindow.h)
ENDIF(APPLE)

add_definitions(${FREEGLUT_DEFINITIONS} ${OPENGL_DEFINITIONS})

#add_executable(glutInterface main.cpp glutWindow.cpp glutWindow.h)
target_link_libraries(glutInterface ${FREEGLUT_LIBRARIES} ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})
