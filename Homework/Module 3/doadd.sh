#!/bin/bash

echo

echo "What would you like to perform?"
echo "1: SUM"
echo "2: AVERAGE"
echo -n "Enter: "
read COMPUTATION

echo

declare -i NUM1
declare -i NUM2
declare -i NUM3

echo -n "Enter the first integer: " 
read NUM1
echo -n "Enter the second integer: " 
read NUM2
echo -n "Enter the third integer: " 
read NUM3

echo

sum() {
    declare -i TOTAL
    TOTAL=$1+$2+$3
    echo "$1"
    echo "The sum of $1, $2, $3 is: $TOTAL"
}

average() {
    declare -i TOTAL
    declare -i MEAN
    TOTAL=$1+$2+$3
    MEAN=$TOTAL/3
    echo "The average of $1, $2, $3 is: $MEAN"
}

case $COMPUTATION in
    1) sum $NUM1 $NUM2 $NUM3;;
    2) average $NUM1 $NUM2 $NUM3;;
esac

echo

exit 0