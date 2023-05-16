# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project (TotkToolkit CXX)
add_executable(TotkToolkit "Public/TotkToolkit/TotkToolkit.h" "Private/TotkToolkit/TotkToolkit.cpp")
set_target_properties(TotkToolkit PROPERTIES APP_TITLE "TotkToolkit" APP_AUTHOR "Me" APP_VERSION "1.0.0")

set_property(TARGET TotkToolkit PROPERTY CXX_STANDARD 23)
set_property(TARGET TotkToolkit PROPERTY CMAKE_CXX_STANDARD_REQUIRED True)

target_include_directories(TotkToolkit PRIVATE Private Public)

target_include_directories(TotkToolkit PUBLIC Lib/Formats/Public Lib/ImGui)
add_subdirectory(Lib/Formats)



project (ImGui)
add_library(ImGui STATIC Lib/ImGui/imgui.h Lib/ImGui/imgui.cpp Lib/ImGui/imstb_rectpack.h Lib/ImGui/imstb_textedit.h Lib/ImGui/imstb_truetype.h Lib/ImGui/imgui_demo.cpp Lib/ImGui/imgui_draw.cpp Lib/ImGui/imgui_internal.h Lib/ImGui/imgui_tables.cpp Lib/ImGui/imgui_widgets.cpp)
target_include_directories(TotkToolkit PUBLIC Lib/ImGui)


target_link_libraries(TotkToolkit PUBLIC Formats ImGui)


if (SWITCH)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Lib/Switch-CMake/cmake)
include(SwitchTools)
find_package(LIBNX REQUIRED)
target_link_libraries(TotkToolkit PUBLIC switch::libnx)
ADD_NRO_TARGET(TotkToolkit)
endif()