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
	${OBJECTDIR}/src/VirtualEnvironment.o \
	${OBJECTDIR}/src/VirtualTask.o \
	${OBJECTDIR}/src/main.o


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
LDLIBSOPTIONS=-Wl,-rpath,../Learning/dist/Debug/GNU-Linux-x86 -L../Learning/dist/Debug/GNU-Linux-x86 -lLearning -Wl,-rpath,../samUtils/dist/Debug/GNU-Linux-x86 -L../samUtils/dist/Debug/GNU-Linux-x86 -lsam_utils

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/navigator

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/navigator: ../Learning/dist/Debug/GNU-Linux-x86/libLearning.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/navigator: ../samUtils/dist/Debug/GNU-Linux-x86/libsam_utils.so

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/navigator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/navigator ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/VirtualEnvironment.o: src/VirtualEnvironment.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Learning/src -I../samUtils/src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/VirtualEnvironment.o src/VirtualEnvironment.cpp

${OBJECTDIR}/src/VirtualTask.o: src/VirtualTask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Learning/src -I../samUtils/src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/VirtualTask.o src/VirtualTask.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Learning/src -I../samUtils/src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:
	cd ../Learning && ${MAKE}  -f Makefile CONF=Debug
	cd ../samUtils && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/navigator

# Subprojects
.clean-subprojects:
	cd ../Learning && ${MAKE}  -f Makefile CONF=Debug clean
	cd ../samUtils && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
