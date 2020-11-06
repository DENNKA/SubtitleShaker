# Compilation

## [Contents](README.md)

## ENGLISH; [НА РУССКОМ](Compilation.ru.md);
<!---
full line:
[ENGLISH](Compilation.md); [НА РУССКОМ](Compilation.ru.md);
-->

---
## Linux
### 1 Setup packages
Install c++, git, make, boost
#### Ubuntu based
`sudo apt-get install git build-essential`  
`sudo apt-get install libboost-all-dev`  
WARNING: boost version must be 1.66 and above  
check version:  
`apt-cache policy libboost-all-dev`  
If version less just search:  
`apt-cache search libboost1`  
and install, for example:  
`sudo apt-get install libboost1.71-all-dev`
### 2 Make
`git clone git@github.com:DENNKA/SubtitleShaker.git`  
`cd SubtitleShaker/`  
`make debug`  
### 3 Execute:
`./SubtitleShaker`  
It's symlink, binary files allocated in bin/debug and bin/release  

## Windows
### Visual Studio
 * Download boost https://www.boost.org
 * unpack in C:\ (or other location)
 * in start menu in folder Visual Studio open command promt
 * in cmd write:  
`cd C:\boost_X_XX_X`
 * and execute  
`.\boostrap.bat`  
 * wait, and also execute  
`.\b2 toolset=msvc --build-type=complete address-model=32 -j4`  
-j4 mean use 4 core, put your number  
compile take about 5gb in disc space  
 * wait
 * When compiled you can delete folder bin.v2
 * if you don't have errors i congratuate you
 * Open SubtitleShaker.sln  
go to Properties and check boost dir in C/C++ - Include dirs   (path_to_boost/) and in Linker - Library dirs (path_to_boost/stage/lib)  
compile x86  
 * End  
