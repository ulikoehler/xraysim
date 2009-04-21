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
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/fpmath.o \
	${OBJECTDIR}/src/matrix.o \
	${OBJECTDIR}/src/main.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -march=core2 -mfpmath=sse -msse3 -fexpensive-optimizations -fomit-frame-pointer -ffast-math -funroll-loops -funsafe-math-optimizations
CXXFLAGS=-m64 -march=core2 -mfpmath=sse -msse3 -fexpensive-optimizations -fomit-frame-pointer -ffast-math -funroll-loops -funsafe-math-optimizations

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/backprojector

dist/Release/${PLATFORM}/backprojector: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -lz -o dist/Release/${PLATFORM}/backprojector ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/fpmath.o: src/fpmath.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -DNDEBUG -o ${OBJECTDIR}/src/fpmath.o src/fpmath.cpp

${OBJECTDIR}/src/matrix.o: src/matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -DNDEBUG -o ${OBJECTDIR}/src/matrix.o src/matrix.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -DNDEBUG -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/backprojector

# Subprojects
.clean-subprojects:
