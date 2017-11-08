#!/bin/sh
echo 5 > /sys/class/gpio/export
echo 'in' > /sys/class/gpio/gpio5/direction
echo 'rising' > /sys/class/gpio/gpio5/edge

echo 2 > /sys/class/gpio/export
echo 3 > /sys/class/gpio/export
echo 4 > /sys/class/gpio/export
echo 'out' > /sys/class/gpio/gpio2/direction
echo 'out' > /sys/class/gpio/gpio3/direction
echo 'out' > /sys/class/gpio/gpio4/direction

