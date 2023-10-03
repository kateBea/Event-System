# Event-System
Some event queue implementation. Captures events from a window and sends them to an app.

# Screenshots

# Building

The requirements are:
- CMake 3.21 (This is what the project uses, but an earlier version is most likely to work).
- compiler capable of C++20 (G++ 12.3.0 was used for the tests).

For building, see the following steps from the terminal (should work on both linux and Windows PowerShell).
On the later you might get solution files from which you have to manually build and run the project
```shell
  # Clone the repository to your desired directory
  git clone --recursive https://github.com/kateBea/Mikoto-Engine.git
  
  # Change directory to the repo folder
  cd Mikoto-Engine
  
  # Make a build directory (preferable)
  mkdir build 
  
  # and open the build directory
  cd build
  
  # Run CMake on the CMake file from the repo root directory
  cmake -S .. -B .
  
  # Finally build the project
  cmake --build . --config Release
  
  # and run the executable (if on Linux, the executable should be in build folder)
  ./Mikoto
```