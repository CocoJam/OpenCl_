cd build
cmake .. -G "Visual Studio 15 2017 Win64"
cd ..
cmake --build build --config debug
cd build/debug && main
cd ../..