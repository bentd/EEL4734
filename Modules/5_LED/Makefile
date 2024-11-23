# Variables
CXX = g++
CXXFLAGS = -Wall -g

# Default to x86_64 if ARCH is not set
ARCH ?= arm

ifeq ($(ARCH), x86_64)
    CXX = g++
else ifeq ($(ARCH), arm)
    CXX = arm-linux-gnueabi-g++
endif

# Targets
all: main

main: leds.cpp
	$(CXX) $(CXXFLAGS) -o main leds.cpp -static

main-dynamic: leds.cpp
	$(CXX) $(CXXFLAGS) -o main leds.cpp

copy:
	scp -r $(CURDIR) beaglebone.local:/home/vagrant/Modules

clean:
	rm -f *.o main

.PHONY: all clean copy
