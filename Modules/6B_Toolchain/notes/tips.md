# Tips

## CT-NG Build

ISL version 0.26 does not work. Try 0.18

The build process will hang without proper memory allocation. I increased from 1GB to 8GB. I also utilized multi thread or processor build process as defined in menuconfig.

## How To Install Guest Additions Vagrant

[Tutorial](https://developer.hashicorp.com/vagrant/docs/providers/virtualbox/boxes)

```bash
wget http://download.virtualbox.org/virtualbox/7.0.14/VBoxGuestAdditions_7.0.14.iso

sudo mkdir /media/VBoxGuestAdditions

sudo mount -o loop,ro VBoxGuestAdditions_7.0.14.iso /media/VBoxGuestAdditions

sudo sh /media/VBoxGuestAdditions/VBoxLinuxAdditions.run

rm VBoxGuestAdditions_7.0.14.iso

sudo umount /media/VBoxGuestAdditions

sudo rmdir /media/VBoxGuestAdditions
```

## Creating Your Own Static Library

Tips

`-l../libs: The -l flag is used to specify the name of the library to link against, not its path. For example, if your library is named libtest.a or libtest.so, you should use -ltest, not -l../libs.`

Use

```bash
arm-cortex_a8-linux-gnueabihf-gcc hello.c -ltest -L../libs -o hello_S
```

Not

```bash
rm-cortex_a8-linux-gnueabihf-gcc hello.c -ltest -L../libs -l../libs -o hello_S
```
