function(copy_directory_recursive source_dir destination_dir)
    file(GLOB files_to_copy "${source_dir}/*")
    foreach(file ${files_to_copy})
        if(IS_DIRECTORY ${file})
            get_filename_component(dir_name ${file} NAME)
            set(destination_dir "${destination_dir}/${dir_name}")
            file(MAKE_DIRECTORY ${destination_dir})
            copy_directory_recursive(${file} ${destination_dir})
        else()
            get_filename_component(file_name ${file} NAME)
            set(destination_file "${destination_dir}/${file_name}")
            configure_file(${file} ${destination_file} COPYONLY)
        endif()
    endforeach()
endfunction()

cmake_minimum_required (VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

project (TotkToolkit C CXX)
add_executable(TotkToolkit "Public/TotkToolkit/TotkToolkit.h" "Private/TotkToolkit/TotkToolkit.cpp" "Public/TotkToolkit/UI/Windows/Window.h" "Private/TotkToolkit/UI/Windows/Window.cpp" "Public/TotkToolkit/UI/ImGuiItem.h" "Public/TotkToolkit/UI/Windows/Filesystem/Browser.h" "Private/TotkToolkit/UI/Windows/Filesystem/Browser.cpp" "Public/TotkToolkit/UI/Localization/TranslationSource.h" "Private/TotkToolkit/UI/ImGuiItem.cpp" "Public/TotkToolkit/UI/MainWindow.h" "Private/TotkToolkit/UI/MainWindow.cpp" "Public/TotkToolkit/UI/Windows/Editors/Text.h" "Private/TotkToolkit/UI/Windows/Editors/Text.cpp" "Public/TotkToolkit/IO/Editor.h" "Public/TotkToolkit/UI/Windows/Editors/PlainText.h" "Private/TotkToolkit/UI/Windows/Editors/PlainText.cpp" "Public/TotkToolkit/UI/Windows/Rendering/Viewport.h" "Private/TotkToolkit/UI/Windows/Rendering/Viewport.cpp" "Public/TotkToolkit/Rendering/Framebuffer.h" "Public/TotkToolkit/Rendering/Texture.h" "Private/TotkToolkit/Rendering/Texture.cpp"  "Private/TotkToolkit/Rendering/Framebuffer.cpp" "Public/TotkToolkit/Rendering/DeviceFeatures.h" "Private/TotkToolkit/Rendering/DeviceFeatures.cpp" "Public/TotkToolkit/Rendering/RenderingSystem.h" "Private/TotkToolkit/Rendering/RenderingSystem.cpp" "Public/TotkToolkit/Rendering/DebugMessageHandler.h" "Private/TotkToolkit/Rendering/DebugMessageHandler.cpp" "Public/TotkToolkit/UI/Windows/Configuration/Settings.h" "Private/TotkToolkit/UI/Windows/Configuration/Settings.cpp" "Public/TotkToolkit/UI/Windows/Editors/BYML.h" "Private/TotkToolkit/UI/Windows/Editors/BYML.cpp")
set_target_properties(TotkToolkit PROPERTIES APP_TITLE "TotkToolkit" APP_AUTHOR "Me" APP_VERSION "1.0.0" ROMFS "${CMAKE_CURRENT_SOURCE_DIR}/Romfs")

copy_directory_recursive(${CMAKE_CURRENT_SOURCE_DIR}/Romfs/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources)

# Include this
target_include_directories(TotkToolkit PRIVATE Private Public)

# Use Formats
target_include_directories(TotkToolkit PUBLIC Lib/Formats/Public Lib/ImGui)
add_subdirectory(Lib/Formats)
target_link_libraries(TotkToolkit PUBLIC Formats)

# Use GLFW
if (SWITCH)
    SET(NINTENDO_SWITCH ON) # For GLFW
    SET(SWITCH_LIBNX ON) # For GLFW (Doesn't do too much...)
endif()
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
if (SWITCH)
    set(GLFW_EGL_STATIC ON CACHE BOOL "" FORCE)
else()
    set(GLFW_EGL_STATIC OFF CACHE BOOL "" FORCE)
endif()
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

# Use ImGui
include(${CMAKE_CURRENT_SOURCE_DIR}/ImGui.cmake)
target_include_directories(ImGui PUBLIC "Lib/GLFW/include")
target_include_directories(TotkToolkit PUBLIC Lib/ImGui)
target_link_libraries(TotkToolkit PUBLIC ImGui)

# Use ImGuiColorTextEdit
include(${CMAKE_CURRENT_SOURCE_DIR}/ImGuiColorTextEdit.cmake)
target_include_directories(TotkToolkit PUBLIC Lib/ImGuiColorTextEdit)
target_link_libraries(TotkToolkit PUBLIC ImGuiColorTextEdit)

# Prefer more modern OpenGL. Especially matters when not building for switch.
set(OpenGL_GL_PREFERENCE GLVND)

# Make sure we can use multiple thrads.
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

target_link_libraries(TotkToolkit PUBLIC Threads::Threads)

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
    if (OpenGL_EGL_FOUND)
        target_link_libraries(TotkToolkit PUBLIC OpenGL::EGL)
    else() # Fallback EGL is provided as a submodule
        target_include_directories(GLAD PUBLIC Lib/EGL-Registry/api)
    endif()
endif()

# For when Sarc_Arhiver is useful:
#add_subdirectory(Lib/Sarc_Archiver)