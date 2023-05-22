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

# Use GLFW
if (SWITCH)
    SET(NINTENDO_SWITCH ON) # For GLFW
endif()
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_EGL_STATIC ON CACHE BOOL "" FORCE)
if (SWITCH) # If GLFW_VULKAN_STATIC is off on switch it doesn't compile because it cannot dynamically load. We set it to ON because it won't attempt to load vulkan on switch anyway. On the other hand, if GLFW_VULKAN_STATIC is on on linux it runs into linking errors.
    set(GLFW_VULKAN_STATIC ON CACHE BOOL "" FORCE)
else()
    set(GLFW_VULKAN_STATIC OFF CACHE BOOL "" FORCE)
endif()
add_subdirectory(Lib/GLFW)
target_link_libraries(TotkToolkit PUBLIC glfw)

# Use GLAD
add_library(GLAD "Lib/Switch-GLAD/include/glad/glad.h" "Lib/Switch-GLAD/source/glad.c")
target_include_directories(GLAD PUBLIC "Lib/Switch-GLAD/include")
target_link_libraries(TotkToolkit PUBLIC GLAD)

# Use C++ standard library (For some reason we need to have this here...)
target_link_libraries(TotkToolkit PUBLIC stdc++)

# Prefer more modern OpenGL. Especially matters when not building for switch.
set(OpenGL_GL_PREFERENCE GLVND)

# Set up for switch if desired
if (SWITCH)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Lib/Switch-CMake/cmake)
    include(SwitchTools)
    ADD_NRO_TARGET(TotkToolkit)

    # Set up LIBNX
    find_package(LIBNX REQUIRED)
    target_include_directories(TotkToolkit SYSTEM PUBLIC ${LIBNX_INCLUDE_DIR})
    target_link_libraries(TotkToolkit PUBLIC ${LIBNX_LIBRARY})
    target_include_directories(glfw SYSTEM PUBLIC ${LIBNX_INCLUDE_DIR})

    # Include PORTLIBS
    target_include_directories(glfw PUBLIC ${PORTLIBS}/include)

    # Set up GLAPI
    find_library(GLAPI NAMES glapi REQUIRED)
    target_link_libraries(TotkToolkit PUBLIC ${GLAPI})

    # Give GLAD PORTLIBS include path so it can load KHR/khrplatform.h
    target_include_directories(GLAD PUBLIC ${PORTLIBS}/include)

    # Set up EGL as imported target (because it requires GLAPI)
    find_library(EGL NAMES EGL REQUIRED)
    add_library(EGL STATIC IMPORTED)
    set_property(TARGET EGL PROPERTY IMPORTED_LOCATION ${EGL})
    target_link_libraries(EGL INTERFACE ${GLAPI})
    target_link_libraries(TotkToolkit PUBLIC EGL)

    # set up DRM_NOUVEAU as imported target (because it requires LIBNX)
    find_library(DRM_NOUVEAU NAMES drm_nouveau REQUIRED)
    add_library(DRM_NOUVEAU STATIC IMPORTED)
    set_property(TARGET DRM_NOUVEAU PROPERTY IMPORTED_LOCATION ${DRM_NOUVEAU})
    target_link_libraries(DRM_NOUVEAU INTERFACE ${LIBNX_LIBRARY})
    target_link_libraries(TotkToolkit PUBLIC DRM_NOUVEAU)
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(TotkToolkit PUBLIC OpenGL::GL)
    target_link_libraries(TotkToolkit PUBLIC OpenGL::EGL)
endif()