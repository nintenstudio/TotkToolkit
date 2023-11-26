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

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

project (TotkToolkit C CXX)
add_executable(TotkToolkit "Public/TotkToolkit/TotkToolkit.h" "Private/TotkToolkit/TotkToolkit.cpp" "Public/TotkToolkit/UI/Window.h" "Private/TotkToolkit/UI/Window.cpp" "Public/TotkToolkit/UI/ImGuiItem.h" "Public/TotkToolkit/UI/Windows/Filesystem/Browser.h" "Private/TotkToolkit/UI/Windows/Filesystem/Browser.cpp" "Public/TotkToolkit/UI/Localization/TranslationSource.h" "Private/TotkToolkit/UI/ImGuiItem.cpp" "Public/TotkToolkit/UI/MainWindow.h" "Private/TotkToolkit/UI/MainWindow.cpp" "Public/TotkToolkit/UI/Windows/Editors/Text.h" "Private/TotkToolkit/UI/Windows/Editors/Text.cpp" "Public/TotkToolkit/IO/Editor.h" "Public/TotkToolkit/UI/Windows/Editors/PlainText.h" "Private/TotkToolkit/UI/Windows/Editors/PlainText.cpp" "Public/TotkToolkit/UI/Windows/Rendering/Viewport.h" "Private/TotkToolkit/UI/Windows/Rendering/Viewport.cpp" "Public/TotkToolkit/Rendering/Framebuffer.h" "Public/TotkToolkit/Rendering/Texture.h" "Private/TotkToolkit/Rendering/Texture.cpp"  "Private/TotkToolkit/Rendering/Framebuffer.cpp" "Public/TotkToolkit/Rendering/DeviceFeatures.h" "Private/TotkToolkit/Rendering/DeviceFeatures.cpp" "Public/TotkToolkit/Rendering/RenderingSystem.h" "Private/TotkToolkit/Rendering/RenderingSystem.cpp" "Public/TotkToolkit/Rendering/DebugMessageHandler.h" "Private/TotkToolkit/Rendering/DebugMessageHandler.cpp" "Public/TotkToolkit/UI/Windows/Configuration/Settings.h" "Private/TotkToolkit/UI/Windows/Configuration/Settings.cpp" "Public/TotkToolkit/UI/Windows/Editors/BYML.h" "Private/TotkToolkit/UI/Windows/Editors/BYML.cpp" "Public/TotkToolkit/IO/Filesystem.h" "Public/TotkToolkit/IO/Streams/Physfs/Physfs.h" "Private/TotkToolkit/IO/Streams/Physfs/Physfs.cpp" "Private/TotkToolkit/IO/Streams/Physfs/EndianReaders/Little.h" "Private/TotkToolkit/IO/Streams/Physfs/EndianReaders/Big.h" "Private/TotkToolkit/IO/Filesystem.cpp" "Public/TotkToolkit/Configuration/Settings.h" "Private/TotkToolkit/Configuration/Settings.cpp" "Public/TotkToolkit/Messaging/NoticeBoard.h" "Public/TotkToolkit/Messaging/Receiver.h" "Public/TotkToolkit/Messaging/Notice.h" "Private/TotkToolkit/Messaging/NoticeBoard.cpp" "Public/TotkToolkit/Messaging/NoticeType.h" "Public/TotkToolkit/Messaging/Notices/Configuration/Settings/Change/DumpDir.h" "Private/TotkToolkit/Messaging/Notices/Configuration/Settings/Change/DumpDir.cpp" "Public/TotkToolkit/Messaging/Notices/Configuration/Settings/Change/WriteDir.h" "Private/TotkToolkit/Messaging/Notices/Configuration/Settings/Change/WriteDir.cpp" "Public/TotkToolkit/Messaging/ExternalReceivers/IO/Filesystem.h" "Private/TotkToolkit/Messaging/ExternalReceivers/IO/Filesystem.cpp" "Private/TotkToolkit/Messaging/Notice.cpp" "Public/TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.h" "Private/TotkToolkit/Messaging/Notices/IO/Filesystem/FilesChange.cpp" "Public/TotkToolkit/UI/Icons.h" "Public/TotkToolkit/UI/EditorSystem.h" "Public/TotkToolkit/UI/Windows/Editor.h" "Public/TotkToolkit/Messaging/ExternalReceivers/UI/EditorSystem.h" "Private/TotkToolkit/Messaging/ExternalReceivers/UI/EditorSystem.cpp" "Private/TotkToolkit/UI/EditorSystem.cpp" "Private/TotkToolkit/UI/Windows/Editor.cpp" "Public/TotkToolkit/IO/FileHandle.h" "Private/TotkToolkit/IO/FileHandle.cpp" "Private/TotkToolkit/IO/Editor.cpp" "Public/TotkToolkit/UI/Fonts.h" "Private/TotkToolkit/UI/Fonts.cpp" "Public/TotkToolkit/Threading/Task.h" "Private/TotkToolkit/Threading/Task.cpp" "Public/TotkToolkit/Threading/TaskReport.h" "Private/TotkToolkit/Threading/TaskReport.cpp" "Public/TotkToolkit/Threading/Tasks/IO/Filesystem/MountArchives.h" "Private/TotkToolkit/Threading/Tasks/IO/Filesystem/MountArchives.cpp" "Public/TotkToolkit/IO/Streams/File/File.h" "Private/TotkToolkit/IO/Streams/File/File.cpp" "Private/TotkToolkit/IO/Streams/File/EndianReaders/Big.h" "Private/TotkToolkit/IO/Streams/File/EndianReaders/Little.h" "Public/TotkToolkit/IO/PHYSFSCall.h" "Public/TotkToolkit/IO/PHYSFSCalls/Mount.h" "Public/TotkToolkit/IO/PHYSFSCalls/MountMemory.h" "Public/TotkToolkit/IO/PHYSFSCalls/Unmount.h" "Private/TotkToolkit/IO/PHYSFSCalls/Mount.cpp" "Private/TotkToolkit/IO/PHYSFSCalls/MountMemory.cpp" "Private/TotkToolkit/IO/PHYSFSCalls/Unmount.cpp" "Public/TotkToolkit/Threading/Mutexes/SharedRecursive.h" "Public/TotkToolkit/IO/PHYSFSCalls/SetWriteDir.h" "Private/TotkToolkit/IO/PHYSFSCalls/SetWriteDir.cpp" "Public/TotkToolkit/UI/Windows/Editors/Texture.h" "Private/TotkToolkit/UI/Windows/Editors/Texture.cpp" "Public/TotkToolkit/UI/Windows/Editors/TXTG.h" "Private/TotkToolkit/UI/Windows/Editors/TXTG.cpp" "Public/TotkToolkit/Resources/TexToGo.h" "Private/TotkToolkit/Resources/TexToGo.cpp" "Public/TotkToolkit/Rendering/TextureCompression.h" "Private/TotkToolkit/Rendering/TextureCompression.cpp" "Public/TotkToolkit/UI/ErrorSystem.h" "Private/TotkToolkit/UI/ErrorSystem.cpp" "Public/TotkToolkit/Messaging/Notices/Errors/UI/Windows/Editor/ParseFailed.h" "Private/TotkToolkit/Messaging/Notices/Errors/UI/Windows/Editor/ParseFailed.cpp" "Public/TotkToolkit/Messaging/Notices/Error.h" "Private/TotkToolkit/Messaging/Notices/Error.cpp" "Public/TotkToolkit/Messaging/ExternalReceivers/UI/ErrorSystem.h" "Private/TotkToolkit/Messaging/ExternalReceivers/UI/ErrorSystem.cpp" "Public/TotkToolkit/Messaging/Notices/Configuration/Settings/Change/BfresDir.h" "Private/TotkToolkit/Messaging/Notices/Configuration/Settings/Change/BfresDir.cpp" "Public/TotkToolkit/UI/Windows/Configuration/Style.h" "Private/TotkToolkit/UI/Windows/Configuration/Style.cpp" "Public/TotkToolkit/UI/ImGuiUtil.h")
set_target_properties(TotkToolkit PROPERTIES APP_TITLE "TotkToolkit" APP_AUTHOR "Me" APP_VERSION "1.0.0" ROMFS "${CMAKE_CURRENT_SOURCE_DIR}/Romfs")

copy_directory_recursive(${CMAKE_CURRENT_SOURCE_DIR}/Romfs/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources)

if (MSVC)
target_compile_options(TotkToolkit PUBLIC "/utf-8")
endif()

# Include this
target_include_directories(TotkToolkit PRIVATE Private Public)

# Use Formats
add_subdirectory(Lib/Formats)
target_link_libraries(TotkToolkit PUBLIC Formats)

# Use Fallback
add_subdirectory(Lib/Fallback)
target_link_libraries(TotkToolkit PUBLIC Fallback)
#target_include_directories(TotkToolkit PUBLIC $<TARGET_PROPERTY:Fallback,INTERFACE_INCLUDE_DIRECTORIES>)

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

# Use Sarc_Archiver
set(PHYSFS_TARGETNAME_UNINSTALL "physfs_uninstall" CACHE STRING "" FORCE) # Avoid conflicting uninstall targets
add_subdirectory(Lib/Sarc_Archiver)
target_link_libraries(TotkToolkit PUBLIC sarc_archiver)

# Use ASTC-Encoder
set(ASTCENC_CLI OFF CACHE BOOL "" FORCE)
add_subdirectory(Lib/ASTC-Encoder)
target_link_libraries(TotkToolkit PUBLIC astcenc-native-static)

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
    target_include_directories(physfs-static SYSTEM PUBLIC ${LIBNX_INCLUDE_DIR})

    message(STATUS "SRC DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
    message(STATUS "BIN DIR: ${CMAKE_CURRENT_BINARY_DIR}")
    file(COPY ${PORTLIBS}/include/GLFW ${PORTLIBS}/include/KHR ${PORTLIBS}/include/EGL DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/PortlibsInclude)

    # Include PORTLIBS
    target_include_directories(glfw PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/PortlibsInclude>
        $<INSTALL_INTERFACE:PortlibsInclude>
    )

    # Set up GLAPI
    find_library(GLAPI NAMES glapi REQUIRED)
    target_link_libraries(TotkToolkit PUBLIC ${GLAPI})

    # Give GLAD PORTLIBS include path so it can load KHR/khrplatform.h
    target_include_directories(GLAD PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/PortlibsInclude>
        $<INSTALL_INTERFACE:PortlibsInclude>
    )

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