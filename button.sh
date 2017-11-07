#!/bin/sh
# button check

GPIOPATH="/sys/class/gpio"



if [ $1 = 'init' ]; then
echo '5' > ${GPIOPATH}/export
echo 'in' > ${GPIOPATH}/gpio5/direction
echo 'both' > ${GPIOPATH}/gpio5/edge

echo '2' > ${GPIOPATH}/export
echo 'out' > ${GPIOPATH}/gpio2/direction
echo '0' > ${GPIOPATH}/gpio2/value
fi

while :
do
RET=`cat ${GPIOPATH}/gpio5/value`
if [ ${RET} = '0' ]; then
echo '1' > ${GPIOPATH}/gpio2/value
else
echo '0' > ${GPIOPATH}/gpio2/value
fi
sleep 1s
done
