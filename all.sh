#!/bin/sh

GPIOPATH="/sys/class/gpio"

if [ $# -ne 4 ]; then
  echo "指定された引数は$#個です。" 1>&2
  exit 1
fi

echo $1 > ${GPIOPATH}/export
echo 'out' > ${GPIOPATH}/gpio$1/direction
echo $2 > ${GPIOPATH}/export
echo 'out' > ${GPIOPATH}/gpio$2/direction
echo $3 > ${GPIOPATH}/export
echo 'out' > ${GPIOPATH}/gpio$3/direction
echo $4 > ${GPIOPATH}/export
echo 'in' > ${GPIOPATH}/gpio$4/direction
echo 'both' > ${GPIOPATH}/gpio5/edge
exit 0
