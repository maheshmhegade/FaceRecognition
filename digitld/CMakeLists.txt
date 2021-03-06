# Open The CMake GUI
# specify the source directory and the binary directory
# press configure
# set CMAKE_INSTALL_PREFIX to the path where you want to install the program
# press configure
# check BUILD_WITH_QT if you want to build the program with a QT-Config GUI
# check GENERATE_DEB_PACKAGE if you want to build a debian package (only on Linux)
#
# UNIX Makefile:
# 1) go to the binary folder and type "make" to build the project
# 2) (optional) type "make install all" to install the files into the install
#    directory
# 3) (optional) type "make package" to create a package of the install folder
#    (.tgz file if GENERATE_DEB_PACKAGE=false, .deb file if GENERATE_DEB_PACKAGE=true)
#
# Microsoft Visual C++:
# 1) open the .sln file
# 2) change the mode to "Release" -> only Release is supported!
# 3) build the project "ALL_BUILD" to build the opentld project
# 4) build the project "INSTALL" to install the files into the install
#    directory
# 5) build the project "PACKAGE" to create an NSIS-installer (NSIS is required)


project(OpenTLD)

cmake_minimum_required(VERSION 2.6)

find_package(OpenCV REQUIRED)

#-------------------------------------------------------------------------------
#version
set(TLD_VERSION_MAJOR 1)
set(TLD_VERSION_MINOR 2)
set(TLD_VERSION_PATCH 0)
set(TLD_VERSION ${TLD_VERSION_MAJOR}.${TLD_VERSION_MINOR}.${TLD_VERSION_PATCH})
add_library(cvblobs
    blob.cpp
    BlobContour.cpp
    BlobOperators.cpp
    BlobProperties.cpp
    BlobResult.cpp
    ComponentLabeling.cpp
    blob.h
    BlobContour.h
    BlobLibraryConfiguration.h
    BlobOperators.h
    BlobProperties.h
    BlobResult.h
    ComponentLabeling.h)
if(WIN32)
	add_definitions(-DLIBCONFIGXX_STATIC -DLIBCONFIG_STATIC -DYY_NO_UNISTD_H -DYY_USE_CONST -D_CRT_SECURE_NO_DEPRECATE -D_STDLIB_H)
endif(WIN32)

add_library(libconfig
    grammar.c
    libconfig.c
    libconfigcpp.cc
    scanctx.c
    scanner.c
    strbuf.c
    grammar.h
    libconfig.h
    libconfig.hh
    parsectx.h
    scanctx.h
    scanner.h
    strbuf.h
    wincompat.h)
link_directories(${OpenCV_LIB_DIR})

add_library(libopentld
    ImAcq.cpp
    BB.cpp
    BBPredict.cpp
    FBTrack.cpp
    Lk.cpp
    Median.cpp
    Clustering.cpp
    DetectionResult.cpp
    DetectorCascade.cpp
    EnsembleClassifier.cpp
    ForegroundDetector.cpp
    MedianFlowTracker.cpp
    NNClassifier.cpp
    TLD.cpp
    TLDUtil.cpp
    VarianceFilter.cpp
    ImAcq.h
    BB.h
    BBPredict.h
    FBTrack.h
    Lk.h
    Median.h
    Clustering.h
    DetectionResult.h
    DetectorCascade.h
    EnsembleClassifier.h
    ForegroundDetector.h
    IntegralImage.h
    MedianFlowTracker.h
    NNClassifier.h
    NormalizedPatch.h
    TLD.h
    TLDUtil.h
    VarianceFilter.h)
target_link_libraries(libopentld ${OpenCV_LIBS})
include_directories(main ${OpenCV_INCLUDE_DIRS})


add_executable(opentld
    OpenTLD.cpp
    Config.cpp
    Gui.cpp
    Main.cpp
    Settings.cpp
    Config.h
    Gui.h
    Main.h
    Settings.h)

target_link_libraries(opentld libopentld cvblobs libconfig ${OpenCV_LIBS})

install(TARGETS opentld DESTINATION bin)

set_target_properties(libopentld PROPERTIES OUTPUT_NAME opentld)

#------------------------------------------------------------------------------
#build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(WIN32)
	add_definitions(-DLIBCONFIGXX_STATIC -DLIBCONFIG_STATIC) #Needed when linking libconfig statically
endif(WIN32)

if(APPLE)
	add_definitions(-DHAVE_XLOCALE_H)
endif(APPLE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgomp")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


configure_file("${PROJECT_SOURCE_DIR}/OpenTLDConfig.cmake.in" "${PROJECT_BINARY_DIR}/OpenTLDConfig.cmake" @ONLY)

