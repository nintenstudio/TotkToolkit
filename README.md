# TotkToolkit
An editor for The Legend of Zelda: Tears of the Kingdom.

## **Building from source**
TotkToolkit can be built from source for Windows, Linux, and Nintendo Switch. To build for Linux or Switch, a codespace can be created off of this repo and things will work right away. To build for Windows or Switch, or to build on one's own Linux installation, further setup is required.
### *For desktop*
To build for windows or linux, simply use CMake to generate build files and then use your compiler of choice to compile them.
#### Prerequisites
* ``rust`` - run the command ``curl --proto '=https' --tlsv1.3 https://sh.rustup.rs -sSf | sh`` to install. 
### *For switch*
#### Prerequisites
* ``libnx`` - install from instructions at https://switchbrew.org/wiki/Setting_up_Development_Environment. You'll also need to make sure the ``DEVKITPRO`` environment variable is set up correctly, and that ``DEVKITPRO/tools/bin`` is in PATH.
* ``rust`` - run the command ``curl --proto '=https' --tlsv1.3 https://sh.rustup.rs -sSf | sh`` to install. 

Use CMake to build for switch. Make sure that it is using the toolchain file at ``Lib/Switch-CMake/DevkitA64Libnx.cmake``.

## *Example ``CMakeUserPresets.json``*
There doesn't seem to be a way to layer ``CMakeUserPresets.json`` over ``CMakePresets.json`` properly, so here's one to start with:
```json
{
    "version": 3,
    "configurePresets": [
        {
            "name": "windows-base",
            "hidden": true,
            "binaryDir": "${sourceDir}/out/build/${presetName}",
            "installDir": "${sourceDir}/out/install/${presetName}",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "cl.exe",
                "CMAKE_CXX_COMPILER": "cl.exe"
            },
            "condition": {
                "type": "equals",
                "lhs": "${hostSystemName}",
                "rhs": "Windows"
            }
        },
        {
            "name": "linux-base",
            "hidden": true,
            "binaryDir": "${sourceDir}/out/build/${presetName}",
            "installDir": "${sourceDir}/out/install/${presetName}",
            "cacheVariables": {
                "CMAKE_C_COMPILER": "clang",
                "CMAKE_CXX_COMPILER": "clang++"
            },
            "condition": {
                "type": "equals",
                "lhs": "${hostSystemName}",
                "rhs": "Linux"
            }
        },
        {
            "name": "switch-base",
            "hidden": true,
            "binaryDir": "${sourceDir}/out/build/${presetName}",
            "installDir": "${sourceDir}/out/install/${presetName}",
            "cacheVariables": {
                "CMAKE_TOOLCHAIN_FILE": "Lib/Switch-CMake/DevkitA64Libnx.cmake"
            }
        },
        {
            "name": "x64-debug-windows",
            "displayName": "x64 Debug (Windows)",
            "inherits": "windows-base",
            "architecture": {
                "value": "x64",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        },
        {
            "name": "x64-release-windows",
            "displayName": "x64 Release (Windows)",
            "inherits": "x64-debug-windows",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release"
            }
        },
        {
            "name": "x86-debug-windows",
            "displayName": "x86 Debug (Windows)",
            "inherits": "windows-base",
            "architecture": {
                "value": "x86",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        },
        {
            "name": "x86-release-windows",
            "displayName": "x86 Release (Windows)",
            "inherits": "x86-debug-windows",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release"
            }
        },
        {
            "name": "x64-debug-linux",
            "displayName": "x64 Debug (Linux)",
            "inherits": "linux-base",
            "architecture": {
                "value": "x64",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        },
        {
            "name": "x64-release-linux",
            "displayName": "x64 Release (Linux)",
            "inherits": "x64-debug-linux",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release"
            }
        },
        {
            "name": "x86-debug-linux",
            "displayName": "x86 Debug (Linux)",
            "inherits": "linux-base",
            "architecture": {
                "value": "x86",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        },
        {
            "name": "x86-release-linux",
            "displayName": "x86 Release (Linux)",
            "inherits": "x86-debug-linux",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release"
            }
        },
        {
            "name": "x64-debug-switch",
            "displayName": "x64 Debug (Switch)",
            "inherits": "switch-base",
            "architecture": {
                "value": "x64",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        },
        {
            "name": "x64-release-switch",
            "displayName": "x64 Release (Switch)",
            "inherits": "x64-debug-switch",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release"
            }
        },
        {
            "name": "x86-debug-switch",
            "displayName": "x86 Debug (Switch)",
            "inherits": "switch-base",
            "architecture": {
                "value": "x86",
                "strategy": "external"
            },
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Debug"
            }
        },
        {
            "name": "x86-release-switch",
            "displayName": "x86 Release (Switch)",
            "inherits": "x86-debug-switch",
            "cacheVariables": {
                "CMAKE_BUILD_TYPE": "Release"
            }
        }
    ]
}
```
