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
	${OBJECTDIR}/src/sam/player/GameManager.o \
	${OBJECTDIR}/src/sam/player/TaskFactory.o \
	${OBJECTDIR}/src/sam/player/data/GameBoard.o \
	${OBJECTDIR}/src/sam/player/data/GameFlow.o \
	${OBJECTDIR}/src/sam/player/data/PlayerIdentity.o \
	${OBJECTDIR}/src/sam/player/learn/GameState.o \
	${OBJECTDIR}/src/sam/player/learn/GameTask.o \
	${OBJECTDIR}/src/sam/player/learn/TaskReward.o \
	${OBJECTDIR}/src/sam/player/main.o \
	${OBJECTDIR}/src/sam/player/modules/BoardActuator.o \
	${OBJECTDIR}/src/sam/player/modules/BoardSensor.o \
	${OBJECTDIR}/src/sam/player/modules/Player.o \
	${OBJECTDIR}/src/sam/player/modules/PlayerPurpose.o \
	${OBJECTDIR}/src/sam/player/modules/PurposeTrainer.o \
	${OBJECTDIR}/src/sam/player/modules/PurposeWinner.o \
	${OBJECTDIR}/src/sam/player/modules/play/Line.o \
	${OBJECTDIR}/src/sam/player/modules/play/PlayerActions.o \
	${OBJECTDIR}/src/sam/player/modules/play/SimplePlayer.o \
	${OBJECTDIR}/src/sam/player/modules/play/SmartPlayer.o \
	${OBJECTDIR}/src/sam/player/modules/play/Strategy.o \
	${OBJECTDIR}/src/sam/player/modules/play/Strategy2.o \
	${OBJECTDIR}/src/sam/player/utils/QExtractor.o \
	${OBJECTDIR}/src/sam/player/utils/TaskTree.o \
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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/sam/player/GameManager.o: src/sam/player/GameManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/GameManager.o src/sam/player/GameManager.cpp

${OBJECTDIR}/src/sam/player/TaskFactory.o: src/sam/player/TaskFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/TaskFactory.o src/sam/player/TaskFactory.cpp

${OBJECTDIR}/src/sam/player/data/GameBoard.o: src/sam/player/data/GameBoard.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/GameBoard.o src/sam/player/data/GameBoard.cpp

${OBJECTDIR}/src/sam/player/data/GameFlow.o: src/sam/player/data/GameFlow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/GameFlow.o src/sam/player/data/GameFlow.cpp

${OBJECTDIR}/src/sam/player/data/PlayerIdentity.o: src/sam/player/data/PlayerIdentity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/PlayerIdentity.o src/sam/player/data/PlayerIdentity.cpp

${OBJECTDIR}/src/sam/player/learn/GameState.o: src/sam/player/learn/GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/learn
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/learn/GameState.o src/sam/player/learn/GameState.cpp

${OBJECTDIR}/src/sam/player/learn/GameTask.o: src/sam/player/learn/GameTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/learn
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/learn/GameTask.o src/sam/player/learn/GameTask.cpp

${OBJECTDIR}/src/sam/player/learn/TaskReward.o: src/sam/player/learn/TaskReward.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/learn
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/learn/TaskReward.o src/sam/player/learn/TaskReward.cpp

${OBJECTDIR}/src/sam/player/main.o: src/sam/player/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/main.o src/sam/player/main.cpp

${OBJECTDIR}/src/sam/player/modules/BoardActuator.o: src/sam/player/modules/BoardActuator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/BoardActuator.o src/sam/player/modules/BoardActuator.cpp

${OBJECTDIR}/src/sam/player/modules/BoardSensor.o: src/sam/player/modules/BoardSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/BoardSensor.o src/sam/player/modules/BoardSensor.cpp

${OBJECTDIR}/src/sam/player/modules/Player.o: src/sam/player/modules/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/Player.o src/sam/player/modules/Player.cpp

${OBJECTDIR}/src/sam/player/modules/PlayerPurpose.o: src/sam/player/modules/PlayerPurpose.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/PlayerPurpose.o src/sam/player/modules/PlayerPurpose.cpp

${OBJECTDIR}/src/sam/player/modules/PurposeTrainer.o: src/sam/player/modules/PurposeTrainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/PurposeTrainer.o src/sam/player/modules/PurposeTrainer.cpp

${OBJECTDIR}/src/sam/player/modules/PurposeWinner.o: src/sam/player/modules/PurposeWinner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/PurposeWinner.o src/sam/player/modules/PurposeWinner.cpp

${OBJECTDIR}/src/sam/player/modules/play/Line.o: src/sam/player/modules/play/Line.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/play/Line.o src/sam/player/modules/play/Line.cpp

${OBJECTDIR}/src/sam/player/modules/play/PlayerActions.o: src/sam/player/modules/play/PlayerActions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/play/PlayerActions.o src/sam/player/modules/play/PlayerActions.cpp

${OBJECTDIR}/src/sam/player/modules/play/SimplePlayer.o: src/sam/player/modules/play/SimplePlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/play/SimplePlayer.o src/sam/player/modules/play/SimplePlayer.cpp

${OBJECTDIR}/src/sam/player/modules/play/SmartPlayer.o: src/sam/player/modules/play/SmartPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/play/SmartPlayer.o src/sam/player/modules/play/SmartPlayer.cpp

${OBJECTDIR}/src/sam/player/modules/play/Strategy.o: src/sam/player/modules/play/Strategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/play/Strategy.o src/sam/player/modules/play/Strategy.cpp

${OBJECTDIR}/src/sam/player/modules/play/Strategy2.o: src/sam/player/modules/play/Strategy2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/play/Strategy2.o src/sam/player/modules/play/Strategy2.cpp

${OBJECTDIR}/src/sam/player/utils/QExtractor.o: src/sam/player/utils/QExtractor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/QExtractor.o src/sam/player/utils/QExtractor.cpp

${OBJECTDIR}/src/sam/player/utils/TaskTree.o: src/sam/player/utils/TaskTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/TaskTree.o src/sam/player/utils/TaskTree.cpp

${OBJECTDIR}/src/sam/player/utils/module2.o: src/sam/player/utils/module2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/module2.o src/sam/player/utils/module2.cpp

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
