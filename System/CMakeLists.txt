CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(sys)

##################################################
#Get files
##################################################
FILE(GLOB_RECURSE SysLibPrv *.h *.cpp *.hpp)

##################################################
#LINK LIBRARIES
##################################################
GET_PROPERTY(PublicSrc GLOBAL PROPERTY SysSRC)
SET(ALLSRC ${PublicSrc} ${SysLibPrv})
SET_PROPERTY(GLOBAL PROPERTY SysSRC ${ALLSRC})