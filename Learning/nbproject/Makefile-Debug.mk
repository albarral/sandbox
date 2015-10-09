#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/GameState.o \
	${OBJECTDIR}/src/LearnPlayer.o \
	${OBJECTDIR}/src/Nav/Connection.o \
	${OBJECTDIR}/src/Nav/ConnectionType.o \
	${OBJECTDIR}/src/Nav/Environment.o \
	${OBJECTDIR}/src/Nav/LearnNav.o \
	${OBJECTDIR}/src/Nav/Place.o \
	${OBJECTDIR}/src/RewardCalculator.o \
	${OBJECTDIR}/src/State.o \
	${OBJECTDIR}/src/Task.o \
	${OBJECTDIR}/src/Transition.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-Wl,-rpath,../samUtils/dist/Debug/GNU-Linux-x86 -L../samUtils/dist/Debug/GNU-Linux-x86 -lsam_utils -lmysqlcppconn -lopencv_core

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}: ../samUtils/dist/Debug/GNU-Linux-x86/libsam_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/GameState.o: src/GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameState.o src/GameState.cpp

${OBJECTDIR}/src/LearnPlayer.o: src/LearnPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/LearnPlayer.o src/LearnPlayer.cpp

${OBJECTDIR}/src/Nav/Connection.o: src/Nav/Connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Nav/Connection.o src/Nav/Connection.cpp

${OBJECTDIR}/src/Nav/ConnectionType.o: src/Nav/ConnectionType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Nav/ConnectionType.o src/Nav/ConnectionType.cpp

${OBJECTDIR}/src/Nav/Environment.o: src/Nav/Environment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Nav/Environment.o src/Nav/Environment.cpp

${OBJECTDIR}/src/Nav/LearnNav.o: src/Nav/LearnNav.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Nav/LearnNav.o src/Nav/LearnNav.cpp

${OBJECTDIR}/src/Nav/Place.o: src/Nav/Place.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/Nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Nav/Place.o src/Nav/Place.cpp

${OBJECTDIR}/src/RewardCalculator.o: src/RewardCalculator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/RewardCalculator.o src/RewardCalculator.cpp

${OBJECTDIR}/src/State.o: src/State.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/State.o src/State.cpp

${OBJECTDIR}/src/Task.o: src/Task.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Task.o src/Task.cpp

${OBJECTDIR}/src/Transition.o: src/Transition.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Transition.o src/Transition.cpp

# Subprojects
.build-subprojects:
	cd ../samUtils && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../samUtils && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
