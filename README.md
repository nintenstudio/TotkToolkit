# TotkToolkit
An editor for The Legend of Zelda: Tears of the Kingdom

## Building from source
### For desktop
To build for windows, simply use CMake to generate build files and then use your compiler of choice to compile them.
### For switch
### Prerequisites
* ``libnx`` - install from instructions at https://switchbrew.org/wiki/Setting_up_Development_Environment. You'll also need to make sure the ``DEVKITPRO`` environment variable is set up correctly, and that ``DEVKITPRO/tools/bin`` is in PATH. 
Use CMake to build for switch. Make sure that it is using the toolchain file at ``Lib/Switch-CMake/DevkitA64Libnx.cmake``
