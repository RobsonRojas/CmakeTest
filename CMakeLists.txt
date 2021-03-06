cmake_minimum_required (VERSION 2.6)
project (Tutorial)

# should we use our own math functions?
option(USE_MYMATH "Use tutorial provided math implementation" ON)


# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )
 
# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
include_directories("${PROJECT_BINARY_DIR}")

# ADD THE MathFunctions library?
#
if(USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set(EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)


add_executable(Tutorial test1.cpp)
target_link_libraries(Tutorial ${EXTRA_LIBS})

# add the install targets
install(TARGETS Tutorial DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h" DESTINATION include)


include(CTest)

add_test (TutorialRuns Tutorial 25)

add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")


add_test (TutorialNegative Tutorial -25)
set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")


add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")

add_test (TutorialUsage Tutorial Usage)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage: *number")



# package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENCE
    "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set (CPACK_PACKAGE_CONTACT "Robson")
include (CPack)


#To install:
#To generate shell isntaller
#cpack --config CPackConfig.cmake
#cpack --config CPackSourceConfig.cmake
#To install
#sudo ./Tutorial-1.0.1-Linux.sh


#To generate DEB package
#cpack --config CPackConfig.cmake -G DEB
#cpack --config CPackSourceConfig.cmake  -G DEB
#To install
#sudo dpkg -i Tutorial-1.0.1-Linux.deb