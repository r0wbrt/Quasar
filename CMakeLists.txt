cmake_minimum_required(VERSION 2.8.11)
project(Quasar CXX)

set(Quasar_VERSION_MAJOR 3)
set(Quasar_VERSION_MINOR 0)
set(Quasar_VERSION_PATCH 0)
set(Quasar_VERSION_SUFFIX "-dev")
set(Quasar_VERSION "${Quasar_VERSION_MAJOR}.${Quasar_VERSION_MINOR}.${Quasar_VERSION_PATCH}${Quasar_VERSION_SUFFIX}")


################################################################################
#
# Build options
#
################################################################################

option(Quasar_BUILD_EXAMPLES "Build example programs?" ON)
option(Quasar_BUILD_TESTS "Build test programs?" ON)

################################################################################
#
# Dependencies
#
################################################################################

# libraries bundled with Quasar
add_subdirectory(lib)
set(Quasar_LIBRARIES_TO_LINK_WITH Ooura_fft)

# additional CMake modules
set(CMAKE_MODULE_PATH "${Quasar_SOURCE_DIR}/cmake")

# SFML - if available
#set(SFML_STATIC true)
find_package(SFML COMPONENTS System Audio)
if(SFML_FOUND)
    message("SFML was found, wrappers and examples using SFML will be built.")
    include_directories(${SFML_INCLUDE_DIR})
    list(APPEND Quasar_LIBRARIES_TO_LINK_WITH ${SFML_LIBRARY})
else()
    message(WARNING "SFML was not found, wrappers and examples using SFML will not be built.")
endif()


################################################################################
#
# Quasar sources
#
################################################################################

# library headers
set(Quasar_HEADERS
    Quasar/quasar.h
    Quasar/global.h
    Quasar/functions.h
#    Quasar/Exceptions.h
#    Quasar/source.h
#    Quasar/transform.h
#    Quasar/filter.h
#    Quasar/ml.h
#    Quasar/filter/MelFilter.h
#    Quasar/filter/MelFilterBank.h
#    Quasar/ml/DtwPoint.h
#    Quasar/ml/Dtw.h
    Quasar/source/SignalSource.h
    Quasar/source/Frame.h
    Quasar/source/FramesCollection.h
    Quasar/source/PlainTextFile.h
    Quasar/source/RawPcmFile.h
#    Quasar/source/WaveFile.h
#    Quasar/source/WaveFileHandler.h
	Quasar/filter/RaisedCosineFilter.h
	Quasar/filter/SincFilter.h
    Quasar/source/generator/Generator.h
    Quasar/source/generator/SineGenerator.h
    Quasar/source/generator/SquareGenerator.h
    Quasar/source/generator/TriangleGenerator.h
    Quasar/source/generator/PinkNoiseGenerator.h
    Quasar/source/generator/WhiteNoiseGenerator.h
    Quasar/source/generator/ChirpGenerator.h
    Quasar/source/window/BarlettWindow.h
    Quasar/source/window/BlackmanHarrisWindow.h
    Quasar/source/window/BlackmanWindow.h
    Quasar/source/window/BlackmanNuttallWindow.h
    Quasar/source/window/FlattopWindow.h
    Quasar/source/window/GaussianWindow.h
    Quasar/source/window/HammingWindow.h
    Quasar/source/window/HannWindow.h
    Quasar/source/window/RectangularWindow.h
    Quasar/transform/Fft.h
    Quasar/transform/Dft.h
    Quasar/transform/QuasarFft.h
    Quasar/transform/OouraFft.h
    Quasar/transform/FftFactory.h
    Quasar/transform/Dct.h
    Quasar/transform/Mfcc.h
#    Quasar/transform/Spectrogram.h
)

# library sources
set(Quasar_SOURCES
#    Quasar/filter/MelFilter.cpp
#    Quasar/filter/MelFilterBank.cpp
#    Quasar/ml/Dtw.cpp
#   Quasar/source/WaveFile.cpp
#   Quasar/source/WaveFileHandler.cpp
#    Quasar/transform/Dft.cpp
#    Quasar/transform/QuasarFft.cpp
#    Quasar/transform/OouraFft.cpp
#    Quasar/transform/FftFactory.cpp
#    Quasar/transform/Dct.cpp
#    Quasar/transform/Mfcc.cpp
#    Quasar/transform/Spectrogram.cpp
)

# SFML wrappers
if(SFML_FOUND)
    list(APPEND Quasar_HEADERS
        Quasar/synth.h
        Quasar/wrappers/SoundBufferAdapter.h
    )
    list(APPEND Quasar_SOURCES
        Quasar/wrappers/SoundBufferAdapter.cpp
    )
endif()


################################################################################
#
# Compiler-specific workarounds
#
################################################################################

if(MSVC)
    # disable "strncpy is deprecated" warning and enable math constants
    add_definitions("/D_CRT_NONSTDC_NO_DEPRECATE /D_USE_MATH_DEFINES")
endif()


if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    if(APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -Wcast-qual -Wcast-align -Wno-unused-parameter -Wmissing-include-dirs -Wpointer-arith -Wredundant-decls -Wshadow -fprofile-arcs -ftest-coverage")
    include(CodeCoverage)
    setup_target_for_coverage(coverage Quasar_test htmlcov)
endif()


################################################################################
#
# Building and linking
#
################################################################################

# main Quasar library
add_library(Quasar ${Quasar_HEADERS} ${Quasar_SOURCES})

# linking with extra libs
target_link_libraries(Quasar ${Quasar_LIBRARIES_TO_LINK_WITH})

# examples
if(Quasar_BUILD_EXAMPLES)
    add_custom_target(examples)
    add_subdirectory(examples)
endif()

#tests
if(Quasar_BUILD_TESTS)
    enable_testing()
    set(UNITTESTPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/unittestpp/")
    add_subdirectory(tests)
endif()

################################################################################
#
# Documentation
#
################################################################################

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
        IMMEDIATE @ONLY
    )
    add_custom_target(docs
        "${DOXYGEN_EXECUTABLE}"
        "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile"
    )
else()
    message(WARNING "Doxygen not found, documentation will not be built")
endif()


################################################################################
#
# Installing
#
################################################################################

# install the binaries and include files
install(TARGETS Quasar
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
install(DIRECTORY Quasar/ DESTINATION include/Quasar FILES_MATCHING PATTERN "*.h")
install(FILES CHANGELOG LICENSE README.md DESTINATION share/Quasar)


################################################################################
#
# Uninstalling
#
################################################################################

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
)
