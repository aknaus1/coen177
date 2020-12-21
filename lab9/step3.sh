echo "gcc step3.c -o Step3"
gcc step3.c -o Step3

for file in file1.txt file2.txt file3.txt file4.txt #file5.txt
do
    for buffer in 100 1000 10000 100000
    do
        echo "Step3 $file $buffer"
        time ./Step3 $file $buffer
        echo " "
    done
done

echo "rm Step3"
rm Step3