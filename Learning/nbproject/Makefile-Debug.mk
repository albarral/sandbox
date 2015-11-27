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
	${OBJECTDIR}/src/nav/Connection.o \
	${OBJECTDIR}/src/nav/ConnectionType.o \
	${OBJECTDIR}/src/nav/Environment.o \
	${OBJECTDIR}/src/nav/LearnNav.o \
	${OBJECTDIR}/src/nav/Place.o \
	${OBJECTDIR}/src/sam/learn/Learn.o \
	${OBJECTDIR}/src/sam/learn/State.o \
	${OBJECTDIR}/src/sam/learn/Task.o \
	${OBJECTDIR}/src/sam/learn/Transition.o


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
LDLIBSOPTIONS=-Wl,-rpath,../utilsDB/dist/Debug/GNU-Linux -L../utilsDB/dist/Debug/GNU-Linux -lsam_utilsDB -lmysqlcppconn -lopencv_core

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}: ../utilsDB/dist/Debug/GNU-Linux/libsam_utilsDB.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/nav/Connection.o: src/nav/Connection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/Connection.o src/nav/Connection.cpp

${OBJECTDIR}/src/nav/ConnectionType.o: src/nav/ConnectionType.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/ConnectionType.o src/nav/ConnectionType.cpp

${OBJECTDIR}/src/nav/Environment.o: src/nav/Environment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/Environment.o src/nav/Environment.cpp

${OBJECTDIR}/src/nav/LearnNav.o: src/nav/LearnNav.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/LearnNav.o src/nav/LearnNav.cpp

${OBJECTDIR}/src/nav/Place.o: src/nav/Place.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/nav
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/nav/Place.o src/nav/Place.cpp

${OBJECTDIR}/src/sam/learn/Learn.o: src/sam/learn/Learn.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/learn
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/learn/Learn.o src/sam/learn/Learn.cpp

${OBJECTDIR}/src/sam/learn/State.o: src/sam/learn/State.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/learn
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/learn/State.o src/sam/learn/State.cpp

${OBJECTDIR}/src/sam/learn/Task.o: src/sam/learn/Task.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/learn
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/learn/Task.o src/sam/learn/Task.cpp

${OBJECTDIR}/src/sam/learn/Transition.o: src/sam/learn/Transition.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/learn
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -I../utilsDB/src -std=c++11 -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/learn/Transition.o src/sam/learn/Transition.cpp

# Subprojects
.build-subprojects:
	cd ../utilsDB && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_learning.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:
	cd ../utilsDB && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
