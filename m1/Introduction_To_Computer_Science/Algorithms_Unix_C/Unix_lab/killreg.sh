#!/bin/sh

if [ -z "$1" ] && [ -z "$2" ]
then
    echo "Error , at least one argument is required !"
    echo "Usage: ./killreg [-SIGNAL] <PATTERN>"
    echo "-SIGNAL: an optional signal to pass to the programs that match the <PATTERN>, e.g., -9, -TERM, etc. By default the -TERM signal is sent ."
    echo "PATTERN: a requried pattern , ./ killreg kills all processes which match this pattern ."
fi

if [ "`echo $1 |grep ^-`" = "" ] && [ $# -eq 2 ]
then   
    echo "Error, the first argument must start with a hyphen"
    echo "Usage: ./killreg [-SIGNAL] <PATTERN>"
    echo "-SIGNAL: an optional signal to pass to the programs that match the <PATTERN>, e.g., -9, -TERM, etc. By default the -TERM signal is sent ."
    echo "PATTERN: a requried pattern , ./ killreg kills all processes which match this pattern ."
fi

if [ -z "$1" ] && [ $# -eq 1 ]
then
    r1=`ps | awk '{print $4}' | grep "$1"`
    killall -TERM $r1 / 2>/dev/null
fi

if [ $# -eq 2 ] && [ "`echo "$1" |grep ^-`" != "" ] 
then 
    com2=`ps | awk '{print $4}' | grep "$2"`
    killall $1 $com2 / 2>/dev/null
fi