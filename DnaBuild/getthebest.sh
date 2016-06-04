#!/bin/bash

res=$(echo "ls $1/*.gen" | bash);
for tmp in $res
do
    echo -e "Start : " $tmp
    ./testdna.sh $tmp
done
