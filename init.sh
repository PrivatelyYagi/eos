#!/bin/sh

GPIOPATH="/sys/class/gpio"

echo 2 > ${GPIOPATH}/export
echo 'out' > ${GPIOPATH}/gpio2/direction
echo 3 > ${GPIOPATH}/export
echo 'out' > ${GPIOPATH}/gpio3/direction
echo 4 > ${GPIOPATH}/export
echo 'out' > ${GPIOPATH}/gpio4/direction
echo 5 > ${GPIOPATH}/export
echo 'in' > ${GPIOPATH}/gpio5/direction
echo 'rising' > ${GPIOPATH}/gpio5/edge
