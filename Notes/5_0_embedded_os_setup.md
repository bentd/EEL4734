# Video Notes

## Video 1

[Link](https://web.eng.fiu.edu/aperezpo/Emb_OS_video/Emb_OS_BBB_rec0/Emb_OS_BBB_rec0.html)

```bash
sudo apt-get install picocom
ls -l /dev/ttyUSB0
sudo adduser $USER dialout
sudo picocom -b 115200 /dev/tty/USB0
```

## Video 2

[Link](https://web.eng.fiu.edu/aperezpo/Emb_OS_video/Emb_OS_BBB_rec1/Emb_OS_BBB_rec1.html)

```bash
sudo apt-get update
sudo apt-get install screenfetch
screenfetch # shows info about os
sudo apt-get install build-essential
sudo apt-get install gcc-arm-linux-gnueabi # installs gcc compiler/toolchain for target beaglebone not laptop x86
sudo apt-get install g++-arm-linux-gnueabi # installs g++ compiler/toolchain for target beaglebone not laptop x86
mkdir ~/test
cd ~/test
gedit hello.c
ls

gcc -o hellox86 hello.c # dynamically compiles executable and includes symbolic references to libraries which the os dynamic linker (ld.so or ld-linux.so) will then resolve those libraries at runtime by searching /lib, /usr/lib, etcetera

# -o or nothing results in executable
# -c results strictly in object files

# -rpath or -rpath-link includes directories manually into the executable if the 

# ldd helps find what libraries are needed for an executable

./hellox86

ls -l # see size of files

file hellox86 # see info about file and for what processor and file format (ELF)

gcc -o hellox86s hello.c -static # compiles static executable which statically links all the library into executable

arm-linux-gnueabi-gcc -o helloARM hello.c # compiles for target beaglebone

ls
ls -l # will notice that arm executable is smaller given the 32 bit opcodes of arm vs 64 bit opcodes of the x86 instruction set

./helloARM # will result in error since /lib/ld-linux.so.3 cannot be found on x86 system

arm-linux-gnueabi-gcc -o helloARMs hello.c -static  #statically linked executable for arm which is bigger

./helloARMs # will run if QEMU arm emulator is running which will let you run the program as if on arm system

sudo apt-get install qemu # qemu emulator which let you run arm code with virtualized arm processor or virtualized beaglebone but cannot virtualize hardware like LEDs

cd /usr

ls -l # arm-linux-gnueabi and arm-linux-gnueabihf are directories which contain shared libraries for program execution (the hf is hard floating point library that uses native floating point processor for certain math operations like trig)

cd arm-linux-gnueabi/lib # contains libraries for code execution

cd ~/test

sudo apt-get install qemu-user -y

qemu-arm -L /usr/arm-linux-gnueabi helloARM # this will work since it will emulate arm processor with the included arm libraries with the c toolchain


```

[hello.c]

``` c
#include <stdio.h>

int main() {
    printf("Hello Linux World\n");
    return 0;
}
```

## Video 3

[Link](https://web.eng.fiu.edu/aperezpo/Emb_OS_video/Emb_OS_BBB_rec2/Emb_BBB_rec2.html)

``` bash
sudo apt-get update
java -version

sudo apt-get install default-jre # just the runtime environment and libraries not the toolchain/development kit (will unzip tarball and install)

java -version # should work now

# install firefox
# install eclipse c/c++ (oxygen version)

mv ~/Downloads/eclipse*.tar.gz ~/
cd ~
tar -xvf eclipse*.tar.gz
cd eclipse
./eclipse # installs eclipse with gui, select settings, and launch

# eclipse > make hello world c project > cross gcc (arm) (not linux gcc for x86) > TestArm > select debug and release >  arm-linux-gnueabi- with /usr/bin (make sure to include dash) > project>buildall > executable is now in binaries directory
```

## Video 4

[Link](https://web.eng.fiu.edu/aperezpo/Emb_OS_video/Emb_OS_BBB_rec3/Emb_OS_BBB_rec3.html)

``` bash
ping 192.168.7.2 # ping beaglebone

ssh root@192.168.7.2 -l root # (can login as debian or any other user) (-l means login as user blank)

ls

mkdir ARM

```

``` bash
# host machine

cd /eclipse-workspace/TestArm/Debug
ls -l
scp TestArm root@192.168.7.2:ARM
```

``` bash
# beaglebone ssh

ls -l

cd ARM
chmod a+x TestArm
./TestArm # might not work if dynamically linked
```

``` bash
# x84
ssh root@192.168.7.2 # will work automatically given that keys are stored

# eclipse > help > install new software > work with: Oxygen > Install GeneralPurposeTools>RemoteSystemExplorerUserActions > Next > Next > Accept Terms

# restart eclipse (remember to add eclipse to /opt and path)

# eclipse > windows > show views > other > remote systems > (remote system) > open > (drag and drop remote systems next to project explorer tab) > right click local > new connection > linux > Host name: 192.168.7.3 Connection name: Beaglebone > Next > ssh.files > Next > processes.shell.linux > Next > ssh.shells > Finish

# eclipse > remote systems > right click beaglebone > connect > userid root  (save password) > ok > yes continue > ok > cancel password recovery

# eclipse > remote systems > right click beaglebone>sshshells > launch shell > (new terminal with ssh session pops up on bottom of eclipse)

# eclipse > remote systems > beaglebone>sftp files > can delete and copy files
```

## Video 5

[Link](https://web.eng.fiu.edu/aperezpo/Emb_OS_video/Emb_OS_BBB_rec4/Emb_OS_BBB_rec4.html)

``` bash

# can run HelloArm on Beaglebone (didn't work last time) but can set up soft links for libraries or change toolchain from soft point to hard floating point library (hf)

# eclipse > project > properties > c/c++ build > settings 
# cross gcc linker > miscellaneous > linker flags: -static or nothing if you want it dynamic

# build steps > post build steps command: scp TestArm root@192.168.7.2:/root/prog
# ^ TestArm is executable file name
# ^ will copy executable after build to device

# eclipse > project > build all
# ^ will copy executable over
```

``` bash
# beaglebone after ssh 

cd /root/prog
./TestArm # should not work

# solution 1
ln -s /lib/ld-linux-armhf.so.3 /lib/ld-linux.so.3

# here we are changing the global arm linux dynamic linker which will load and link shared libraries for programs, will load them into memory

# hf is just hard float library

# *.so.3 represents shared object or shared library to be used by programs and 3 is just a version number

# ie libc.so.3 is just c standard library

# solution 2

# eclipse > new c roject > project name: TestArmhf toolchains: cross GCC > cross compiler prefix: arm-linux-gnueabihf- cross compiler path: /usr/bin

sudo apt-get install gcc-arm-linux-gnueabihf
sudo apt-get install g++-arm-linux-gnueabihf

# repeat same steps as above for soft point library
```
