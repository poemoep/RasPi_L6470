# RasPi_L6470

RasPi_L6470 is a library that makes L6470(STMicro) easy to use on Raspberry Pi.

# Features
you can do with this library

* Execute L6470 command(Run, Goto, GoHome ... and so on.)
* Set initial parametor to L6470.
* Get parametor from L6470.
* generate initial parametor with HEX.

# Requirement

* GNU Make (debug with ver4.2.1)
* GCC (debug with ver Raspbian 8.3.0-6+rpi1)
* WiringPi (debug with ver2.60)
    (For SPI control. Therefore, it may work with other SBCs, but I have not confirmed it. )

# Usage

First Test
```bash
git clone https://github.com/hoge/~
cd raspi_l6470
make 
./main
```

generate "L6470_user.h" from generator
```bash
"edit generator.h"
make user 
```
"make user" is build generator && execute "./gen"  && add stdout to "L6470_user.h"
The backup of L6470_user.h is left at the bottom of the same file using "#if 0".

# Author


* Made by poemoep.
  (I made it within my hobby, so there may be bugs.)

# License
The source code is licensed MIT.