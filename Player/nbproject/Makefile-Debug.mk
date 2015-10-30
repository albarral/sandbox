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
	${OBJECTDIR}/src/GameManager.o \
	${OBJECTDIR}/src/TaskFactory.o \
	${OBJECTDIR}/src/data/GameBoard.o \
	${OBJECTDIR}/src/data/GameFlow.o \
	${OBJECTDIR}/src/data/PlayerIdentity.o \
	${OBJECTDIR}/src/learn/GameState.o \
	${OBJECTDIR}/src/learn/GameTask.o \
	${OBJECTDIR}/src/learn/TaskReward.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/modules/BoardActuator.o \
	${OBJECTDIR}/src/modules/BoardSensor.o \
	${OBJECTDIR}/src/modules/Player.o \
	${OBJECTDIR}/src/modules/PlayerPurpose.o \
	${OBJECTDIR}/src/modules/PurposeTrainer.o \
	${OBJECTDIR}/src/modules/PurposeWinner.o \
	${OBJECTDIR}/src/modules/play/Line.o \
	${OBJECTDIR}/src/modules/play/PlayerActions.o \
	${OBJECTDIR}/src/modules/play/SimplePlayer.o \
	${OBJECTDIR}/src/modules/play/SmartPlayer.o \
	${OBJECTDIR}/src/modules/play/Strategy.o \
	${OBJECTDIR}/src/modules/play/Strategy2.o \
	${OBJECTDIR}/src/utils/TaskTree.o \
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
LDLIBSOPTIONS=-llog4cxx -lopencv_core -Wl,-rpath,../samUtils/dist/Debug/GNU-Linux-x86 -L../samUtils/dist/Debug/GNU-Linux-x86 -lsam_utils -Wl,-rpath,../Learning/dist/Debug/GNU-Linux-x86 -L../Learning/dist/Debug/GNU-Linux-x86 -lsam_learning

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player: ../samUtils/dist/Debug/GNU-Linux-x86/libsam_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player: ../Learning/dist/Debug/GNU-Linux-x86/libsam_learning.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/GameManager.o: src/GameManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/GameManager.o src/GameManager.cpp

${OBJECTDIR}/src/TaskFactory.o: src/TaskFactory.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/TaskFactory.o src/TaskFactory.cpp

${OBJECTDIR}/src/data/GameBoard.o: src/data/GameBoard.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/data/GameBoard.o src/data/GameBoard.cpp

${OBJECTDIR}/src/data/GameFlow.o: src/data/GameFlow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/data/GameFlow.o src/data/GameFlow.cpp

${OBJECTDIR}/src/data/PlayerIdentity.o: src/data/PlayerIdentity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/data/PlayerIdentity.o src/data/PlayerIdentity.cpp

${OBJECTDIR}/src/learn/GameState.o: src/learn/GameState.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/learn
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/learn/GameState.o src/learn/GameState.cpp

${OBJECTDIR}/src/learn/GameTask.o: src/learn/GameTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/learn
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/learn/GameTask.o src/learn/GameTask.cpp

${OBJECTDIR}/src/learn/TaskReward.o: src/learn/TaskReward.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/learn
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/learn/TaskReward.o src/learn/TaskReward.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/modules/BoardActuator.o: src/modules/BoardActuator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/BoardActuator.o src/modules/BoardActuator.cpp

${OBJECTDIR}/src/modules/BoardSensor.o: src/modules/BoardSensor.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/BoardSensor.o src/modules/BoardSensor.cpp

${OBJECTDIR}/src/modules/Player.o: src/modules/Player.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/Player.o src/modules/Player.cpp

${OBJECTDIR}/src/modules/PlayerPurpose.o: src/modules/PlayerPurpose.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/PlayerPurpose.o src/modules/PlayerPurpose.cpp

${OBJECTDIR}/src/modules/PurposeTrainer.o: src/modules/PurposeTrainer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/PurposeTrainer.o src/modules/PurposeTrainer.cpp

${OBJECTDIR}/src/modules/PurposeWinner.o: src/modules/PurposeWinner.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/PurposeWinner.o src/modules/PurposeWinner.cpp

${OBJECTDIR}/src/modules/play/Line.o: src/modules/play/Line.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/play/Line.o src/modules/play/Line.cpp

${OBJECTDIR}/src/modules/play/PlayerActions.o: src/modules/play/PlayerActions.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/play/PlayerActions.o src/modules/play/PlayerActions.cpp

${OBJECTDIR}/src/modules/play/SimplePlayer.o: src/modules/play/SimplePlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/play/SimplePlayer.o src/modules/play/SimplePlayer.cpp

${OBJECTDIR}/src/modules/play/SmartPlayer.o: src/modules/play/SmartPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/play/SmartPlayer.o src/modules/play/SmartPlayer.cpp

${OBJECTDIR}/src/modules/play/Strategy.o: src/modules/play/Strategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/play/Strategy.o src/modules/play/Strategy.cpp

${OBJECTDIR}/src/modules/play/Strategy2.o: src/modules/play/Strategy2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/modules/play
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/modules/play/Strategy2.o src/modules/play/Strategy2.cpp

${OBJECTDIR}/src/utils/TaskTree.o: src/utils/TaskTree.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/TaskTree.o src/utils/TaskTree.cpp

${OBJECTDIR}/src/utils/module2.o: src/utils/module2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../samUtils/src -I../Learning/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/utils/module2.o src/utils/module2.cpp

# Subprojects
.build-subprojects:
	cd ../samUtils && ${MAKE}  -f Makefile CONF=Debug
	cd ../Learning && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player

# Subprojects
.clean-subprojects:
	cd ../samUtils && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../Learning && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
