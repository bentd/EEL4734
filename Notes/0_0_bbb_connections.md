# How To Connect

## SSH

Only works through USB connection.

Depending on the IP address of the device, you can ssh into the device using XX.XXX.XXX.XX

`ssh debian@beaglebone.local`

OR

`ssh debian@192.168.6.2`

## Serial

Only works through serial connection with cable that uses Prolific Controller PL2303. Will need to download Prolific Driver App from macOS Store.

This allows you to either `screen` command to create a serial connection into the beaglebone black in macOS and vagrant.

`screen /dev/ttyUSB0 115200`

## VirtualBox

For use with virtualbox and vagrant you must enable USB Controller in virtual machine settings and add the devices before image boot.
