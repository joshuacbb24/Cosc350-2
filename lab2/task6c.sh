#!/bin/sh
echo "enter a number for the tail"
read tnumber
echo "enter an odd number for the base"
read bnumber
divisor=2
let remainder=$bnumber%$divisor
while [ "$remainder" -eq 0 ]; do
echo "incorrect entry"
echo "enter an odd number for the base"
read bnumber
let remainder=$bnumber%$divisor
done

let spaces=$bnumber-1
let divisor=$bnumber/2
let halfway=$divisor+1
stars=1

for i in $(seq 1 $bnumber);
do
if [ "$i" -le "$divisor" ]
then
for j in $(seq 1 $tnumber);
do
echo -n " "
done
for j in $(seq 1 $stars);
do
echo -n "*"
done
for j in $(seq 1 $spaces);
do
echo -n " "
done
echo
let spaces=$spaces-2
let stars=$stars+2

else
if [ "$i" -eq "$halfway" ];
then
let tnumbertwo=$tnumber+$stars
for k in $(seq 1 $tnumbertwo);
do
echo -n "*"
done
else
for j in $(seq 1 $tnumber);
do
echo -n " "
done
for j in $(seq 1 $stars);
do
echo -n "*"
done
fi
for j in $(seq 1 $spaces);
do
echo -n " "
done
echo
let spaces=$spaces+2
let stars=$stars-2
fi
done
exit 0