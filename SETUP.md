This document assumes Pure Data is already installed on the Raspberry Pi and that the Teensy is listed as ```/midi/dev/1``` (or something similar).

#Installing the pHAT DAC
### Step 1
- Open the module blacklist file: ```sudo nano /etc/modprobe.d/raspi-blacklist.conf```
- Comment out the following lines:
```
blacklist i2c-bcm2708
blacklist snd-soc-pcm512x
blacklist snd-soc-wm8804
```
to
```
#blacklist i2c-bcm2708
#blacklist snd-soc-pcm512x
#blacklist snd-soc-wm8804
```
- Save and close nano by pressing ```CTRL + X``` then ```y``` and finally ```enter```.
### Step 2
- Open the modules file: ```sudo nano /etc/modules```
- Comment out the following line:
```
snd_bcm2835
```
to
```
#snd_bcm2835
```
### Step 3
- Create ```asounf.conf```: ```sudo nano /etc/asound.conf```
- Enter the following:
```
pcm.!default  {
 type hw card 0
}
ctl.!default {
 type hw card 0
}
```
- Save and close nano by pressing ```CTRL + X``` then ```y``` and finally ```enter```.
### Step 4
- Open ```config.txt```: ```sudo nano /boot/config.txt```
- Add the following line:
```
dtoverlay=hifiberry-dac
```
- Comment out the following line:
```
dtparam=audio=on
```
to
```
#dtparam=audio=on
```
- Save and close nano by pressing ```CTRL + X``` then ```y``` and finally ```enter```.

# Running pd in nogui
### Step 1
- Create the ```/bin``` folder: ```mkdir ./```
- Enter the new folder: ```cd ./bin```
### Step 2
- Create a new script called ```pd_startup```: ```sudo nano pd_startup```
- Add the following line:
```
pd -nogui -midiindev 1 /path/to/your/patch &
```
- Save and close nano by pressing ```CTRL + X``` then ```y``` and finally ```enter```.
- Make the script executable: ```sudo chmod 755 pd_startup```
### Step 3
- Open ```rc.local```: ```sudo nano /etc/rc.local```
- Add the following line:
```
/home/pi/bin/pd_startup
```
- Save and close nano by pressing ```CTRL + X``` then ```y``` and finally ```enter```.
