cmake_minimum_required (VERSION 3.8)

project (TotkToolkit C CXX)
add_executable(TotkToolkit "Public/TotkToolkit/TotkToolkit.h" "Private/TotkToolkit/TotkToolkit.cpp")
set_target_properties(TotkToolkit PROPERTIES APP_TITLE "TotkToolkit" APP_AUTHOR "Me" APP_VERSION "1.0.0")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Include this
target_include_directories(TotkToolkit PRIVATE Private Public)

# Use Formats
target_include_directories(TotkToolkit PUBLIC Lib/Formats/Public Lib/ImGui)
add_subdirectory(Lib/Formats)
target_link_libraries(TotkToolkit PUBLIC Formats)

# Use ImGui
add_library(ImGui STATIC Lib/ImGui/imgui.h Lib/ImGui/imgui.cpp Lib/ImGui/imstb_rectpack.h Lib/ImGui/imstb_textedit.h Lib/ImGui/imstb_truetype.h Lib/ImGui/imgui_demo.cpp Lib/ImGui/imgui_draw.cpp Lib/ImGui/imgui_internal.h Lib/ImGui/imgui_tables.cpp Lib/ImGui/imgui_widgets.cpp)
target_include_directories(TotkToolkit PUBLIC Lib/ImGui)
target_link_libraries(TotkToolkit PUBLIC ImGui)

# Use SDL
if (SWITCH)
SET(NINTENDO_SWITCH ON) # For SDL
endif()
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory(Lib/SDL)
target_compile_features(SDL2-static PRIVATE c_std_11)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
target_link_libraries(TotkToolkit PUBLIC Threads::Threads)
target_link_libraries(TotkToolkit PUBLIC SDL2-static)

# Set up for switch if desired
if (SWITCH)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Lib/Switch-CMake/cmake)
include(SwitchTools)
find_package(LIBNX REQUIRED)
target_include_directories(TotkToolkit PUBLIC ${LIBNX_INCLUDE_DIR})
target_link_libraries(TotkToolkit PUBLIC switch::libnx)
ADD_NRO_TARGET(TotkToolkit)
#target_include_directories(SDL2-static PUBLIC ${LIBNX_INCLUDE_DIR})
endif()