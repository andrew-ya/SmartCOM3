##WINE installation
#####(Clean stock setup of Debian 8 netinst / Ubuntu Server 16.04 LTS)
```
sudo apt-get install software-properties-common
sudo apt-get install gcc g++ git
sudo locale-gen ru_RU.UTF-8
```
#####Debian:
```
wget https://dl.winehq.org/wine-builds/Release.key
sudo apt-key add Release.key
sudo add-apt-repository "https://dl.winehq.org/wine-builds/debian/ $(lsb_release) main"
```
#####Ubuntu:
```
sudo add-apt-repository ppa:wine/wine-builds
```
#####Both:
```
sudo dpkg --add-architecture i386
sudo apt-get update
sudo apt-get install winehq-devel wine-devel-dev
```
##SmartCOM3 installation
#####If you already have SmartCOM3.dll (32bit) / SmartCOM3_x64.dll (64bit) from SmartCOM3 windows installation:
#####32 bit:
```
WINEARCH=win32 WINEPREFIX=~/smartcom3prefix wine regsvr32 /i /path/to/SmartCOM3.dll
```
#####64 bit:
```
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix wine64 regsvr32 /i /path/to/SmartCOM3_x64.dll
```
#####Or download from itinvest.ru SmartCOM3 distrib & install:
#####32 bit:
```
(e.g. wget -O SmartCOM-3.0.162.msi http://www.itinvest.ru/downloads/software/SmartCOM/3.0.162)
WINEARCH=win32 WINEPREFIX=~/smartcom3prefix wine msiexec /i SmartCOM-3.0.162.msi
```
#####64 bit:
```
(e.g. wget -O SmartCOM-x64-3.0.162.msi http://www.itinvest.ru/downloads/software/SmartCOM-x64/3.0.162)
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix wine64 msiexec /i SmartCOM-x64-3.0.162.msi
```
##Compiling example
```
cd ~
git clone https://github.com/antonred/SmartCOM3
cd SmartCOM3
mkdir build
cd build

wineg++ -Wall -std=c++1y -c -D_FORCENAMELESSUNION ../SmartCOM3.cpp ../TestRobot.cpp
ls
SmartCOM3.o  TestRobot.o

wineg++ -o "TestRobot"  ./SmartCOM3.o ./TestRobot.o    -lole32 -loleaut32 -luuid
ls
SmartCOM3.o  TestRobot.exe  TestRobot.exe.so  TestRobot.o
```
#####TestRobot.exe.so - this is our program packed in shared lib
#####TestRobot.exe - this is launching script containing something "wine TestRobot.exe.so"
##Running example
#####!!! mkdir ~/smartcom3prefix/drive_c/logs
#####32 bit:
```
WINEARCH=win32 WINEPREFIX=~/smartcom3prefix WINEDEBUG=-all ./TestRobot.exe mxdemo.ittrade.ru 8443 LOGIN PASSWORD
```
#####Or without script:
```
WINEARCH=win32 WINEPREFIX=~/smartcom3prefix WINEDEBUG=-all wine TestRobot.exe.so mxdemo.ittrade.ru 8443 LOGIN PASSWORD
```

#####64 bit:
```
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix WINEDEBUG=-all ./TestRobot.exe mxdemo.ittrade.ru 8443 LOGIN PASSWORD
```
#####Or without script:
```
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix WINEDEBUG=-all wine64 TestRobot.exe.so mxdemo.ittrade.ru 8443 LOGIN PASSWORD
```

##Troubleshooting
#####Fixing linking troubles:
```
echo "/opt/wine-devel/lib" | sudo tee --append /etc/ld.so.conf
echo "/opt/wine-devel/lib64" | sudo tee --append /etc/ld.so.conf
sudo ldconfig
```
