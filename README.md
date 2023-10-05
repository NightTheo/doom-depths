# DoomDepths in C

> OMNES Theo - 5AL1 - 2023 - ESGI

/!\ Readme in progress

## Quick start

1. Installer Conan
```bash
pip install conan
```
---

2. Installer les dépendances
```bash
conan install . --output-folder=cmake-build-debug  --build=missing
cd cmake-build-debug/build
source ./Release/generators/conanbuild.sh
cmake ../ -DCMAKE_TOOLCHAIN_FILE=build/Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
./DoomDepths
```
---



## Architecture
