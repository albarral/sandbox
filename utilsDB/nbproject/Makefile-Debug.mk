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
	${OBJECTDIR}/src/sam/utilsDB/DBClient.o \
	${OBJECTDIR}/src/sam/utilsDB/DBConnection.o \
	${OBJECTDIR}/src/sam/utilsDB/Database.o


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
LDLIBSOPTIONS=-lmysqlcppconn

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_utilsDB.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_utilsDB.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_utilsDB.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/sam/utilsDB/DBClient.o: src/sam/utilsDB/DBClient.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/utilsDB
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/utilsDB/DBClient.o src/sam/utilsDB/DBClient.cpp

${OBJECTDIR}/src/sam/utilsDB/DBConnection.o: src/sam/utilsDB/DBConnection.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/utilsDB
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/utilsDB/DBConnection.o src/sam/utilsDB/DBConnection.cpp

${OBJECTDIR}/src/sam/utilsDB/Database.o: src/sam/utilsDB/Database.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sam/utilsDB
	${RM} "$@.d"
	$(COMPILE.cc) -g -Isrc -fPIC  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/sam/utilsDB/Database.o src/sam/utilsDB/Database.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libsam_utilsDB.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
