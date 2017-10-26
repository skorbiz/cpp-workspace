# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project.
PROJECT(openMP_HelloWorld)
MESSAGE(${PROJECT_NAME})

#Uses the 2011 version of C
add_definitions(-std=c++0x)

#Includes openMP in the project
find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

# Used to resolve absolute path names
SET(ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Verbose mode prints more info when doing make
set(CMAKE_VERBOSE_MAKEFILE false)

# Set paths
# SET(RW_ROOT $ENV{RW_ROOT})

# We use the settings that robwork studio uses
IF( NOT DEFINED CMAKE_BUILD_TYPE )
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

#Use RobWork
#SET(RobWork_DIR ${RW_ROOT}/cmake) 
#FIND_PACKAGE(RobWork REQUIRED)

#INCLUDE_DIRECTORIES( ${ROBWORK_INCLUDE_DIRS} )
#LINK_DIRECTORIES( ${ROBWORK_LIBRARY_DIRS} )

# Set the output dir for generated libraries and binaries
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ROOT}/../bin/${CMAKE_BUILD_TYPE}" CACHE PATH "Runtime directory" FORCE)
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ROOT}/../libs/${CMAKE_BUILD_TYPE}" CACHE PATH "Library directory" FORCE)
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${ROOT}/../libs/${CMAKE_BUILD_TYPE}" CACHE PATH "Archive directory" FORCE)

ADD_EXECUTABLE(program main)
#TARGET_LINK_LIBRARIES(collisiondetection ${ROBWORK_LIBRARIES})