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
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/GameManager.o \
	${OBJECTDIR}/src/TaskFactory.o \
	${OBJECTDIR}/src/data/GameBoard.o \
	${OBJECTDIR}/src/data/GameFlow.o \
	${OBJECTDIR}/src/data/PlayerIdentity.o \
	${OBJECTDIR}/src/learn/GameDistance.o \
	${OBJECTDIR}/src/learn/GameState.o \
	${OBJECTDIR}/src/learn/GameTask.o \
	${OBJECTDIR}/src/learn/TaskReward.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/modules/BoardActuator.o \
	${OBJECTDIR}/src/modules/BoardSensor.o \
	${OBJECTDIR}/src/modules/Informer.o \
	${OBJECTDIR}/src/modules/Line.o \
	${OBJECTDIR}/src/modules/Player.o \
	${OBJECTDIR}/src/modules/PlayerActions.o \
	${OBJECTDIR}/src/modules/Strategy.o \
	${OBJECTDIR}/src/modules/Strategy2.o \
	${OBJECTDIR}/src/utils/module2.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/GameManager.o: src/GameManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameManager.o src/GameManager.cpp

${OBJECTDIR}/src/TaskFactory.o: src/TaskFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TaskFactory.o src/TaskFactory.cpp

${OBJECTDIR}/src/data/GameBoard.o: src/data/GameBoard.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/data/GameBoard.o src/data/GameBoard.cpp

${OBJECTDIR}/src/data/GameFlow.o: src/data/GameFlow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/data/GameFlow.o src/data/GameFlow.cpp

${OBJECTDIR}/src/data/PlayerIdentity.o: src/data/PlayerIdentity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/data/PlayerIdentity.o src/data/PlayerIdentity.cpp

${OBJECTDIR}/src/learn/GameDistance.o: src/learn/GameDistance.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/learn
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/learn/GameDistance.o src/learn/GameDistance.cpp

${OBJECTDIR}/src/learn/GameState.o: src/learn/GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/learn
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/learn/GameState.o src/learn/GameState.cpp

${OBJECTDIR}/src/learn/GameTask.o: src/learn/GameTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/learn
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/learn/GameTask.o src/learn/GameTask.cpp

${OBJECTDIR}/src/learn/TaskReward.o: src/learn/TaskReward.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/learn
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/learn/TaskReward.o src/learn/TaskReward.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/modules/BoardActuator.o: src/modules/BoardActuator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/BoardActuator.o src/modules/BoardActuator.cpp

${OBJECTDIR}/src/modules/BoardSensor.o: src/modules/BoardSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/BoardSensor.o src/modules/BoardSensor.cpp

${OBJECTDIR}/src/modules/Informer.o: src/modules/Informer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/Informer.o src/modules/Informer.cpp

${OBJECTDIR}/src/modules/Line.o: src/modules/Line.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/Line.o src/modules/Line.cpp

${OBJECTDIR}/src/modules/Player.o: src/modules/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/Player.o src/modules/Player.cpp

${OBJECTDIR}/src/modules/PlayerActions.o: src/modules/PlayerActions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/PlayerActions.o src/modules/PlayerActions.cpp

${OBJECTDIR}/src/modules/Strategy.o: src/modules/Strategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/Strategy.o src/modules/Strategy.cpp

${OBJECTDIR}/src/modules/Strategy2.o: src/modules/Strategy2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/Strategy2.o src/modules/Strategy2.cpp

${OBJECTDIR}/src/utils/module2.o: src/utils/module2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/module2.o src/utils/module2.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
