#!/usr/bin/bash

echo "Compiling files..."
g++ -o main.exe main.cpp UnionFind.cpp graph.cpp

export LC_NUMERIC="en_US.UTF-8"
TIMEFORMAT=%R

DIR="time/time_v2.txt"
echo "" >$DIR

for i in inputs/*.in
do
  i=$(basename $i)
  i=${i%".in"}
  echo "testing $i..."
  echo -n "$i" >> $DIR
  for run in $(seq 1 $N)
  do
    echo -n "," >> $DIR
    duration=$( { time ./main.exe < inputs/$i".in" > outputs/$i".out" ;} 2>&1)
    echo -n "$duration" >> $DIR
    echo "$duration"
  done
  printf "\n" >> $DIR
done

rm main.exe

echo "Done! Check $DIR for time report"