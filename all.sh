#!/bin/sh

if [ $# -ne 4 ]; then
  echo "指定された引数は$#個です。" 1>&2
  exit 1
fi

echo $1 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio$1/direction
echo $2 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio$2/direction
echo $3 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio$3/direction
echo $4 > /sys/class/gpio/export
echo in > /sys/class/gpio/gpio$4/direction

exit 0
