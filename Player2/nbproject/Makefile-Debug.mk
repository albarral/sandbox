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
	${OBJECTDIR}/src/sam/player/ConsolePlayer.o \
	${OBJECTDIR}/src/sam/player/PlayerConfig.o \
	${OBJECTDIR}/src/sam/player/bus/Bus.o \
	${OBJECTDIR}/src/sam/player/bus/BusUser.o \
	${OBJECTDIR}/src/sam/player/bus/COBus.o \
	${OBJECTDIR}/src/sam/player/bus/SOBus.o \
	${OBJECTDIR}/src/sam/player/data/GameAction.o \
	${OBJECTDIR}/src/sam/player/data/GameBoard.o \
	${OBJECTDIR}/src/sam/player/data/PlayerData.o \
	${OBJECTDIR}/src/sam/player/data/T3Board.o \
	${OBJECTDIR}/src/sam/player/data/T3Game.o \
	${OBJECTDIR}/src/sam/player/main.o \
	${OBJECTDIR}/src/sam/player/modules/analyse/GameAnalyser.o \
	${OBJECTDIR}/src/sam/player/modules/analyse/LineAnalyser2.o \
	${OBJECTDIR}/src/sam/player/modules/analyse/SimpleAnalyser2.o \
	${OBJECTDIR}/src/sam/player/modules/analyse/Strategy.o \
	${OBJECTDIR}/src/sam/player/modules/attack/Attacker.o \
	${OBJECTDIR}/src/sam/player/modules/move/VirtualMover.o \
	${OBJECTDIR}/src/sam/player/modules/watch/BoardWatcher.o \
	${OBJECTDIR}/src/sam/player/modules/watch/VirtualWatcher.o \
	${OBJECTDIR}/src/sam/player/utils/Board.o \
	${OBJECTDIR}/src/sam/player/utils/BoardPlace.o \
	${OBJECTDIR}/src/sam/player/utils/BoardZone.o \
	${OBJECTDIR}/src/sam/player/utils/Game.o \
	${OBJECTDIR}/src/sam/player/utils/GameMove.o \
	${OBJECTDIR}/src/sam/player/utils/GamePiece.o \
	${OBJECTDIR}/src/sam/player/utils/Move.o


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
LDLIBSOPTIONS=-Wl,-rpath,../brooks/dist/Debug/GNU-Linux -L../brooks/dist/Debug/GNU-Linux -lsam_brooks -Wl,-rpath,../utils/dist/Debug/GNU-Linux -L../utils/dist/Debug/GNU-Linux -lsam_utils -Wl,-rpath,../utilsDB/dist/Debug/GNU-Linux -L../utilsDB/dist/Debug/GNU-Linux -lsam_utilsDB -llog4cxx -lopencv_core -lmysqlcppconn

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2: ../brooks/dist/Debug/GNU-Linux/libsam_brooks.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2: ../utils/dist/Debug/GNU-Linux/libsam_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2: ../utilsDB/dist/Debug/GNU-Linux/libsam_utilsDB.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/sam/player/AppPlayer.o: src/sam/player/AppPlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/AppPlayer.o src/sam/player/AppPlayer.cpp

${OBJECTDIR}/src/sam/player/ConsolePlayer.o: src/sam/player/ConsolePlayer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/ConsolePlayer.o src/sam/player/ConsolePlayer.cpp

${OBJECTDIR}/src/sam/player/PlayerConfig.o: src/sam/player/PlayerConfig.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/PlayerConfig.o src/sam/player/PlayerConfig.cpp

${OBJECTDIR}/src/sam/player/bus/Bus.o: src/sam/player/bus/Bus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/bus/Bus.o src/sam/player/bus/Bus.cpp

${OBJECTDIR}/src/sam/player/bus/BusUser.o: src/sam/player/bus/BusUser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/bus/BusUser.o src/sam/player/bus/BusUser.cpp

${OBJECTDIR}/src/sam/player/bus/COBus.o: src/sam/player/bus/COBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/bus/COBus.o src/sam/player/bus/COBus.cpp

${OBJECTDIR}/src/sam/player/bus/SOBus.o: src/sam/player/bus/SOBus.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/bus
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/bus/SOBus.o src/sam/player/bus/SOBus.cpp

${OBJECTDIR}/src/sam/player/data/GameAction.o: src/sam/player/data/GameAction.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/GameAction.o src/sam/player/data/GameAction.cpp

${OBJECTDIR}/src/sam/player/data/GameBoard.o: src/sam/player/data/GameBoard.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/GameBoard.o src/sam/player/data/GameBoard.cpp

${OBJECTDIR}/src/sam/player/data/PlayerData.o: src/sam/player/data/PlayerData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/PlayerData.o src/sam/player/data/PlayerData.cpp

${OBJECTDIR}/src/sam/player/data/T3Board.o: src/sam/player/data/T3Board.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/T3Board.o src/sam/player/data/T3Board.cpp

${OBJECTDIR}/src/sam/player/data/T3Game.o: src/sam/player/data/T3Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/data
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/data/T3Game.o src/sam/player/data/T3Game.cpp

${OBJECTDIR}/src/sam/player/main.o: src/sam/player/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/main.o src/sam/player/main.cpp

${OBJECTDIR}/src/sam/player/modules/analyse/GameAnalyser.o: src/sam/player/modules/analyse/GameAnalyser.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/analyse
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/analyse/GameAnalyser.o src/sam/player/modules/analyse/GameAnalyser.cpp

${OBJECTDIR}/src/sam/player/modules/analyse/LineAnalyser2.o: src/sam/player/modules/analyse/LineAnalyser2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/analyse
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/analyse/LineAnalyser2.o src/sam/player/modules/analyse/LineAnalyser2.cpp

${OBJECTDIR}/src/sam/player/modules/analyse/SimpleAnalyser2.o: src/sam/player/modules/analyse/SimpleAnalyser2.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/analyse
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/analyse/SimpleAnalyser2.o src/sam/player/modules/analyse/SimpleAnalyser2.cpp

${OBJECTDIR}/src/sam/player/modules/analyse/Strategy.o: src/sam/player/modules/analyse/Strategy.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/analyse
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/analyse/Strategy.o src/sam/player/modules/analyse/Strategy.cpp

${OBJECTDIR}/src/sam/player/modules/attack/Attacker.o: src/sam/player/modules/attack/Attacker.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/attack
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/attack/Attacker.o src/sam/player/modules/attack/Attacker.cpp

${OBJECTDIR}/src/sam/player/modules/move/VirtualMover.o: src/sam/player/modules/move/VirtualMover.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/move
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/move/VirtualMover.o src/sam/player/modules/move/VirtualMover.cpp

${OBJECTDIR}/src/sam/player/modules/watch/BoardWatcher.o: src/sam/player/modules/watch/BoardWatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/watch
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/watch/BoardWatcher.o src/sam/player/modules/watch/BoardWatcher.cpp

${OBJECTDIR}/src/sam/player/modules/watch/VirtualWatcher.o: src/sam/player/modules/watch/VirtualWatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/modules/watch
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/modules/watch/VirtualWatcher.o src/sam/player/modules/watch/VirtualWatcher.cpp

${OBJECTDIR}/src/sam/player/utils/Board.o: src/sam/player/utils/Board.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/Board.o src/sam/player/utils/Board.cpp

${OBJECTDIR}/src/sam/player/utils/BoardPlace.o: src/sam/player/utils/BoardPlace.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/BoardPlace.o src/sam/player/utils/BoardPlace.cpp

${OBJECTDIR}/src/sam/player/utils/BoardZone.o: src/sam/player/utils/BoardZone.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/BoardZone.o src/sam/player/utils/BoardZone.cpp

${OBJECTDIR}/src/sam/player/utils/Game.o: src/sam/player/utils/Game.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/Game.o src/sam/player/utils/Game.cpp

${OBJECTDIR}/src/sam/player/utils/GameMove.o: src/sam/player/utils/GameMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/GameMove.o src/sam/player/utils/GameMove.cpp

${OBJECTDIR}/src/sam/player/utils/GamePiece.o: src/sam/player/utils/GamePiece.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/GamePiece.o src/sam/player/utils/GamePiece.cpp

${OBJECTDIR}/src/sam/player/utils/Move.o: src/sam/player/utils/Move.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/player/utils
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../brooks/src -I../utils/src -I../utilsDB/src -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/player/utils/Move.o src/sam/player/utils/Move.cpp

# Subprojects
.build-subprojects:
	cd ../brooks && ${MAKE}  -f Makefile CONF=Debug
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug
	cd ../utilsDB && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/player2

# Subprojects
.clean-subprojects:
	cd ../brooks && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../utils && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../utilsDB && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
