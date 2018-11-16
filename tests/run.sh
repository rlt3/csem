#!/bin/bash

while read line; do                                                                
    prog=$(echo $line | awk '{print $1}')
    val=$(echo $line | awk '{print $2}')
    ./csem < tests/$prog > tmp.ll
	clang -Wno-everything tmp.ll -o prog
    ./prog
    if [ $? -ne $val ]; then                                                           
        echo "$prog failed!"
        exit 1                                                                      
    fi 
    echo "$prog passed."
done < tests/expected.txt  

rm -f tmp.ll
rm -f prog
echo "All tests passed. Good job."
