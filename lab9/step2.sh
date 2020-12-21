echo "gcc step2.c -o Step2"
gcc step2.c -o Step2

for file in file1.txt file2.txt file3.txt file4.txt #file5.txt
do
    echo "Step2 $file $buffer"
    time ./Step2 $file $buffer
    echo " "
done

echo "rm Step2"
rm Step2