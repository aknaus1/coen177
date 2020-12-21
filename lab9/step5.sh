# echo "gcc step5.c -o Step5"
gcc step5.c -o Step5

for file in file4.txt #file5.txt
do
    for buffer in 100 1000 10000 100000
    do
        for thread in 2 8 32 64
        do
            echo "Step5 $file $buffer $thread"
            time ./Step5 $file $buffer $thread
            echo " "
        done
    done
done

# echo "rm Step5"
rm Step5