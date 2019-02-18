rm -r build && mkdir build
echo "Building project through cmake"
cd build
# cmake .. -G "Ninja"
# Ninja
cmake .. -G "Visual Studio 15 2017 Win64"
cd ..
cmake --build build --config release
cd build/release && ./main

# ./main
read -p "Press Enter to Close..."