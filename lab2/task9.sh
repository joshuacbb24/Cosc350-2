#!/bin/sh
echo "enter directory name"
read dirname
count=0
if [ -d "$dirname" ]; 
then
echo "directory exists"
echo "what is the file name"
read file
while [ ! -f "$file" ]; do
let count++
if [ "$count" -ge 3 ]; then
echo "File does not exist."
exit 2
fi
echo "File does not exist. what is the file name?"
read file
done
if [ -f "$file" ]; then
if [ -r "$file" ]; then
echo "what word do you want found?"
read word
if grep -q $word $file
then
echo "$word found"
exit 0
else
echo "$word not found"
exit 4
fi
else
echo "file is not readable"
exit 3
fi
fi
else
echo "no such directory"
exit 1
fi