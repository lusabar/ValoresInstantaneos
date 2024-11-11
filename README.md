# ValoresInstantaneos

**ValoresInstantaneos** is a simple application that aims to provide graphical representations of electric magnitudes various forms, namely: time-domain sinusoids, phasor diagram, Lissajous curve and instantaneous power.

## Installation ##

### Arch Linux and variants ###

```sh
wget https://github.com/lusabar/ValoresInstantaneos/releases/download/v1.0.0/ValoresInstantaneos-1.0.0-x86_64-ArchLinux.tar.gz
tar xfz ValoresInstantaneos-1.0.0-x86_64-ArchLinux.tar.gz
cd ValoresInstantaneos
makepkg -si
```

### Debian Linux and variants ###

```sh
wget https://github.com/lusabar/ValoresInstantaneos/releases/download/v1.0.0/ValoresInstantaneos-1.0.0-amd64-DebianLinux.deb
sudo dpkg -i ValoresInstantaneos-1.0.0-amd64-DebianLinux.deb 
sudo apt -f install
```

### Windows 10/11###

Download and execute the installer or unzip the avaliable .zip portable file and execute the program.

## Compile from source ##

### Linux ###

Clone this repository

```sh
git clone https://github.com/lusabar/ValoresInstantaneos
cd ValoresInstantaneos
```

Make a build directory and change into it

```sh
mkdir build
cd build
```

Run cmake

`cmake ..`

Run make

`make`
