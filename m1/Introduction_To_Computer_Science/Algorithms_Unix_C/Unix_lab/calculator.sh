#!/bin/sh

if [ -z "$1" ] || [ -z "$2" ]
then
    echo "Please Enter operand a:"
    read a
    echo "Please Enter operand b:"
    read b
    echo sum $a '+' $b = $[$a+$b]
    echo diff $a '-' $b = $[$a-$b]
    echo mult $a '*' $b = $[$a*$b]
    echo div $a '/' $b = $[$a/$b]
else
    echo sum $1 '+' $2 = $[$1+$2]
    echo diff $1 '-' $2 = $[$1-$2]
    echo mult $1 '*' $2 = $[$1*$2]
    echo div $1 '/' $2 = $[$1/$2]
fi
