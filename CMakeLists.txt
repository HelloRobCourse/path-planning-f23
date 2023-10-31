cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(path_planning)

option(MBOT "Build code for the MBot." OFF)

if(MBOT)
  message("Building code for the MBot.")
  set(MACHINE_TYPE "OMNI")
else()
  message("Building code for laptop.")
  set(MACHINE_TYPE "LAPTOP")
endif()

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

find_package(Threads REQUIRED)

# If we're building for the Omnibot, find LCM.
if(${MACHINE_TYPE} STREQUAL "OMNI")
  find_package(mbot_bridge REQUIRED)
endif()

# Nav App helper. Only build if we are not on the Omnibot
add_executable(nav_cli src/path_planner_cli.cpp
  src/graph_search/graph_search.cpp
  src/graph_search/distance_transform.cpp
  src/utils/graph_utils.cpp
)
target_link_libraries(nav_cli
  ${CMAKE_THREAD_LIBS_INIT}
)
target_include_directories(nav_cli PRIVATE
  include
)

# If we're building for the Omnibot, build the LCM server.
if(${MACHINE_TYPE} STREQUAL "OMNI")
  add_executable(robot_plan_path src/robot_plan_path.cpp
    src/graph_search/distance_transform.cpp
    src/graph_search/graph_search.cpp
    src/utils/graph_utils.cpp
  )
  target_link_libraries(robot_plan_path
    mbot_bridge_cpp
  )
  target_include_directories(robot_plan_path PRIVATE
    include
  )
endif()

if (CMAKE_BUILD_TYPE MATCHES Test)
endif()
