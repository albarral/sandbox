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
	${OBJECTDIR}/src/RewardCalculator.o \
	${OBJECTDIR}/src/State.o \
	${OBJECTDIR}/src/Task.o \
	${OBJECTDIR}/src/Transition.o \
	${OBJECTDIR}/src/nav/Connection.o \
	${OBJECTDIR}/src/nav/ConnectionType.o \
	${OBJECTDIR}/src/nav/Environment.o \
	${OBJECTDIR}/src/nav/LearnNav.o \
	${OBJECTDIR}/src/nav/Place.o


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

${OBJECTDIR}/src/nav/Connection.o: src/nav/Connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/Connection.o src/nav/Connection.cpp

${OBJECTDIR}/src/nav/ConnectionType.o: src/nav/ConnectionType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/ConnectionType.o src/nav/ConnectionType.cpp

${OBJECTDIR}/src/nav/Environment.o: src/nav/Environment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/Environment.o src/nav/Environment.cpp

${OBJECTDIR}/src/nav/LearnNav.o: src/nav/LearnNav.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/LearnNav.o src/nav/LearnNav.cpp

${OBJECTDIR}/src/nav/Place.o: src/nav/Place.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../samUtils/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/Place.o src/nav/Place.cpp

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
