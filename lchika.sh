#!/bin/sh
# led signals

GPIOPATH="/sys/class/gpio" GPIO2="${GPIOPATH}/gpio2/value"

echo "led chika chika"

while :
do
echo 1 >${GPIO2} sleep 1s
echo 0 >${GPIO2} sleep 1s
done
