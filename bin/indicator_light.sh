files=$(shopt -s nullglob dotglob; echo /home/pi/podcast_packager/downloads/*)
if (( ${#files} ))
then
  echo "0" > /sys/class/gpio/gpio4/value
else
  echo "1" > /sys/class/gpio/gpio4/value
fi