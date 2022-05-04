#!/bin/sh
echo "you pass $# arguments"
value=$1
count=1
total=1
while [ "$count" -le "$value" ];
do
let total=total*count
let count++
done
echo "$total"
exit 0

