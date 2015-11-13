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
CND_PLATFORM=GNU-Linux
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
	${OBJECTDIR}/src/sam/player/AppPlayer.o \
	${OBJECTDIR}/src/sam/player/bus/Bus.o \
	${OBJECTDIR}/src/sam/player/bus/BusCO.o \
	${OBJECTDIR}/src/sam/player/bus/BusSO.o \
	${OBJECTDIR}/src/sam/player/data/BoardLine.o \
	${OBJECTDIR}/src/sam/player/data/PlayerMode.o \
	${OBJECTDIR}/src/sam/player/main.o \
	${OBJECTDIR}/src/sam/player/modules/analyse/LineAnalyser.o \
	${OBJECTDIR}/src/sam/player/utils/module2.o


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
LDLIBSOPTIONS=-llog4cxx

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/sam/player/AppPlayer.o: src/sam/player/AppPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/AppPlayer.o src/sam/player/AppPlayer.cpp

${OBJECTDIR}/src/sam/player/bus/Bus.o: src/sam/player/bus/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/bus/Bus.o src/sam/player/bus/Bus.cpp

${OBJECTDIR}/src/sam/player/bus/BusCO.o: src/sam/player/bus/BusCO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/bus/BusCO.o src/sam/player/bus/BusCO.cpp

${OBJECTDIR}/src/sam/player/bus/BusSO.o: src/sam/player/bus/BusSO.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/bus/BusSO.o src/sam/player/bus/BusSO.cpp

${OBJECTDIR}/src/sam/player/data/BoardLine.o: src/sam/player/data/BoardLine.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/BoardLine.o src/sam/player/data/BoardLine.cpp

${OBJECTDIR}/src/sam/player/data/PlayerMode.o: src/sam/player/data/PlayerMode.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/PlayerMode.o src/sam/player/data/PlayerMode.cpp

${OBJECTDIR}/src/sam/player/main.o: src/sam/player/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/main.o src/sam/player/main.cpp

${OBJECTDIR}/src/sam/player/modules/analyse/LineAnalyser.o: src/sam/player/modules/analyse/LineAnalyser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/analyse
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/analyse/LineAnalyser.o src/sam/player/modules/analyse/LineAnalyser.cpp

${OBJECTDIR}/src/sam/player/utils/module2.o: src/sam/player/utils/module2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/module2.o src/sam/player/utils/module2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
