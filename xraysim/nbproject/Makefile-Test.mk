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
OBJECTDIR=build/Test/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/matrix.o \
	${OBJECTDIR}/test/testmain.o \
	${OBJECTDIR}/src/matrixtask.o \
	${OBJECTDIR}/src/seedstack.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Test.mk dist/Test/${PLATFORM}/xraysim-test

dist/Test/${PLATFORM}/xraysim-test: ${OBJECTFILES}
	${MKDIR} -p dist/Test/${PLATFORM}
	${LINK.cc} -o dist/Test/${PLATFORM}/xraysim-test ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/matrix.o: src/matrix.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/matrix.o src/matrix.cpp

${OBJECTDIR}/test/testmain.o: test/testmain.cpp 
	${MKDIR} -p ${OBJECTDIR}/test
	$(COMPILE.cc) -g -o ${OBJECTDIR}/test/testmain.o test/testmain.cpp

${OBJECTDIR}/src/matrixtask.o: src/matrixtask.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/matrixtask.o src/matrixtask.cpp

${OBJECTDIR}/src/seedstack.o: src/seedstack.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -g -o ${OBJECTDIR}/src/seedstack.o src/seedstack.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Test
	${RM} dist/Test/${PLATFORM}/xraysim-test

# Subprojects
.clean-subprojects:
