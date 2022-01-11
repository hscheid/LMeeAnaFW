project(PlottingFW CXX)
cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE off)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11) # 17?
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
  message(STATUS "activating filesystem workaround for old gcc versions")
  set(CXX_FILESYSTEM_LIBRARIES "stdc++fs")
endif()

# The following two lines can be used to force using one specific root installation
# set(ROOTSYS ~/root/mybuild)
# list(APPEND CMAKE_PREFIX_PATH ${ROOTSYS})

# set(REQUIRED_ROOT_VERSION 6.16) #not sure which one we need, but its probably super old

set(Boost_USE_MULTITHREADED TRUE)
if(APPLE)
  set(CMAKE_MACOSX_RPATH ON)
endif(APPLE)

set(MODULE PlottingFramework)
set(SRCS
  src/core/LmBackground.cpp
  src/core/LmCocktail.cpp
  src/core/LmFileManager.cpp
  src/core/LmHandler.cpp
  src/core/LmManager.cpp
  src/core/LmQA.cpp
  src/core/LmBaseManager.cpp
  src/core/LmCocktailMan.cpp
  src/core/LmFitFunctions.cpp
  src/core/LmHelper.cpp
  # src/core/LmManager_save.cpp
  src/core/LmRebinner.cpp
  src/core/LmBaseSignal.cpp
  src/core/LmCocktailPart.cpp
  src/core/LmFitter.cpp
  src/core/LmHistogram.cpp
  src/core/LmMultiQA.cpp
  src/core/LmSignal.cpp
)
string(REPLACE ".cpp" ".h" HDRS "${SRCS}")
# string(REPLACE "src" "inc" HDRS "${HDRS}")
# set(MODULE_HDR src/core/${MODULE}.h)

# find dependencies
find_package(ROOT CONFIG REQUIRED)
# find_package(ROOT ${REQUIRED_ROOT_VERSION} CONFIG REQUIRED)
include(${ROOT_USE_FILE})
message(STATUS "root  version: ${ROOT_VERSION}")


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# create PlottingFramework library
add_library(${MODULE} SHARED ${SRCS} ${HDRS})
target_link_libraries(${MODULE} PUBLIC
  ROOT::Gui
  ROOT::Hist
  ROOT::Gpad
  ${CXX_FILESYSTEM_LIBRARIES}
)

# helper function to add executables that are linked to the PlottingFramework
function(add_plotting_executable APP_NAME)
  cmake_parse_arguments(PARSE_ARGV 1 APP "" "" "SOURCES;ADD_FILES")
  if(APP_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Got trailing arguments ${APP_UNPARSED_ARGUMENTS}")
  endif()
  add_executable(${APP_NAME} ${APP_SOURCES} ${APP_ADD_FILES})
  target_link_libraries(${APP_NAME} PlottingFramework)
  message(STATUS "Creating executable ${APP_NAME} from file(s) ${APP_SOURCES}")
endfunction()

# add the command-line plotting app
add_plotting_executable(sebastian
  SOURCES src/user/sebastian.cpp src/user/sebastian.h
)

add_plotting_executable(jerome
  SOURCES src/user/jerome.cpp src/user/jerome.h
)
