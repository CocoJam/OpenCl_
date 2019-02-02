echo "Running Test Scripts..."
cd Build/Test
for name in *.exe
do
     "./"$name
done

read -p "Press Enter to Close..."
