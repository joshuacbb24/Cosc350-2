#!/bin/sh

if [ "$#" -ne 1 ];
then
echo "You need to pass one numerical argument"
exit 0
fi

value=$1
total=0
while [ "$value" -ne 0 ];
do
let val=$value%10
let total=$total+$val
let value=$value/10
done
echo "$total"
exit 0

