#!/bin/bash
# 3つのGPIOを同時にoffにするスクリプト

if [ $# -ne 3 ]; then
  echo "指定された引数は$#個です。" 1>&2
  echo "実行するには3個の引数が必要です。" 1>&2
  exit 1
fi


echo 0 > /sys/class/gpio/gpio$1/value
sleep 1s
echo 0 > /sys/class/gpio/gpio$2/value
sleep 1s
echo 0 > /sys/class/gpio/gpio$3/value

exit 0
