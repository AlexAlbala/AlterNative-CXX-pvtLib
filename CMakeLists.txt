CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(AlternativeLib CXX)
SET_PROPERTY(GLOBAL PROPERTY GL_IS_RELEASE 1)
ADD_SUBDIRECTORY(System System)
#ADD_SUBDIRECTORY(Microsoft.SPOT Microsoft.SPOT)

SET(CMAKE_BUILD_TYPE Debug)