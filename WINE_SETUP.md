##Prepare & WINE installation
#####(Clean stock setup of Debian 8 netinst / Ubuntu Server 16.04 LTS)
```
sudo apt-get install software-properties-common
sudo locale-gen ru_RU.UTF-8
sudo apt-get install g++ git
```
#####32 bit (if required):
```
sudo dpkg --add-architecture i386
sudo apt-get install gcc-multilib g++-multilib libc6-dev-i386
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
sudo apt-get update
sudo apt-get install winehq-devel wine-devel-dev
```
##SmartCOM3 installation
_Notes:_    
   _1. Don't install Mono, Gecko and other if not required - just cancel_      
   _2. Paths to dll may be:_    
    _* like wine "C:\\Program Files\\..." or "Z:\\home\\...\prefix\drive_c\Program Files\\...") or_    
    _* like linux ("/home/.../prefix/drive_c/Program Files/...")_
    
###You already have SmartCOM3*.dll - just register:
#####32 bit:
```
WINEARCH=win32 WINEPREFIX=~/smartcom3prefix wine regsvr32 /i "/full/path/to/SmartCOM3.dll"
```
Output at the end: **regsvr32: Successfully installed DLL '.../SmartCOM3.dll'**
#####64 bit:
```
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix wine64 regsvr32 /i "/full/path/to/SmartCOM3_x64.dll"
```
Output at the end: **regsvr32: Successfully installed DLL '.../SmartCOM3_x64.dll'**
###You don't have SmartCOM3*.dll - download distrib & install:    
####Without graphical interface (local or remote w/o X-forwarding) type & ignore errors:
#####32 bit:
```
(e.g. wget -O SmartCOM-3.0.162.msi http://www.itinvest.ru/downloads/software/SmartCOM/3.0.162)
WINEARCH=win32 WINEPREFIX=~/smartcom3prefix wine msiexec /i SmartCOM-3.0.162.msi
```
Output at the end: **regsvr32: Successfully installed DLL '.../SmartCOM3.dll'**
#####64 bit:
```
(e.g. wget -O SmartCOM-x64-3.0.162.msi http://www.itinvest.ru/downloads/software/SmartCOM-x64/3.0.162)
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix wine64 msiexec /i SmartCOM-x64-3.0.162.msi
```
Output at the end: **regsvr32: Successfully installed DLL '.../SmartCOM3_x64.dll'**     
####With graphical interface     
_Don't install Mono, Gecko and other if not required - just cancel_     
#####32 bit:
```
(e.g. wget -O SmartCOM-3.0.162.msi http://www.itinvest.ru/downloads/software/SmartCOM/3.0.162)
WINEARCH=win32 WINEPREFIX=~/smartcom3prefix wine msiexec /i SmartCOM-3.0.162.msi
```
#####64 bit:
First install distrib (with wine 32 bit):
```
(e.g. wget -O SmartCOM-x64-3.0.162.msi http://www.itinvest.ru/downloads/software/SmartCOM-x64/3.0.162)
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix wine msiexec /i SmartCOM-x64-3.0.162.msi
```
And then register dll manually (with wine 64 bit):
```
WINEARCH=win64 WINEPREFIX=~/smartcom3prefix wine64 regsvr32 /i "/full/path/to/SmartCOM3_x64.dll"
```
Output at the end: **regsvr32: Successfully installed DLL '.../SmartCOM3_x64.dll'**     
##Compiling example
```
cd ~
git clone https://github.com/antonred/SmartCOM3
cd SmartCOM3
mkdir build
cd build
```
#####32 bit:
```
wineg++ -m32 -Wall -std=c++1y -c -D_FORCENAMELESSUNION ../SmartCOM3.cpp ../TestRobot.cpp
ls
SmartCOM3.o  TestRobot.o

wineg++ -m32 -o "TestRobot"  ./SmartCOM3.o ./TestRobot.o    -lole32 -loleaut32 -luuid -L"/opt/wine-devel/lib/wine" -L"/opt/wine-devel/lib"
ls
SmartCOM3.o  TestRobot.exe  TestRobot.exe.so  TestRobot.o
```
#####64 bit:
```
wineg++ -Wall -std=c++1y -c -D_FORCENAMELESSUNION ../SmartCOM3.cpp ../TestRobot.cpp
ls
SmartCOM3.o  TestRobot.o

wineg++ -o "TestRobot"  ./SmartCOM3.o ./TestRobot.o    -lole32 -loleaut32 -luuid
ls
SmartCOM3.o  TestRobot.exe  TestRobot.exe.so  TestRobot.o
```
#####TestRobot.exe.so - this is our program packed in shared lib
#####TestRobot.exe - this is launching script containing something like "wine TestRobot.exe.so"
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
#####32 bit:
```
echo "/opt/wine-devel/lib" | sudo tee --append /etc/ld.so.conf
echo "/opt/wine-devel/lib/wine" | sudo tee --append /etc/ld.so.conf
sudo ldconfig
```
#####64 bit:
```
echo "/opt/wine-devel/lib64" | sudo tee --append /etc/ld.so.conf
echo "/opt/wine-devel/lib64/wine" | sudo tee --append /etc/ld.so.conf
sudo ldconfig
```
