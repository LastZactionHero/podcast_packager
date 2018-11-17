#!/bin/bash
echo "4" > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio4/direction

if [ -n "$(ls -A /home/pi/podcast_packager/downloads 2>/dev/null)" ]
then
  echo "0" > /sys/class/gpio/gpio4/value
else
  echo "1" > /sys/class/gpio/gpio4/value
fi
