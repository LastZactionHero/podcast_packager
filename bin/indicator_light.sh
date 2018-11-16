#!/bin/bash
if [ -n "$(ls -A /home/pi/podcast_packager/downloads 2>/dev/null)" ]
then
  echo "0" > /sys/class/gpio/gpio4/value
else
  echo "1" > /sys/class/gpio/gpio4/value
fi