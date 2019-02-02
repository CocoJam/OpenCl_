echo "Building project through cmake"
cd build
cmake -j 10 .. -G Ninja
Ninja
./main
read -p "Press Enter to Close..."