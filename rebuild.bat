cd build
cmake .. -G "Visual Studio 15 2017 Win64" -DCMAKE_CXX_FLAGS=/D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING
cd ..
cmake --build build --config debug
cd build/debug && main
cd ../..