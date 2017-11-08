#!/bin/sh

if [ $# -ne 4 ]; then
  echo "指定された引数は$#個です。" 1>&2
  exit 1
fi

echo $1 > /sys/class/gpio/unexport
echo $2 > /sys/class/gpio/unexport
echo $3 > /sys/class/gpio/unexport
echo $4 > /sys/class/gpio/unexport

exit 0