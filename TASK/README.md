# TASK 


![cerium-ubuntu](https://github.com/satyajitghana/ProjektCerium/workflows/cerium-ubuntu/badge.svg)
![cerium-windows](https://github.com/satyajitghana/ProjektCerium/workflows/cerium-windows/badge.svg)

----
![release-date](https://img.shields.io/github/release-date-pre/satyajitghana/projektcerium)
![tag](https://img.shields.io/github/v/tag/satyajitghana/projektcerium?include_prereleases)
![release](https://img.shields.io/github/v/release/satyajitghana/projektcerium?include_prereleases)
![license](https://img.shields.io/github/license/satyajitghana/projektcerium)
![maintainer](https://img.shields.io/badge/maintainer-shadowleaf-blue)

## Build from source (Linux)

1. clone the repo

```
git clone https://github.com/AravindMutthe/Task.git


2. install dependencies


```
sudo apt update --fix-missing
sudo apt upgrade
sudo apt install libxt-dev libglew-dev libsuitesparse-dev
sudo apt install tk8.5 tcl8.5 tcl8.5-dev tcl-dev
```

GCC-9.2


```
sudo apt install gcc-9 g++-9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9 --slave /usr/bin/gcov gcov /usr/bin/gcov-9
```

OpenCV-4.2.0


```
sh install_opencv.sh
```

2. build


```
sh build.sh
```

3. run

```
.bin/cerium -h
An OpenCV Based, Video Processing Utils Library
Usage:
  cerium [OPTION...]

  -r, --record           Record
      --working_dir arg  Working directory (default: experiments)
  -o, --output arg       output filename (without extension) (default:
                         output)
  -t, --timestamp        add timestamp to filename (default: true)
      --cam arg          camera id (default: 0)
  -c, --channel arg      BGR -> 012 (default: 0)
  -l, --list             list the files stored in this manner
  -h, --help             print help

```

## Build from source (Windows)

Simply run build.ps1


```
powershell ./build.ps1
```

Make sure to copy all the .dll files from prebuilt opencv library from `C:\tools\opencv\build\x64\vc15\bin` to the exxecutable directory

### Sample Run to record video

`./cerium --record --working_dir=experiments -o output -t --cam=0 --channel=0`

### Sample Run to list video

`./cerium --list`

## My Notes for Arch Linux

Install VTK
`sudo pacman -S vtk`
