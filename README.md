# SmartCOM3
ITInvest SmartCOM3 API C++ binding (Windows/Linux and possibly Mac OS X)    
It's usefull for coding C++ and linking native high performance C/C++ libraries with SmartCOM3 API
#Tested platforms
Windows 7/8 (32/64) + Visual Studio 2012/2013 (MSVC 11.0/12.0)

Ubuntu 12/14 & Debian 7/8 (32/64) + Winelib 1.6-1.8 (gcc 4.8-5.0)

# Installation & building
#Windows
1. Download SmartCOM3 API 32 or 64 bit from http://www.itinvest.ru/software/smartcom/
2. Install it
3. Launch Visual Studio and create empty WIN32 project
4. Just add sources and build project

#Linux
###Installation
1. Create Wine prefix 32 or 64 bit
2. Download corresponding SmartCOM3 API from http://www.itinvest.ru/software/smartcom/
3. Install it:      
    e.g. "wine msiexec /i /path/to/smartcom/setup.msi"    
    or just register dll like "wine regsvr32 /i /path/to/smartcom.dll"
4. Setup cyrillic support ru_RU.utf8

###Building     
Notes:      
1. Add "-D_FORCENAMELESSUNION" compiler flag (VARIANTs support)        
2. Link with libole32, liboleaut32 and libuuid      
3. If you building shared library, add position independent flag to compiler "-fPIC"     
```
mkdir build
cd build
wineg++ -std=c++11 -c -D_FORCENAMELESSUNION -MMD -MP -MF"SmartCOM3.d" -MT"SmartCOM3.d" -o "SmartCOM3.o" "../SmartCOM3.cpp"
wineg++ -std=c++11 -c -D_FORCENAMELESSUNION -MMD -MP -MF"SmartCOM3enums.d" -MT"SmartCOM3enums.d" -o "SmartCOM3enums.o" "../SmartCOM3enums.cpp"
wineg++ -std=c++11 -c -D_FORCENAMELESSUNION -MMD -MP -MF"Test.d" -MT"Test.d" -o "Test.o" "../Test.cpp"
wineg++ -o "SmartCOM3" ./SmartCOM3.o ./SmartCOM3enums.o ./Test.o -lole32 -loleaut32 -luuid
```
###Launching
Notes about error "wrong binary format"      
1. Check that you link all libs above and they are exist on LD path         
2. Wine prefix and downloaded SmartCOM3 version must be the same architecture (32 or 64 bit)       
```
env LANG=ru_RU.utf8 ./SmartCOM3.exe    
or directly without launcher script
env LANG=ru_RU.utf8 wine SmartCOM3.exe.so
```
#Test output
```
IStClient::InitializeApartments()
IStClient::InitializeApartments() OK
IStClient::IStClient()
IStClient::IStClient() OK
SmartCOM3 version: 3,0,162,5805

Connecting...
Press ENTER to disconnect
TestRobot::Connected()
TestRobot::AddSymbol(6A.CME.H2015) 1 of 21304
TestRobot::AddSymbol(6A.CME.M2015) 2 of 21304
TestRobot::AddSymbol(6A.CME.U2014) 3 of 21304
TestRobot::AddSymbol(6A.CME.Z2014) 4 of 21304
TestRobot::AddSymbol(6B.CME.H2015) 5 of 21304
TestRobot::AddSymbol(6B.CME.H2016) 6 of 21304
TestRobot::AddSymbol(6B.CME.H2017) 7 of 21304
TestRobot::AddSymbol(6B.CME.H2018) 8 of 21304
TestRobot::AddSymbol(6B.CME.M2015) 9 of 21304
TestRobot::AddSymbol(6B.CME.M2016) 10 of 21304
.....
TestRobot::AddSymbol() added 21304 of 21304

Disconnecting...
TestRobot::Disconnected(Disconnected by user)
Press ENTER to exit

IStClient::~IStClient()
IStClient::~IStClient() OK
IStClient::UninitializeApartments()
IStClient::UninitializeApartments() OK
```
