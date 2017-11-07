
if [ $# -ne 3 ]; then
  echo "指定された引数は$#個です。" 1>&2
  echo "実行するには3個の引数が必要です。" 1>&2
  exit 1
fi

echo $1 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio$1/direction
echo $2 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio$2/direction
echo $3 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio$3/direction

echo 1 > /sys/class/gpio/gpio$1/value
sleep 1s
echo 1 > /sys/class/gpio/gpio$2/value
sleep 1s
echo 1 > /sys/class/gpio/gpio$3/value
sleep 1s

echo 0 > /sys/class/gpio/gpio$1/value
sleep 1s
echo 0 > /sys/class/gpio/gpio$2/value
sleep 1s
echo 0 > /sys/class/gpio/gpio$3/value
sleep 1s

echo $1 > /sys/class/gpio/unexport
echo $2 > /sys/class/gpio/unexport
echo $3 > /sys/class/gpio/unexport

exit 0
