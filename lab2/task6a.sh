#!/bin/sh
echo "enter an odd number greater than 3"
read number
divisor=2
let remainder=$number%$divisor
while [ "$number" -le 3 -o "$remainder" -eq 0 ]; do
echo "incorrect entry"
echo "enter an odd number greater than 3"
read number
let remainder=$number%$divisor
done

let spaces=$number/2
let divisor=$number/2
stars=1
for i in $(seq 1 $number);
do

if [ "$i" -le "$divisor" ]
then
for j in $(seq 1 $spaces);
do
echo -n " "
done
for j in $(seq 1 $stars);
do
echo -n "*"
done
echo
let spaces--
let stars=$stars+2

else
for j in $(seq 1 $spaces);
do
echo -n " "
done
for j in $(seq 1 $stars);
do
echo -n "*"
done
echo
let spaces++
let stars=$stars-2
fi
done
exit 0