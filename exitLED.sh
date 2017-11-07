#!/bin/bash
# 3つのGPIOを同時にexitにするスクリプト

if [ $# -ne 3 ]; then
  echo "指定された引数は$#個です。" 1>&2
  echo "実行するには3個の引数が必要です。" 1>&2
  exit 1
fi

echo $1 > /sys/class/gpio/unexport

echo $2 > /sys/class/gpio/unexport

echo $3 > /sys/class/gpio/unexport

exit 0
