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
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran

# Macros
PLATFORM=GNU-Linux-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/matrix.o \
	${OBJECTDIR}/src/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-lz -lcairo
CXXFLAGS=-lz -lcairo

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Debug.mk dist/Debug/${PLATFORM}/backprojector

dist/Debug/${PLATFORM}/backprojector: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/${PLATFORM}
	${LINK.cc} -lz -o dist/Debug/${PLATFORM}/backprojector ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/matrix.o: src/matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/matrix.o src/matrix.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/${PLATFORM}/backprojector

# Subprojects
.clean-subprojects:
