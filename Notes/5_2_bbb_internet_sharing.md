
# sharing internet with beaglebone black over usb

1.
    - make sure to enable the bbb by going to the device tab and select usb and select circutco beagleboneblack only the device in available

2.
    - do an ifconfig and determine the internet interface and the bbb interface, on my machine they are enp0s3 and

    - enx0479b7ec9c69 respectively. (enx0479b7ec9c69 associated with 192.168.7.2)

    - the ip addresses of the usb network connection are:

    - ubuntu computer: 192.168.7.1

    - beaglebone black: 192.168.7.2

    - but when i log into the bbb, it cannot go out to the internet.

    - so, i will attempt to share my ubuntu's internet connection to the bbb via the usb network connection:

3.
    - ssh to the bbb:
    - ssh 192.168.7.2 –l root

4.
    - in the bbb console type the following:
    - sudo ifconfig usb0 192.168.7.2
    - sudo route add default gw 192.168.7.1

5.
    - in the linux console of host system (ubuntu) type:
    - sudo ifconfig enx0479b7ec9c69 192.168.7.1
    - sudo iptables --table nat --append postrouting --out-interface enp0s3 -j masquerade
    - sudo iptables --append forward --in-interface enx0479b7ec9c69 -j accept
    - sudo echo 1 > /proc/sys/net/ipv4/ip_forward
    - (if you get an error on the last statement or if you do sudo cat /proc/sys/net/ipv4/ip_forward and it prints out a 0,then do the following)
    sudo bash -c 'echo 1 > /proc/sys/net/ipv4/ip_forward'
6.
    - set the dns server address in the bbb console:
    - echo "nameserver 8.8.8.8" >> /etc/resolv.conf
    - (if you get an error, then cd /etc, sudo nano resolv.conf, and enter nameserver 8.8.8.8 after the comment) then ctrl-o and ctrl-x to save and exit

7.
    - to test connection do, ping google.com and it should work.
